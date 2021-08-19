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
 *         File: system.h
 *      Created: 2020-10-02
 *       Author: Geoffrey Ottoy
 *      Version: 2.0
 *
 *  Description: Header file for system.c which contains basic system
 *               initialization (for the oscillator and I2C slave interface).
 * 
 */

#ifndef __SYSTEM_H__
#define	__SYSTEM_H__

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>

   
void SYSTEM_Initialize(uint8_t slave_address); //MODIFIED (was void))
void SYSTEM_SetSensorISR(void (* SensorInterruptHandler)(void));

#ifdef	__cplusplus
}
#endif

#endif	/* __SYSTEM_H__ */

