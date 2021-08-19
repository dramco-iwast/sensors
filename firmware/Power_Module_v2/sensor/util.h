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
 *         File: util.h
 *      Created: 2020-11-27
 *       Author: Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Utilities - LEDS - Interrupt pin
 *
 */

#ifndef __UTIL_H__
#define __UTIL_H__

/* Header includes */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../global.h"

#define WDT_COUNT_OK_INTERVAL 4

void Enter_sleep();

void LED_Init(void);
void LED_Blink(void);

void comm_init(void);
void generateInt(void);

void WDT_Init(void);
void WDT_set_16sec();
void WDT_set_64sec();


// get/set LED0 aliases
#define LED0_TRIS                 TRISCbits.TRISC7
#define LED0_LAT                  LATCbits.LATC7
#define LED0_PORT                 PORTCbits.RC7
#define LED0_WPU                  WPUCbits.WPUC7
#define LED0_OD                   ODCONCbits.ODCC7
#define LED0_ANS                  ANSELCbits.ANSC7
#define LED0_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define LED0_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define LED0_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define LED0_GetValue()           PORTCbits.RC7
#define LED0_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define LED0_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define LED0_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define LED0_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define LED0_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define LED0_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define LED0_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define LED0_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)


// get/set LED1 aliases
#define LED1_TRIS                           TRISCbits.TRISC6
#define LED1_LAT                            LATCbits.LATC6
#define LED1_PORT                           PORTCbits.RC6
#define LED1_WPU                            WPUCbits.WPUC6
#define LED1_OD                             ODCONCbits.ODCC6
#define LED1_ANS                            ANSELCbits.ANSC6
#define LED1_SetHigh()                      do { LATCbits.LATC6 = 1; } while(0)
#define LED1_SetLow()                       do { LATCbits.LATC6 = 0; } while(0)
#define LED1_Toggle()                       do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define LED1_GetValue()                     PORTCbits.RC6
#define LED1_SetDigitalInput()              do { TRISCbits.TRISC6 = 1; } while(0)
#define LED1_SetDigitalOutput()             do { TRISCbits.TRISC6 = 0; } while(0)
#define LED1_SetPullup()                    do { WPUCbits.WPUC6 = 1; } while(0)
#define LED1_ResetPullup()                  do { WPUCbits.WPUC6 = 0; } while(0)
#define LED1_SetPushPull()                  do { ODCONCbits.ODCC6 = 0; } while(0)
#define LED1_SetOpenDrain()                 do { ODCONCbits.ODCC6 = 1; } while(0)
#define LED1_SetAnalogMode()                do { ANSELCbits.ANSC6 = 1; } while(0)
#define LED1_SetDigitalMode()               do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set READY aliases
#define READY_TRIS                 TRISCbits.TRISC0
#define READY_LAT                  LATCbits.LATC0
#define READY_PORT                 PORTCbits.RC0
#define READY_WPU                  WPUCbits.WPUC0
#define READY_OD                   ODCONCbits.ODCC0
#define READY_ANS                  ANSELCbits.ANSC0
#define READY_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define READY_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define READY_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define READY_GetValue()           PORTCbits.RC0
#define READY_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define READY_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define READY_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define READY_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define READY_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define READY_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define READY_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define READY_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

#endif
