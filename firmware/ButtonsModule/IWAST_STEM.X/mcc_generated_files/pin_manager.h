/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18446
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LSW_1 aliases
#define LSW_1_TRIS                 TRISAbits.TRISA2
#define LSW_1_LAT                  LATAbits.LATA2
#define LSW_1_PORT                 PORTAbits.RA2
#define LSW_1_WPU                  WPUAbits.WPUA2
#define LSW_1_OD                   ODCONAbits.ODCA2
#define LSW_1_ANS                  ANSELAbits.ANSA2
#define LSW_1_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LSW_1_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LSW_1_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LSW_1_GetValue()           PORTAbits.RA2
#define LSW_1_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LSW_1_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LSW_1_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LSW_1_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LSW_1_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define LSW_1_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define LSW_1_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define LSW_1_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set READY aliases
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

// get/set SDA1 aliases
#define SDA1_TRIS                 TRISBbits.TRISB5
#define SDA1_LAT                  LATBbits.LATB5
#define SDA1_PORT                 PORTBbits.RB5
#define SDA1_WPU                  WPUBbits.WPUB5
#define SDA1_OD                   ODCONBbits.ODCB5
#define SDA1_ANS                  ANSELBbits.ANSB5
#define SDA1_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define SDA1_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define SDA1_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define SDA1_GetValue()           PORTBbits.RB5
#define SDA1_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define SDA1_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define SDA1_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define SDA1_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define SDA1_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define SDA1_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define SDA1_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS                 TRISBbits.TRISB7
#define SCL1_LAT                  LATBbits.LATB7
#define SCL1_PORT                 PORTBbits.RB7
#define SCL1_WPU                  WPUBbits.WPUB7
#define SCL1_OD                   ODCONBbits.ODCB7
#define SCL1_ANS                  ANSELBbits.ANSB7
#define SCL1_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define SCL1_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define SCL1_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define SCL1_GetValue()           PORTBbits.RB7
#define SCL1_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define SCL1_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define SCL1_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define SCL1_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define SCL1_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define SCL1_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define SCL1_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set SW_2 aliases
#define SW_2_TRIS                 TRISCbits.TRISC0
#define SW_2_LAT                  LATCbits.LATC0
#define SW_2_PORT                 PORTCbits.RC0
#define SW_2_WPU                  WPUCbits.WPUC0
#define SW_2_OD                   ODCONCbits.ODCC0
#define SW_2_ANS                  ANSELCbits.ANSC0
#define SW_2_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SW_2_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SW_2_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SW_2_GetValue()           PORTCbits.RC0
#define SW_2_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SW_2_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define SW_2_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define SW_2_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define SW_2_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define SW_2_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define SW_2_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define SW_2_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set Led0 aliases
#define Led0_TRIS                 TRISCbits.TRISC1
#define Led0_LAT                  LATCbits.LATC1
#define Led0_PORT                 PORTCbits.RC1
#define Led0_WPU                  WPUCbits.WPUC1
#define Led0_OD                   ODCONCbits.ODCC1
#define Led0_ANS                  ANSELCbits.ANSC1
#define Led0_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define Led0_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define Led0_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define Led0_GetValue()           PORTCbits.RC1
#define Led0_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define Led0_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define Led0_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define Led0_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define Led0_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define Led0_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define Led0_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define Led0_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SW_1 aliases
#define SW_1_TRIS                 TRISCbits.TRISC2
#define SW_1_LAT                  LATCbits.LATC2
#define SW_1_PORT                 PORTCbits.RC2
#define SW_1_WPU                  WPUCbits.WPUC2
#define SW_1_OD                   ODCONCbits.ODCC2
#define SW_1_ANS                  ANSELCbits.ANSC2
#define SW_1_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SW_1_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SW_1_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SW_1_GetValue()           PORTCbits.RC2
#define SW_1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SW_1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SW_1_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SW_1_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SW_1_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define SW_1_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define SW_1_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define SW_1_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set LSW_3 aliases
#define LSW_3_TRIS                 TRISCbits.TRISC3
#define LSW_3_LAT                  LATCbits.LATC3
#define LSW_3_PORT                 PORTCbits.RC3
#define LSW_3_WPU                  WPUCbits.WPUC3
#define LSW_3_OD                   ODCONCbits.ODCC3
#define LSW_3_ANS                  ANSELCbits.ANSC3
#define LSW_3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define LSW_3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define LSW_3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define LSW_3_GetValue()           PORTCbits.RC3
#define LSW_3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define LSW_3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define LSW_3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define LSW_3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define LSW_3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define LSW_3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define LSW_3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define LSW_3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SW_3 aliases
#define SW_3_TRIS                 TRISCbits.TRISC4
#define SW_3_LAT                  LATCbits.LATC4
#define SW_3_PORT                 PORTCbits.RC4
#define SW_3_WPU                  WPUCbits.WPUC4
#define SW_3_OD                   ODCONCbits.ODCC4
#define SW_3_ANS                  ANSELCbits.ANSC4
#define SW_3_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SW_3_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SW_3_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SW_3_GetValue()           PORTCbits.RC4
#define SW_3_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SW_3_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SW_3_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define SW_3_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define SW_3_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define SW_3_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define SW_3_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define SW_3_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set LSW_2 aliases
#define LSW_2_TRIS                 TRISCbits.TRISC5
#define LSW_2_LAT                  LATCbits.LATC5
#define LSW_2_PORT                 PORTCbits.RC5
#define LSW_2_WPU                  WPUCbits.WPUC5
#define LSW_2_OD                   ODCONCbits.ODCC5
#define LSW_2_ANS                  ANSELCbits.ANSC5
#define LSW_2_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define LSW_2_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define LSW_2_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define LSW_2_GetValue()           PORTCbits.RC5
#define LSW_2_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define LSW_2_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define LSW_2_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define LSW_2_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define LSW_2_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define LSW_2_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define LSW_2_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define LSW_2_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set SW_4 aliases
#define SW_4_TRIS                 TRISCbits.TRISC6
#define SW_4_LAT                  LATCbits.LATC6
#define SW_4_PORT                 PORTCbits.RC6
#define SW_4_WPU                  WPUCbits.WPUC6
#define SW_4_OD                   ODCONCbits.ODCC6
#define SW_4_ANS                  ANSELCbits.ANSC6
#define SW_4_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define SW_4_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define SW_4_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define SW_4_GetValue()           PORTCbits.RC6
#define SW_4_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define SW_4_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define SW_4_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define SW_4_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define SW_4_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define SW_4_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define SW_4_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define SW_4_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set LSW_4 aliases
#define LSW_4_TRIS                 TRISCbits.TRISC7
#define LSW_4_LAT                  LATCbits.LATC7
#define LSW_4_PORT                 PORTCbits.RC7
#define LSW_4_WPU                  WPUCbits.WPUC7
#define LSW_4_OD                   ODCONCbits.ODCC7
#define LSW_4_ANS                  ANSELCbits.ANSC7
#define LSW_4_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define LSW_4_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define LSW_4_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define LSW_4_GetValue()           PORTCbits.RC7
#define LSW_4_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define LSW_4_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define LSW_4_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define LSW_4_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define LSW_4_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define LSW_4_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define LSW_4_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define LSW_4_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF0 pin functionality
 * @Example
    IOCCF0_ISR();
 */
