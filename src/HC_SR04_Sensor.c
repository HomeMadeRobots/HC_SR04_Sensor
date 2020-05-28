#include "HC_SR04_Sensor.h"

#include "Delay.h"


/*============================================================================*/
/* Macros */
/*============================================================================*/
#define MAX_PULSE_DURATION 24242 /* = D_max * 2 * 10^6 / Sound_Speed_min */
                                 /* =   4   * 2 * 10^6 /      330        */


/*============================================================================*/
/* Attributes access */
/*============================================================================*/
#define My_Obstacle_Distance (Me->var_attr->Obstacle_Distance)
#define My_Is_Measured_Distance_Valid (Me->var_attr->Is_Measured_Distance_Valid)
#define My_Sound_Speed (Me->var_attr->Sound_Speed)
#define My_Echo_Start_Time (Me->var_attr->Echo_Start_Time)
#define My_Echo_Stop_Time (Me->var_attr->Echo_Stop_Time)


/*============================================================================*/
/* Component_Operations */
/*============================================================================*/
void HC_SR04_Sensor__Cyclic( const HC_SR04_Sensor* Me )
{
    uint32_t pulse_duration = 0;
    
    /* Compute measured distance */
    /*****************************************************************
    Physical computation :
    
    distance = pulse_duration / 2 * sound_speed / 10^6
       [m]          [µs]               [m/s]      
       
       / 2    : round trip
       / 10^6 : convert [µs] to [s]
    
    ******************************************************************
    
    Software computation (take into account resolutions) :
    
    Distance * 2^-11 = pulse_duration / 2 * Sound_Speed * 10^-2 / 10^6
    
    Distance = pulse_duration * Sound_Speed / 97 656
    *****************************************************************/
    pulse_duration = My_Echo_Stop_Time - My_Echo_Start_Time;
    if( pulse_duration > MAX_PULSE_DURATION )
    {
        pulse_duration = MAX_PULSE_DURATION;
        My_Is_Measured_Distance_Valid = false;
    }
    else
    {
        My_Is_Measured_Distance_Valid = true;
    }
    My_Obstacle_Distance = (pulse_duration * My_Sound_Speed ) / 97656;

    /* Trigger a new measure */
    Me->Trigger_Pin->Set_Level( IO_LEVEL_HIGH );
    Wait_Microsecond( 10 );
    Me->Trigger_Pin->Set_Level( IO_LEVEL_LOW );
}


/*============================================================================*/
/* Realized interfaces */
/*============================================================================*/
void HC_SR04__Obstacle_Distance__Get_Measured_Distance(
    const HC_SR04_Sensor* Me,
    T_Distance* distance )
{
    *distance = My_Obstacle_Distance;
}
/*----------------------------------------------------------------------------*/
void HC_SR04__Obstacle_Distance__Is_Measured_Distance_Valid(
    const HC_SR04_Sensor* Me,
    bool* is_measure_valid )
{
    *is_measure_valid = My_Is_Measured_Distance_Valid;
}
/*----------------------------------------------------------------------------*/
void HC_SR04__Setting__Set_Sound_Speed(
    const HC_SR04_Sensor* Me,
    uint16_t speed )
{
    My_Sound_Speed = speed;
}


/*============================================================================*/
/* Received events */
/*============================================================================*/
void HC_SR04__Echo_Pin__Hardware_Interruption_Arised(
    const HC_SR04_Sensor* Me,
    E_IO_Level pin_level,
    uint32_t interruption_timestamp )
{
    if( pin_level == IO_LEVEL_HIGH )
    {
        My_Echo_Start_Time = interruption_timestamp;
    }
    else
    {
        My_Echo_Stop_Time = interruption_timestamp;
    }
}