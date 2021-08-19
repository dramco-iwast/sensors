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
 *         File: battery.h
 *      Created: 2020-11-27
 *       Author: Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Read battery voltage
 *
 */


#ifndef __BATTERY_H__
#define __BATTERY_H__

/* Header includes */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../global.h"

typedef enum{
    BATTERY_FVR_DISABLE,
    BATTERY_FVR_ENABLE,
}battery_fvr_t;


void ADC_Init();
void ADC_Fixed_Voltage_Ref(battery_fvr_t mode);
void battery_init();
float battery_measure(void);

#define BAT_VOLT_ADC_CHN   0x14

// get/set BAT_MEAS_EN_TRIS aliases
#define BAT_MEAS_EN_TRIS                    TRISAbits.TRISA2
#define BAT_MEAS_EN_LAT                     LATAbits.LATA2
#define BAT_MEAS_EN_PORT                    PORTAbits.RA2
#define BAT_MEAS_EN_WPU                     WPUAbits.WPUA2
#define BAT_MEAS_EN_OD                      ODCONAbits.ODCA2
#define BAT_MEAS_EN_ANS                     ANSELAbits.ANSA2
#define BAT_MEAS_EN_SetHigh()               do { LATAbits.LATA2 = 1; } while(0)
#define BAT_MEAS_EN_SetLow()                do { LATAbits.LATA2 = 0; } while(0)
#define BAT_MEAS_EN_Toggle()                do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define BAT_MEAS_EN_GetValue()              PORTAbits.RA2
#define BAT_MEAS_EN_SetDigitalInput()       do { TRISAbits.TRISA2 = 1; } while(0)
#define BAT_MEAS_EN_SetDigitalOutput()      do { TRISAbits.TRISA2 = 0; } while(0)
#define BAT_MEAS_EN_SetPullup()             do { WPUAbits.WPUA2 = 1; } while(0)
#define BAT_MEAS_EN_ResetPullup()           do { WPUAbits.WPUA2 = 0; } while(0)
#define BAT_MEAS_EN_SetPushPull()           do { ODCONAbits.ODCA2 = 0; } while(0)
#define BAT_MEAS_EN_SetOpenDrain()          do { ODCONAbits.ODCA2 = 1; } while(0)
#define BAT_MEAS_EN_SetAnalogMode()         do { ANSELAbits.ANSA2 = 1; } while(0)
#define BAT_MEAS_EN_SetDigitalMode()        do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set BAT_VOLT aliases
#define BAT_VOLT_TRIS                       TRISCbits.TRISC4
#define BAT_VOLT_LAT                        LATCbits.LATC4
#define BAT_VOLT_PORT                       PORTCbits.RC4
#define BAT_VOLT_WPU                        WPUCbits.WPUC4
#define BAT_VOLT_OD                         ODCONCbits.ODCC4
#define BAT_VOLT_ANS                        ANSELCbits.ANSC4
#define BAT_VOLT_SetHigh()                  do { LATCbits.LATC4 = 1; } while(0)
#define BAT_VOLT_SetLow()                   do { LATCbits.LATC4 = 0; } while(0)
#define BAT_VOLT_Toggle()                   do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define BAT_VOLT_GetValue()                 PORTCbits.RC4
#define BAT_VOLT_SetDigitalInput()          do { TRISCbits.TRISC4 = 1; } while(0)
#define BAT_VOLT_SetDigitalOutput()         do { TRISCbits.TRISC4 = 0; } while(0)
#define BAT_VOLT_SetPullup()                do { WPUCbits.WPUC4 = 1; } while(0)
#define BAT_VOLT_ResetPullup()              do { WPUCbits.WPUC4 = 0; } while(0)
#define BAT_VOLT_SetPushPull()              do { ODCONCbits.ODCC4 = 0; } while(0)
#define BAT_VOLT_SetOpenDrain()             do { ODCONCbits.ODCC4 = 1; } while(0)
#define BAT_VOLT_SetAnalogMode()            do { ANSELCbits.ANSC4 = 1; } while(0)
#define BAT_VOLT_SetDigitalMode()           do { ANSELCbits.ANSC4 = 0; } while(0)


#endif
