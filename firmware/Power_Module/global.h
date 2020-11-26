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
 *         File: global.h
 *      Created: 2020-10-02
 *       Author: Geoffrey Ottoy
 *      Version: 2.0
 *
 *  Description: Global settings, constants and types
 *
 */

#ifndef __GLOBAL_H__
#define	__GLOBAL_H__

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

/******************************************************************************
 * Build settings -> modify to your needs                                     *
 ******************************************************************************/   

#define I2C_ADDRESS                 0x45

#define SENSOR_TYPE                 POWER    
    
/******************************************************************************
 * Definitions and types                                                      *
 ******************************************************************************/
#define DEFAULT_ACK                 0xAA

// i2c slave device commands
#define CMD_POLL                    0x10 // see if a sensor responds
#define CMD_DEVICE_TYPE             0x11 // request the sensor device type
#define CMD_INT_TOGGLE              0x15 // request toggle (on the sensor of interrupt line)
#define CMD_GET_M_NR                0x23 // get nr. of metrics
#define CMD_GET_M_DATA              0x14 // get measurement
#define CMD_START_MEASUREMENT       0x13 // get/start a measurement
#define CMD_SET_THRESHOLDS          0x24 // set thresholds

 // supported sensor types
#define SOUND_LEVEL                 0x01
#define BUTTONS                     0x02
#define BME680                      0x03
#define POWER                       0x01 // TODO change to 0x04, for testing purposes, the power module becomes a sound module

/* general sensor API providing methods for
 *  - initializing sensor operation
 *  - starting a new measurement
 *  - sensor 'loop' behavior
 *  - retrieving measurement data
 *  - setting thresholds
 */
typedef struct sensorApi{
    void (* Init)(void);
    void (* Measure)(void);
    void (* Loop)(void);
    void (* GetData)(uint8_t *, uint8_t *);
    void (* UpdateThreshold)(uint8_t, uint8_t *);
} Sensor_API_t;

// default operating frequency (32 MHz internal oscillator)
#define _XTAL_FREQ 32000000

/******************************************************************************
 * CONFIGURATION WORD                                                         *
 ******************************************************************************/

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINT1    // Power-up default value for COSC bits->HFINTOSC (1MHz)
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN = ON     // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable bit->FSCM timer enabled

// CONFIG2
#pragma config MCLRE = ON    // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config PWRTS = OFF    // Power-up Timer Enable bit->PWRT disabled
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN = OFF    // Brown-out reset enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 2.45V
#pragma config ZCDDIS = OFF    // Zero-cross detect disable->Zero-cross detect circuit is disabled at POR.
#pragma config PPS1WAY = OFF    // Peripheral Pin Select one-way control->The PPSLOCK bit can be cleared and set only once in software
#pragma config STVREN = OFF    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG3
#pragma config WDTCPS = WDTCPS_10    // WDT Period Select bits->Divider ratio 1:32768
//#pragma config WDTE = SWDTEN    // WDT enabled/disabled by SWDTEN bit in WDTCON0
#pragma config WDTE = OFF    // WDT enabled/disabled by SWDTEN bit in WDTCON0
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC    // WDT input clock selector->WDT reference clock is the 31.0kHz LFINTOSC output

// CONFIG4
#pragma config BBSIZE = BB512    // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF    // Boot Block Enable bit->Boot Block disabled
#pragma config SAFEN = OFF    // SAF Enable bit->SAF disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block not write protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block not write protected
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration Register not write protected
#pragma config WRTD = OFF    // Data EEPROM write protection bit->Data EEPROM NOT write protected
#pragma config WRTSAF = OFF    // Storage Area Flash Write Protection bit->SAF not write protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.

// CONFIG5
#pragma config CP = OFF    // UserNVM Program memory code protection bit->UserNVM code protection disabled

#ifdef	__cplusplus
}
#endif

#endif	/* __GLOBAL_H__ */
