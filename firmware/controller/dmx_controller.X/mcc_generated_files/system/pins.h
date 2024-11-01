/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
*/

/*
? [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA2 aliases
#define SWITCH_TRIS                 TRISAbits.TRISA2
#define SWITCH_LAT                  LATAbits.LATA2
#define SWITCH_PORT                 PORTAbits.RA2
#define SWITCH_WPU                  WPUAbits.WPUA2
#define SWITCH_OD                   ODCONAbits.ODCA2
#define SWITCH_ANS                  ANSELAbits.ANSELA2
#define SWITCH_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define SWITCH_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define SWITCH_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define SWITCH_GetValue()           PORTAbits.RA2
#define SWITCH_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define SWITCH_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define SWITCH_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define SWITCH_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define SWITCH_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define SWITCH_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define SWITCH_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define SWITCH_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RB2 aliases
#define LED_GREEN_TRIS                 TRISBbits.TRISB2
#define LED_GREEN_LAT                  LATBbits.LATB2
#define LED_GREEN_PORT                 PORTBbits.RB2
#define LED_GREEN_WPU                  WPUBbits.WPUB2
#define LED_GREEN_OD                   ODCONBbits.ODCB2
#define LED_GREEN_ANS                  ANSELBbits.ANSELB2
#define LED_GREEN_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define LED_GREEN_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define LED_GREEN_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define LED_GREEN_GetValue()           PORTBbits.RB2
#define LED_GREEN_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define LED_GREEN_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define LED_GREEN_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define LED_GREEN_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define LED_GREEN_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define LED_GREEN_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define LED_GREEN_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define LED_GREEN_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB3 aliases
#define LED_RED_TRIS                 TRISBbits.TRISB3
#define LED_RED_LAT                  LATBbits.LATB3
#define LED_RED_PORT                 PORTBbits.RB3
#define LED_RED_WPU                  WPUBbits.WPUB3
#define LED_RED_OD                   ODCONBbits.ODCB3
#define LED_RED_ANS                  ANSELBbits.ANSELB3
#define LED_RED_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define LED_RED_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define LED_RED_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define LED_RED_GetValue()           PORTBbits.RB3
#define LED_RED_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define LED_RED_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define LED_RED_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define LED_RED_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define LED_RED_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define LED_RED_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define LED_RED_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define LED_RED_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RC4 aliases
#define RS485_DE_TRIS                 TRISCbits.TRISC4
#define RS485_DE_LAT                  LATCbits.LATC4
#define RS485_DE_PORT                 PORTCbits.RC4
#define RS485_DE_WPU                  WPUCbits.WPUC4
#define RS485_DE_OD                   ODCONCbits.ODCC4
#define RS485_DE_ANS                  ANSELCbits.
#define RS485_DE_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RS485_DE_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RS485_DE_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RS485_DE_GetValue()           PORTCbits.RC4
#define RS485_DE_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RS485_DE_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RS485_DE_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define RS485_DE_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define RS485_DE_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define RS485_DE_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define RS485_DE_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define RS485_DE_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

// get/set RC5 aliases
#define IO_RC5_TRIS                 TRISCbits.TRISC5
#define IO_RC5_LAT                  LATCbits.LATC5
#define IO_RC5_PORT                 PORTCbits.RC5
#define IO_RC5_WPU                  WPUCbits.WPUC5
#define IO_RC5_OD                   ODCONCbits.ODCC5
#define IO_RC5_ANS                  ANSELCbits.
#define IO_RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define IO_RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define IO_RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define IO_RC5_GetValue()           PORTCbits.RC5
#define IO_RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define IO_RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define IO_RC5_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define IO_RC5_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define IO_RC5_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define IO_RC5_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define IO_RC5_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define IO_RC5_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

// get/set RC6 aliases
#define IO_RC6_TRIS                 TRISCbits.TRISC6
#define IO_RC6_LAT                  LATCbits.LATC6
#define IO_RC6_PORT                 PORTCbits.RC6
#define IO_RC6_WPU                  WPUCbits.WPUC6
#define IO_RC6_OD                   ODCONCbits.ODCC6
#define IO_RC6_ANS                  ANSELCbits.
#define IO_RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define IO_RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define IO_RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define IO_RC6_GetValue()           PORTCbits.RC6
#define IO_RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define IO_RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define IO_RC6_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define IO_RC6_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define IO_RC6_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define IO_RC6_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define IO_RC6_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define IO_RC6_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/