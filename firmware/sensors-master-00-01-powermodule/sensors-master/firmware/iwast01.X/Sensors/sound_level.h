

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
#define mode_TRIS                   TRISCbits.TRISC3
#define mode_LAT                    LATCbits.LATC3
#define mode_PORT                   PORTCbits.RC3
#define mode_WPU                    WPUCbits.WPUC3
#define mode_OD                     ODCONCbits.ODCC3
#define mode_ANS                    ANSELCbits.ANSC3
#define mode_SetHigh()              do { LATCbits.LATC3 = 1; } while(0)
#define mode_SetLow()               do { LATCbits.LATC3 = 0; } while(0)
#define mode_Toggle()               do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define mode_GetValue()             PORTCbits.RC3
#define mode_SetDigitalInput()      do { TRISCbits.TRISC3 = 1; } while(0)
#define mode_SetDigitalOutput()     do { TRISCbits.TRISC3 = 0; } while(0)
#define mode_SetPullup()            do { WPUCbits.WPUC3 = 1; } while(0)
#define mode_ResetPullup()          do { WPUCbits.WPUC3 = 0; } while(0)
#define mode_SetPushPull()          do { ODCONCbits.ODCC3 = 0; } while(0)
#define mode_SetOpenDrain()         do { ODCONCbits.ODCC3 = 1; } while(0)
#define mode_SetAnalogMode()        do { ANSELCbits.ANSC3 = 1; } while(0)
#define mode_SetDigitalMode()       do { ANSELCbits.ANSC3 = 0; } while(0)

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


#define AnalogIn_TRIS                 TRISCbits.TRISC1
#define AnalogIn_LAT                  LATCbits.LATC1
#define AnalogIn_PORT                 PORTCbits.RC1
#define AnalogIn_WPU                  WPUCbits.WPUC1
#define AnalogIn_OD                   ODCONCbits.ODCC1
#define AnalogIn_ANS                  ANSELCbits.ANSC1
#define AnalogIn_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define AnalogIn_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define AnalogIn_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define AnalogIn_GetValue()           PORTCbits.RC1
#define AnalogIn_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define AnalogIn_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define AnalogIn_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define AnalogIn_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define AnalogIn_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define AnalogIn_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define AnalogIn_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define AnalogIn_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

/* Initializer for:
typedef struct devApi{
   void (* Init)(void);
   void (* Measure)(void);
   void (* Loop)(void);
   void (* GetData)(uint8_t *, uint8_t *);
   void (* UpdateThreshold)(uint8_t, uint8_t *);
} Device_API_t;
 */
#define SENSOR_API { \
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