#ifndef HC_SR04_SENSOR_H
#define HC_SR04_SENSOR_H


/*============================================================================*/
/* Inclusions */
/*============================================================================*/
/* Attributes */
#include <stdint.h>


/* Realized interfaces */
#include "Distance_Measurement.h"
#include "Sound_Speed_Setting.h"


/* Required interfaces */
#include "Discrete_Output.h"


/* Received events */
#include "Hardware_Interruption_Arised.h"


/*============================================================================*/
/* Component_Type */
/*============================================================================*/
typedef struct {
    uint32_t Echo_Start_Time;
    uint32_t Echo_Stop_Time;
    uint16_t Sound_Speed; /* cm/s */
    T_Distance Obstacle_Distance;
    bool Is_Measured_Distance_Valid;
} HC_SR04_Sensor_Var;

typedef struct {

    /* Variable attributes */
    HC_SR04_Sensor_Var* var_attr;

    /* Required interfaces */
    const Discrete_Output* Trigger_Pin;

} HC_SR04_Sensor;


/*============================================================================*/
/* Component_Operations */
/*============================================================================*/
void HC_SR04_Sensor__Cyclic( const HC_SR04_Sensor* Me );


/*============================================================================*/
/* Realized interfaces */
/*============================================================================*/
void HC_SR04__Obstacle_Distance__Get_Measured_Distance(
    const HC_SR04_Sensor* Me,
    T_Distance* distance );
void HC_SR04__Obstacle_Distance__Is_Measured_Distance_Valid(
    const HC_SR04_Sensor* Me,
    bool* is_measure_valid );
    
void HC_SR04__Setting__Set_Sound_Speed(
    const HC_SR04_Sensor* Me,
    uint16_t speed );


/*============================================================================*/
/* Received events */
/*============================================================================*/
void HC_SR04__Echo_Pin__Hardware_Interruption_Arised(
    const HC_SR04_Sensor* Me,
    E_IO_Level Pin_Level,
    uint32_t Interruption_Timestamp );

#endif