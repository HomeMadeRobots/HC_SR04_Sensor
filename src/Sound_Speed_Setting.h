#ifndef SOUND_SPEED_SETTING_H
#define SOUND_SPEED_SETTING_H


/* Arguments */
#include <stdint.h>


/*============================================================================*/
/* Client_Server_Interface */
/*============================================================================*/
typedef struct {
    /* Synchronous_Operation */
    void (*Set_Sound_Speed) ( uint16_t sound_speed );
} Sound_Speed_Setting;


#endif