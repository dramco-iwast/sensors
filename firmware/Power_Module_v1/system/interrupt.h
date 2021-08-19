#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define GlobalInterruptEnable() (INTCONbits.GIE = 1)

#define GlobalInterruptDisable() (INTCONbits.GIE = 0)

#define PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

#define PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

void SetSensorInterruptHandler(void (* InterruptHandler)(void));

#endif  /* __INTERRUPT_H__ */
