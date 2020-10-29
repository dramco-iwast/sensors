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
 *      Created: 2019-09-11
 *       Author: Geoffrey Ottoy
 *      Version: 0.1
 *
 *  Description: Global settings, constants and types
 *
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif

/******************************************************************************
 * Build settings -> modify to your needs                                     *
 ******************************************************************************/   

//#define I2C_ADDRESS                 0x67
//#define I2C_ADDRESS                 0x48
#define I2C_ADDRESS                   0x90
    
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
#define POWER                       0x04 // terug wijzigen naar 4!!!
    
/* general sensor API providing methods for
 *  - initializing sensor operation
 *  - starting a new measurement
 *  - sensor 'loop' behavior
 *  - retrieving measurement data
 *  - setting thresholds
 */
typedef struct devApi{
    void (* Init)(void);
    void (* Measure)(void);
    void (* Loop)(void);
    void (* GetData)(uint8_t *, uint8_t *);
    void (* UpdateThreshold)(uint8_t, uint8_t *);
} Device_API_t;


#define _XTAL_FREQ 32000000

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

