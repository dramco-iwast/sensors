/* 
 * File:   bme680_air_quality.h
 * Author: Sarah
 *
 * Created on 11 september 2019, 13:26
 */

//#ifndef BME680_SENSOR_H
//#define	BME680_SENSOR_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../global.h"
    
#define TYPE_BYTE       BME680
#define M_NR            0x04

#define SLAVE_ADDRESS   I2C_ADDRESS

// get/set USER_LED aliases
#define USER_LED_TRIS                 TRISAbits.TRISA2
#define USER_LED_LAT                  LATAbits.LATA2
#define USER_LED_PORT                 PORTAbits.RA2
#define USER_LED_WPU                  WPUAbits.WPUA2
#define USER_LED_OD                   ODCONAbits.ODCA2
#define USER_LED_ANS                  ANSELAbits.ANSA2
#define USER_LED_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define USER_LED_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define USER_LED_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define USER_LED_GetValue()           PORTAbits.RA2
#define USER_LED_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define USER_LED_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define USER_LED_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define USER_LED_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define USER_LED_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define USER_LED_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define USER_LED_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define USER_LED_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set INT aliases
#define READY_TRIS                 TRISAbits.TRISA4
#define READY_LAT                  LATAbits.LATA4
#define READY_PORT                 PORTAbits.RA4
#define READY_WPU                  WPUAbits.WPUA4
#define READY_OD                   ODCONAbits.ODCA4
#define READY_ANS                  ANSELAbits.ANSA4
#define READY_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define READY_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define READY_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define READY_GetValue()           PORTAbits.RA4
#define READY_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define READY_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define READY_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define READY_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define READY_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define READY_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define READY_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define READY_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set CS1 aliases
#define CS1_TRIS                 TRISCbits.TRISC7
#define CS1_LAT                  LATCbits.LATC7
#define CS1_PORT                 PORTCbits.RC7
#define CS1_WPU                  WPUCbits.WPUC7
#define CS1_OD                   ODCONCbits.ODCC7
#define CS1_ANS                  ANSELCbits.ANSC7
#define CS1_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define CS1_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define CS1_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define CS1_GetValue()           PORTCbits.RC7
#define CS1_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define CS1_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define CS1_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define CS1_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define CS1_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define CS1_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define CS1_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define CS1_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

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
    BME680_Init, \
    BME680_Measure, \
    BME680_Loop, \
    BME680_GetData, \
    BME680_SetThreshold \
}  

/* Sensor API prototypes ******************************************************/

void BME680_Init(void);
void BME680_Measure(void);
void BME680_Loop(void);
void BME680_GetData(uint8_t * data, uint8_t  * length);
void BME680_SetThreshold(uint8_t metric, uint8_t * thresholdData);

// todo: check if these can be moved elsewhere
//void delay_ms(uint32_t period);
int8_t spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t spi_transfer(uint8_t x);


