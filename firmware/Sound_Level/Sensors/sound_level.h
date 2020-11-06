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
 *       Author: Matthias Alleman - Jona Cappelle
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

#define BLINK_ACTIVE_LED

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

// get/set DOUT aliases
#define DOUT_TRIS                 TRISCbits.TRISC6
#define DOUT_LAT                  LATCbits.LATC6
#define DOUT_PORT                 PORTCbits.RC6
#define DOUT_WPU                  WPUCbits.WPUC6
#define DOUT_OD                   ODCONCbits.ODCC6
#define DOUT_ANS                  ANSELCbits.ANSC6
#define DOUT_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define DOUT_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define DOUT_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define DOUT_GetValue()           PORTCbits.RC6
#define DOUT_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define DOUT_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define DOUT_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define DOUT_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define DOUT_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define DOUT_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define DOUT_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define DOUT_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)


// get/set VDDBIASAMP aliases
#define VDDBIASAMP_TRIS                 TRISBbits.TRISB4
#define VDDBIASAMP_LAT                  LATBbits.LATB4
#define VDDBIASAMP_PORT                 PORTBbits.RB4
#define VDDBIASAMP_WPU                  WPUBbits.WPUB4
#define VDDBIASAMP_OD                   ODCONBbits.ODCB4
#define VDDBIASAMP_ANS                  ANSELBbits.ANSB4
#define VDDBIASAMP_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define VDDBIASAMP_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define VDDBIASAMP_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define VDDBIASAMP_GetValue()           PORTBbits.RB4
#define VDDBIASAMP_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define VDDBIASAMP_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define VDDBIASAMP_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define VDDBIASAMP_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define VDDBIASAMP_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define VDDBIASAMP_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define VDDBIASAMP_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define VDDBIASAMP_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set VDDBIAS aliases
#define VDDBIAS_TRIS                 TRISCbits.TRISC2
#define VDDBIAS_LAT                  LATCbits.LATC2
#define VDDBIAS_PORT                 PORTCbits.RC2
#define VDDBIAS_WPU                  WPUCbits.WPUC2
#define VDDBIAS_OD                   ODCONCbits.ODCC2
#define VDDBIAS_ANS                  ANSELCbits.ANSC2
#define VDDBIAS_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define VDDBIAS_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define VDDBIAS_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define VDDBIAS_GetValue()           PORTCbits.RC2
#define VDDBIAS_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define VDDBIAS_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define VDDBIAS_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define VDDBIAS_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define VDDBIAS_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define VDDBIAS_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define VDDBIAS_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define VDDBIAS_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set VDDAMP aliases
#define VDDAMP_TRIS                 TRISCbits.TRISC4
#define VDDAMP_LAT                  LATCbits.LATC4
#define VDDAMP_PORT                 PORTCbits.RC4
#define VDDAMP_WPU                  WPUCbits.WPUC4
#define VDDAMP_OD                   ODCONCbits.ODCC4
#define VDDAMP_ANS                  ANSELCbits.ANSC4
#define VDDAMP_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define VDDAMP_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define VDDAMP_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define VDDAMP_GetValue()           PORTCbits.RC4
#define VDDAMP_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define VDDAMP_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define VDDAMP_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define VDDAMP_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define VDDAMP_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define VDDAMP_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define VDDAMP_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define VDDAMP_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)



// get/set THRESHOLD1 aliases
#define THRESHOLD1_TRIS                 TRISAbits.TRISA2
#define THRESHOLD1_LAT                  LATAbits.LATA2
#define THRESHOLD1_PORT                 PORTAbits.RA2
#define THRESHOLD1_WPU                  WPUAbits.WPUA2
#define THRESHOLD1_OD                   ODCONAbits.ODCA2
#define THRESHOLD1_ANS                  ANSELAbits.ANSA2
#define THRESHOLD1_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define THRESHOLD1_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define THRESHOLD1_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define THRESHOLD1_GetValue()           PORTAbits.RA2
#define THRESHOLD1_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define THRESHOLD1_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define THRESHOLD1_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define THRESHOLD1_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define THRESHOLD1_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define THRESHOLD1_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define THRESHOLD1_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define THRESHOLD1_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)


// get/set THRESHOLD2 aliases
#define THRESHOLD2_TRIS                 TRISCbits.TRISC5
#define THRESHOLD2_LAT                  LATCbits.LATC5
#define THRESHOLD2_PORT                 PORTCbits.RC5
#define THRESHOLD2_WPU                  WPUCbits.WPUC5
#define THRESHOLD2_OD                   ODCONCbits.ODCC5
#define THRESHOLD2_ANS                  ANSELCbits.ANSC5
#define THRESHOLD2_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define THRESHOLD2_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define THRESHOLD2_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define THRESHOLD2_GetValue()           PORTCbits.RC5
#define THRESHOLD2_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define THRESHOLD2_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define THRESHOLD2_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define THRESHOLD2_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define THRESHOLD2_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define THRESHOLD2_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define THRESHOLD2_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define THRESHOLD2_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)



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

