 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
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
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "dmx.h"
#include "dma.h"
#include "mcc_generated_files/system/system.h"

uint8_t rxData[COLOR_COUNT+1]; // Holds mode, then 3 bytes of data depending on the mode
uint8_t ledData[NUM_LEDS*COLOR_COUNT];
volatile uint8_t RxBuff[8];
uint8_t pwm11Fg = 0;
uint8_t pwm12Fg = 0;
uint8_t pwm21Fg = 0;
uint8_t pwm22Fg = 0;

extern uint8_t rxFg;


int a = 1;
int b = 1;
int c = 1;
int d = 1;

uint8_t red1[4] = {255, 0, 0, 0};
uint8_t orange1[4] = {252, 150, 8, 0};
uint8_t yellow1[4] = {247, 243, 22, 0};
uint8_t green1[4] = {32, 196, 14, 0};
uint8_t blue1[4] = {13, 73, 214, 0};
uint8_t nam1[4] = {32, 3, 128, 0};
uint8_t purple1[4] = {192, 12, 242, 0};

int rainbow3[8][4] = {
    {255, 0, 0, 0},      //1 red
    {252, 150, 8, 0},    //2 orange
    {247, 243, 22, 0},   //3 yellow
    {32, 196, 14, 0},    //4 green
    {13, 73, 214, 0},    //5 blue
    {32, 3, 128, 0},     //6 navy
    {192, 12, 242, 0},    //7 purple
    {0, 0, 0, 255}      //8 white
};

void setLed(uint8_t pos, led_t color){
    ledData[pos*4] = color.g;
    ledData[pos*4+1] = color.r;
    ledData[pos*4+2] = color.b;
    ledData[pos*4+3] = color.w;
}

void setAllLeds(led_t color){
    for(uint8_t i = 0; i < NUM_LEDS; i++){ // set ledData[] array to an initial color
        setLed(i, color);
    }
}

// Set entire strip to G,R,B value sent through DMX
void reactive(void){
    led_t color = {.g = rxData[1], .r = rxData[2], .b = rxData[3]};
    for(uint8_t i = 0; i < NUM_LEDS; i++){
        setLed(i, color);
    }
}

// DMX sends # of leds and 2 thresholds. This function converts that into G,R,B data
// Below thresh1, turn leds green, Between thresh1 & thresh2, leds turn yellow, above thresh2, leds turn red
void visualizer(void) {
    uint8_t leds = rxData[1];
    uint8_t thresh1 = rxData[2];
    uint8_t thresh2 = rxData[3];
    for (uint8_t i = 0; i < rxData[1]; i++) { // set color leds
        if (i < thresh1) {
            setLed(i, green);
        } else if (i < thresh2) {
            setLed(i, yellow);
        } else {
            setLed(i, red);
        }
    }
    for (uint8_t i = leds; i < NUM_LEDS; i++) { // turn off the rest of the leds
        setLed(i, off);
    }
}

void dmxToLed(void) {
    switch (rxData[0]) {
        case STANDBY:
        case REACTIVE: // DMX sends G,R,B values that the entire led strip turns to
            reactive();
            break;
    }
}

void DMXRcvCallback(uint8_t* pData, int16_t length)
{
    length = 5;
    memcpy(RxBuff, pData, length) ;
//    strcpy(RxBuff, pData) ;
}


void PWM_SetDuty(int i, uint8_t duty)
{
    // PWM 
    uint16_t period = (uint16_t)PWM1PRH << 8 | PWM1PRL;

    // Duty cycle 
    uint16_t dutyCycleValue = ((uint32_t)period * duty) / 255;

    // Duty cycle 
    if(i == 1) PWM1_16BIT_SetSlice1Output1DutyCycleRegister(dutyCycleValue);
    if(i == 2) PWM1_16BIT_SetSlice1Output2DutyCycleRegister(dutyCycleValue);
    if(i == 3) PWM2_16BIT_SetSlice1Output1DutyCycleRegister(dutyCycleValue);
    if(i == 4) PWM2_16BIT_SetSlice1Output2DutyCycleRegister(dutyCycleValue);
    
    PWM1_16BIT_LoadBufferRegisters();
}



void PWM1_16BIT_SetDuty8Bit(int i, uint8_t duty)
{
    // PWM 
    uint16_t period = (uint16_t)PWM1PRH << 8 | PWM1PRL;

    // Duty cycle 
    uint16_t dutyCycleValue = ((uint32_t)period * duty) / 255;

    // Duty cycle 
    if(i == 1) 
    {
        PWM1_16BIT_SetSlice1Output1DutyCycleRegister(dutyCycleValue);
//        pwm11Fg=1;    //for pwm problem
    }
    if(i == 2)
    {
        PWM1_16BIT_SetSlice1Output2DutyCycleRegister(dutyCycleValue);
//        pwm12Fg=1;    //for pwm problem
    }
//    PWM1_16BIT_LoadBufferRegisters();
}