void IOCCF0_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF0 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF0 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF0_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF0 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF0_SetInterruptHandler() method.
    This handler is called every time the IOCCF0 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF0_SetInterruptHandler(IOCCF0_InterruptHandler);

*/
extern void (*IOCCF0_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF0 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF0_SetInterruptHandler() method.
    This handler is called every time the IOCCF0 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF0_SetInterruptHandler(IOCCF0_DefaultInterruptHandler);

*/
void IOCCF0_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF2 pin functionality
 * @Example
    IOCCF2_ISR();
 */
void IOCCF2_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF2 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF2 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF2 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_InterruptHandler);

*/
extern void (*IOCCF2_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF2 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler);

*/
void IOCCF2_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF4 pin functionality
 * @Example
    IOCCF4_ISR();
 */
void IOCCF4_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF4 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF4 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF4_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF4_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF4 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF4_SetInterruptHandler() method.
    This handler is called every time the IOCCF4 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF4_SetInterruptHandler(IOCCF4_InterruptHandler);

*/
extern void (*IOCCF4_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF4 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF4_SetInterruptHandler() method.
    This handler is called every time the IOCCF4 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF4_SetInterruptHandler(IOCCF4_DefaultInterruptHandler);

*/
void IOCCF4_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF6 pin functionality
 * @Example
    IOCCF6_ISR();
 */
void IOCCF6_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF6 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF6 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF6_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF6_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF6 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF6_SetInterruptHandler() method.
    This handler is called every time the IOCCF6 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF6_SetInterruptHandler(IOCCF6_InterruptHandler);

*/
extern void (*IOCCF6_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF6 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF6_SetInterruptHandler() method.
    This handler is called every time the IOCCF6 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF6_SetInterruptHandler(IOCCF6_DefaultInterruptHandler);

*/
void IOCCF6_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/