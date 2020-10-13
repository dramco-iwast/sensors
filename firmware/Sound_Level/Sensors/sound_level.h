/*  ____  ____      _    __  __  ____ ___
 * |  _ \|  _ \    / \  |  \/  |/ ___/ _ \
 * | | | | |_) |  / _ \ | |\/| | |  | | | |
 * | |_| |  _ <  / ___ \| |  | | |__| |_| |
 * |____/|_| \_\/_/   \_\_|  |_|\____\___/
 *                           research group
 *                             dramco.be/
 *
 *  KU Leuven - Technology Campus Gent,
 *  Gebroeders De Smetstraat 1,
 *  B-9000 Gent, Belgium
 *
 *         File: sound_level.h
 *      Created: 2019-09-11
 *       Author: Matthias Alleman
 *      Version: 0.2
 *
 *  Description: Sound Level Sensor Header File
 *
 */


#ifndef __SOUND_LEVEL_H__
#define	__SOUND_LEVEL_H__

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../global.h"

//#define BLINK_ACTIVE_LED

#define TYPE_BYTE   SOUND_LEVEL
#define M_NR        0x01

#define SLAVE_ADDRESS I2C_ADDRESS

// get/set powerMic aliases
#define powerMic_TRIS                 TRISCbits.TRISC0
#define powerMic_LAT                  LATCbits.LATC0
#define powerMic_PORT                 PORTCbits.RC0
#define powerMic_WPU                  WPUCbits.WPUC0
#define powerMic_OD                   ODCONCbits.ODCC0
#define powerMic_ANS                  ANSELCbits.ANSC0
#define powerMic_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define powerMic_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define powerMic_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define powerMic_GetValue()           PORTCbits.RC0
#define powerMic_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define powerMic_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define powerMic_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define powerMic_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define powerMic_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define powerMic_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define powerMic_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define powerMic_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set powerMic aliases
#define nWakeMic_TRIS                 TRISCbits.TRISC3
#define nWakeMic_LAT                  LATCbits.LATC3
#define nWakeMic_PORT                 PORTCbits.RC3
#define nWakeMic_WPU                  WPUCbits.WPUC3
#define nWakeMic_OD                   ODCONCbits.ODCC3
#define nWakeMic_ANS                  ANSELCbits.ANSC3
#define nWakeMic_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define nWakeMic_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define nWakeMic_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define nWakeMic_GetValue()           PORTCbits.RC3
#define nWakeMic_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define nWakeMic_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define nWakeMic_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define nWakeMic_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define nWakeMic_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define nWakeMic_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define nWakeMic_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define nWakeMic_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set READY aliases
#define READY_TRIS                 TRISCbits.TRISC7
#define READY_LAT                  LATCbits.LATC7
#define READY_PORT                 PORTCbits.RC7
#define READY_WPU                  WPUCbits.WPUC7
#define READY_OD                   ODCONCbits.ODCC7
#define READY_ANS                  ANSELCbits.ANSC7
#define READY_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define READY_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define READY_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define READY_GetValue()           PORTCbits.RC7
#define READY_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define READY_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define READY_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define READY_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define READY_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define READY_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define READY_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define READY_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)




// get/set LED aliases
#define LED_TRIS                 TRISBbits.TRISB6
#define LED_LAT                  LATBbits.LATB6
#define LED_PORT                 PORTBbits.RC6
#define LED_WPU                  WPUBbits.WPUB6
#define LED_OD                   ODCONBbits.ODCB6
#define LED_ANS                  ANSELBbits.ANSB6
#define LED_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define LED_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define LED_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define LED_GetValue()           PORTBbits.RB6
#define LED_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define LED_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define LED_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)


/* Initializer for:
typedef struct devApi{
   void (* Init)(void);
   void (* Measure)(void);
   void (* Loop)(void);
   void (* GetData)(uint8_t *, uint8_t *);
   void (* UpdateThreshold)(uint8_t, uint8_t *);
} Device_API_t;
 */
#define SOUND_API { \
    SoundLevel_Init, \
    SoundLevel_Measure, \
    SoundLevel_Loop, \
    SoundLevel_GetData, \
    SoundLevel_SetThreshold \
}  

/* Sensor API prototypes ******************************************************/

void SoundLevel_Init(void);
void SoundLevel_Measure(void);
void SoundLevel_Loop(void);
void SoundLevel_GetData(uint8_t * data, uint8_t  * length);
void SoundLevel_SetThreshold(uint8_t metric, uint8_t * thresholdData);

#endif	/* __SOUND_LEVEL_H__ */