void PWM2_16BIT_SetDuty8Bit(int i, uint8_t duty)
{
    // PWM
    uint16_t period = (uint16_t)PWM2PRH << 8 | PWM2PRL;

    // Duty cycle 
    uint16_t dutyCycleValue = ((uint32_t)period * duty) / 255;

    // Duty cycle
    if(i == 1)
    {
        PWM2_16BIT_SetSlice1Output1DutyCycleRegister(dutyCycleValue);
//        pwm21Fg = 1;  //for pwm problem
    }else{};
    if(i == 2)
    {
        PWM2_16BIT_SetSlice1Output2DutyCycleRegister(dutyCycleValue);
//        pwm22Fg = 1;  //for pwm problem
    }else{};

//    PWM2_16BIT_LoadBufferRegisters();
}



void rainbow(void)
{
    for(int i=0; i<8 ; i++)
    {
            
            a=255 - rainbow3[i][0];
            b=255 - rainbow3[i][1];
            c=255 - rainbow3[i][2];
            d=255 - rainbow3[i][3];
    
            PWM1_16BIT_SetDuty8Bit(2,a);    //red
            PWM1_16BIT_SetDuty8Bit(1,b);    //green
            PWM2_16BIT_SetDuty8Bit(2,c);    //blue
            PWM2_16BIT_SetDuty8Bit(1,d);    //white
            PWM1_16BIT_LoadBufferRegisters();
            PWM2_16BIT_LoadBufferRegisters();
            
//            if(U1ERRIRbits.RXBKIF == 1)break;
            
             for(int j=0; j<1000; j++)
            {
                if(U1ERRIRbits.RXBKIF == 1)
                    return;  // break ??? ?? ??
                __delay_ms(1);
            }
    }
}

/*
    Main application
*/

typedef struct {
    unsigned char r;  // 
    unsigned char g;  // 
    unsigned char b;  // 
    unsigned char w;  //
} Color;

uint8_t num=0;
int main(void)
{
    __delay_ms(1000);
//    while(U1ERRIRbits.RXBKIF);
//    __delay_ms(1000);   //wait a entire master init is complited. 
    
//    OSCENbits.PLLEN = 1;
    //setAllLeds(off);
    
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    DMX_Initialize();
    DMA_Initialize();
    
    //Rx Callback
    UART1_RxCompleteCallbackRegister(DMXRcvCallback);
    
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
    RC4 = 0;
    
    OSCENbits.PLLEN = 1;
    uint8_t isFirst = 0;
    
    while(1)
    {
        num++;
//        if(PIR4bits.U1RXIF == 1)
        {
            a=255 - RxBuff[1];
            b=255 - RxBuff[2];
            c=255 - RxBuff[3];
            d=255 - RxBuff[4];

            PWM1_16BIT_SetDuty8Bit(2,a);    //red
            PWM1_16BIT_SetDuty8Bit(1,b);    //green
            PWM2_16BIT_SetDuty8Bit(2,c);    //blue
            PWM2_16BIT_SetDuty8Bit(1,d);    //white
            
            PWM1_16BIT_LoadBufferRegisters();
            PWM2_16BIT_LoadBufferRegisters();
    //        __delay_ms(10);
        }
//        __delay_ms(50);
        if(U1ERRIRbits.RXBKIF == 0)     // Break Reception Interrupt Flag
        {
            __delay_ms(10);
            if(U1ERRIRbits.RXBKIF == 0)
            {
                isFirst = 1;
                U1ERRIEbits.RXBKIE = 0;
                rainbow();
            }

        }
        
        else
        {
            U1ERRIEbits.RXBKIE = 1;
        }
        
        if(isFirst)
        {
            INTERRUPT_GlobalInterruptDisable(); 
            __delay_ms(10);
              SYSTEM_Initialize();
            // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
            // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
            // Use the following macros to: 

            DMX_Initialize();
            DMA_Initialize();
            isFirst = 0;
            INTERRUPT_GlobalInterruptEnable(); 
        }
        
        if(rxFg)
        {
            U1ERRIEbits.RXBKIE = 1;
//            INTERRUPT_GlobalInterruptEnable();
            rxFg = 0;
        }
        
//        switch (rxData[0]) {
//            case STANDBY:
//            case REACTIVE: // DMX sends G,R,B values that the entire led strip turns to
//                reactive();
//                break;
//        }        
    }
}