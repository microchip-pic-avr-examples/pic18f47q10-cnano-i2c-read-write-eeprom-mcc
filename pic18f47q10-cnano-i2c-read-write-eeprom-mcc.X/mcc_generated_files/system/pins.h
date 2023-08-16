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
 * @version Driver Version  3.1.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

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

// get/set RB1 aliases
#define SCL_TRIS                 TRISBbits.TRISB1
#define SCL_LAT                  LATBbits.LATB1
#define SCL_PORT                 PORTBbits.RB1
#define SCL_WPU                  WPUBbits.WPUB1
#define SCL_OD                   ODCONBbits.ODCB1
#define SCL_ANS                  ANSELBbits.ANSELB1
#define SCL_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define SCL_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define SCL_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define SCL_GetValue()           PORTBbits.RB1
#define SCL_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define SCL_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define SCL_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define SCL_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define SCL_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define SCL_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 aliases
#define SDL_TRIS                 TRISBbits.TRISB2
#define SDL_LAT                  LATBbits.LATB2
#define SDL_PORT                 PORTBbits.RB2
#define SDL_WPU                  WPUBbits.WPUB2
#define SDL_OD                   ODCONBbits.ODCB2
#define SDL_ANS                  ANSELBbits.ANSELB2
#define SDL_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define SDL_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define SDL_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define SDL_GetValue()           PORTBbits.RB2
#define SDL_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define SDL_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define SDL_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define SDL_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define SDL_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define SDL_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define SDL_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define SDL_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RD0 aliases
#define TX_TRIS                 TRISDbits.TRISD0
#define TX_LAT                  LATDbits.LATD0
#define TX_PORT                 PORTDbits.RD0
#define TX_WPU                  WPUDbits.WPUD0
#define TX_OD                   ODCONDbits.ODCD0
#define TX_ANS                  ANSELDbits.ANSELD0
#define TX_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define TX_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define TX_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define TX_GetValue()           PORTDbits.RD0
#define TX_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define TX_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define TX_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define TX_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define TX_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define TX_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define TX_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define TX_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set RD1 aliases
#define RX_TRIS                 TRISDbits.TRISD1
#define RX_LAT                  LATDbits.LATD1
#define RX_PORT                 PORTDbits.RD1
#define RX_WPU                  WPUDbits.WPUD1
#define RX_OD                   ODCONDbits.ODCD1
#define RX_ANS                  ANSELDbits.ANSELD1
#define RX_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define RX_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define RX_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define RX_GetValue()           PORTDbits.RD1
#define RX_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define RX_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define RX_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define RX_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define RX_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define RX_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define RX_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

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