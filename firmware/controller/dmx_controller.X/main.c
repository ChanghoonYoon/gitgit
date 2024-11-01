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
#include "main.h"
#include "dmx.h"
#include "dma.h"
#include "mcc_generated_files/system/system.h"

uint8_t dmxData[NODES * COLOR_COUNT + 1];
volatile int16_t num = 0;

MODES_T mode;

led_t updateStandbyVals(led_t currentVals)
{
    uint8_t r = currentVals.r;
    uint8_t g = currentVals.g;
    uint8_t b = currentVals.b;
    uint8_t w = currentVals.w;

    static uint8_t init_index = 0;

    if (r == MAX_SB_VAL && g < MAX_SB_VAL && b == 0 && w == 0) // (1_yellow)
    { // increase green phase
        currentVals.g++;
    }
    else if (g == MAX_SB_VAL && r > 0 && b == 0 && w == 0) // (2_green)
    { // decrease red phase
        currentVals.r--;
    }
    else if (g == MAX_SB_VAL && b < MAX_SB_VAL && r == 0 && w == 0) // 3_chunglock)
    { // increase blue phase
        currentVals.b++;
    }
    else if (b == MAX_SB_VAL && g > 0 && r == 0 && w == 0) // 4_blue
    { // decrease green phase
        currentVals.g--;
    }
    else if (b == MAX_SB_VAL && r < MAX_SB_VAL && g == 0 && w == 0) 
    { // increase red phase
        currentVals.r++;
    }
    //-----
    else if (b == MAX_SB_VAL && r == MAX_SB_VAL && w < MAX_SB_VAL && g == 0) 
    { // increase red phase
        currentVals.w++;
    }
    else if (w == MAX_SB_VAL && b > 0 && r > 0 && g == 0) 
    { // increase red phase
        currentVals.b--;
        currentVals.r--;
    }
    
    else if (w == MAX_SB_VAL && b == 0 && r < MAX_SB_VAL && g == 0) 
    { // increase red phase
        currentVals.r++;
    }
    else if (w > 0 && b == 0 && r == MAX_SB_VAL && g == 0) 
    { // increase red phase
        currentVals.w--;
    }
    
    //------
    else if (r == MAX_SB_VAL && b > 0 && g == 0)
    { // decrease blue phase
        currentVals.b--;
    }
    else
    { // reset to a known value
        currentVals.r = 0;
        currentVals.g = 0;
        currentVals.b = MAX_SB_VAL;
        currentVals.w = MAX_SB_VAL;
    }
    return currentVals;
}

#define STANDBY_DELAY 3
led_t standbyLed = {.r = MAX_SB_VAL, .g = 0, .b = 0};

void standby(void)
{
    uint8_t index = 0;
    static uint8_t standby_delay_counter = 0;
    static led_t standbyVals[NODES] = {
        {.r = MAX_SB_VAL, .g = 0, .b = 0},
        {.r = MAX_SB_VAL, .g = (uint8_t)(MAX_SB_VAL * .85), .b = 0},
        {.r = (uint8_t)(MAX_SB_VAL * .275), .g = MAX_SB_VAL, .b = 0},
        {.r = 0, .g = (uint8_t)MAX_SB_VAL, .b = (uint8_t)(MAX_SB_VAL * .57)},
        {.r = 0, .g = (uint8_t)(MAX_SB_VAL * .57), .b = MAX_SB_VAL},
        {.r = (uint8_t)(MAX_SB_VAL * .275), .g = 0, .b = MAX_SB_VAL},
        {.r = MAX_SB_VAL, .g = 0, .b = (uint8_t)(MAX_SB_VAL * .85)},
    };
    dmxData[index++] = STANDBY;
    if (standby_delay_counter < STANDBY_DELAY)
    {
        standby_delay_counter++;
    }
    else
    {
        for (uint8_t i = 0; i < NODES; i++)
        {
            standbyVals[i] = updateStandbyVals(standbyVals[i]);
            dmxData[index++] = standbyVals[i].g;
            dmxData[index++] = standbyVals[i].r;
            dmxData[index++] = standbyVals[i].b;
            dmxData[index++] = standbyVals[i].w;
        }
        standby_delay_counter = 0;
    }
}

void reactive(void)
{
    uint8_t index = 0;
    dmxData[index++] = 0x01; // dmxData[0] = 0x01
    for (uint8_t i = 0; i < NODES; i++)
    {
        dmxData[index++] = i;
        dmxData[index++] = i;
        dmxData[index++] = i;
        dmxData[index++] = i;
    }
}

void increase_Val(void)
{
    uint8_t index = 0;
    dmxData[index++] = 0x01; // dmxData[0] = 0x01
    for (uint8_t i = 0; i < NODES; i++)
    {
        dmxData[index++] = num;
        dmxData[index++] = num;
        dmxData[index++] = num;
        dmxData[index++] = num;
    }
}

void increase_Num(void)
{
    uint8_t index = 0;
    dmxData[index++] = 0x01; // dmxData[0] = 0x01 F
    for (uint8_t i = 0; i < NODES; i++)
    {
        dmxData[index++] = i + 1;
        dmxData[index++] = i + 2;
        dmxData[index++] = i + 3;
        dmxData[index++] = i + 4;
    }
}

void reds(void)
{
    uint8_t index = 0;
    dmxData[index++] = 0x01; // dmxData[0] = 0x01
    for (uint8_t i = 0; i < NODES; i++)
    {
        dmxData[index++] = i + 1;
        dmxData[index++] = i + 2;
        dmxData[index++] = i + 3;
        dmxData[index++] = i + 4;
        if (index == 6 && index == 7 && index == 8 && index == 9)
        {
            dmxData[6] = 255;
            dmxData[7] = 255;
            dmxData[8] = 255;
            dmxData[9] = 255;
        }
    }
}

typedef struct
{
    unsigned char r; //
    unsigned char g; //
    unsigned char b; //
    unsigned char w; //
} Color;

Color arr[4] = {
    {255, 0, 255, 255}, // red
    {0, 255, 255, 255}, // green
    {255, 255, 255, 0}, // blue
    {255, 255, 0, 255}  // white
};

uint8_t red1[4] = {255, 0, 0, 0};
uint8_t orange1[4] = {252, 150, 8, 0};
uint8_t yellow1[4] = {247, 243, 22, 0};
uint8_t green1[4] = {32, 196, 14, 0};
uint8_t blue1[4] = {13, 73, 214, 0};
uint8_t nam1[4] = {32, 3, 128, 0};
uint8_t purple1[4] = {192, 12, 242, 0};

/*
    Main application
*/
uint8_t PreKey, CurKey;

uint8_t u8rotationValue;

uint8_t dim = 0;

static uint8_t isFadingOut = 0;

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

int main(void)
{
    MODES_T mode;
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    DMX_Initialize();
    DMA_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    // INTERRUPT_GlobalInterruptDisable();

    RC4 = 1; // Set tx in UART 485
    //    mode = STANDBY;
    mode = REACTIVE;
    PreKey = CurKey = RA2;
    OSCENbits.PLLEN = 1;
    //    __delay_ms(2000);

    u8rotationValue = 1;
    int go = 0;

    led_t leds[2];
    leds[2].r = MAX_SB_VAL;
    leds[2].g = 0;
    leds[2].b = 0;
    leds[2].w = 0;
    uint8_t rain = 0;
    uint8_t speed = 0;
    while (1)
    {
        CurKey = RA2;
        // test
//                if(PORTAbits.RA2 == 0)
//                {
//                    __delay_ms(1000);
//                    speed++;
//                    if(speed > 3)
//                    {
//                        speed = 0;
//                    }
//                }//for Button On/Of
        //        {
        switch (mode)
        {
        case STANDBY:
            standby();
            break;
        case REACTIVE:
            reactive();
            //                  increase_Val();
            //                  rainbow();
            //                  increase_Num();
            //                  send_rgbw();
            
            dmxData[1] = 255-leds[2].r;
            dmxData[2] = 255-leds[2].g;
            dmxData[3] = 255-leds[2].b;
            dmxData[4] = 255-leds[2].w;
            
            leds[2] = updateStandbyVals(leds[2]);
            dmxData[5] = leds[2].r;
            dmxData[6] = leds[2].g;
            dmxData[7] = leds[2].b;
            dmxData[8] = leds[2].w;
            
//                dmxData[1] = rainbow3[rain][0];
//                dmxData[2] = rainbow3[rain][1];
//                dmxData[3] = rainbow3[rain][2];
//                dmxData[4] = rainbow3[rain][3];
//                
//                dmxData[5] = rainbow3[rain+1][0];
//                dmxData[6] = rainbow3[rain+1][1];
//                dmxData[7] = rainbow3[rain+1][2];
//                dmxData[8] = rainbow3[rain+1][3];
//                rain++;
//                if(rain>7)
//                {
//                    rain = 0;
//                }
            

            //                    switch(u8rotationValue) {
            //                      case 1: // Red
            //                          if (!isFadingOut) {
            //                              // ???? ??
            //                              dmxData[5] = (uint8_t)((red1[0] * num) / 255); //r
            //                              dmxData[6] = (uint8_t)((red1[1] * num) / 255); //g
            //                              dmxData[7] = (uint8_t)((red1[2] * num) / 255); //b
            //                              dmxData[8] = 0; //w
            //                              if(num >= 255) {
            //                                  isFadingOut = 1;
            //                                  num = go;
            //                              }
            //                          } else {
            //                              // ????? ??
            //                              dmxData[5] = (uint8_t)((red1[0] * (255 - num)) / 255); //r
            //                              dmxData[6] = (uint8_t)((red1[1] * (255 - num)) / 255); //g
            //                              dmxData[7] = (uint8_t)((red1[2] * (255 - num)) / 255); //b
            //                              dmxData[8] = 0; //w
            //                              if(num >= 255) {
            //                                  u8rotationValue++;
            //                                  num = go;
            //                                  isFadingOut = 0;
            //                              }
            //                          }
            //                          break;
            //
            //                      case 2: // Orange
            //                          if (!isFadingOut) {
            //                              dmxData[5] = (uint8_t)((orange1[0] * num) / 255);
            //                              dmxData[6] = (uint8_t)((orange1[1] * num) / 255);
            //                              dmxData[7] = (uint8_t)((orange1[2] * num) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  isFadingOut = 1;
            //                                  num = go;
            //                              }
            //                          } else {
            //                              dmxData[5] = (uint8_t)((orange1[0] * (255 - num)) / 255);
            //                              dmxData[6] = (uint8_t)((orange1[1] * (255 - num)) / 255);
            //                              dmxData[7] = (uint8_t)((orange1[2] * (255 - num)) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  u8rotationValue++;
            //                                  num = go;
            //                                  isFadingOut = 0;
            //                              }
            //                          }
            //                          break;
            //
            //                      case 3: // Yellow
            //                          if (!isFadingOut) {
            //                              dmxData[5] = (uint8_t)((yellow1[0] * num) / 255);
            //                              dmxData[6] = (uint8_t)((yellow1[1] * num) / 255);
            //                              dmxData[7] = (uint8_t)((yellow1[2] * num) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  isFadingOut = 1;
            //                                  num = go;
            //                              }
            //                          } else {
            //                              dmxData[5] = (uint8_t)((yellow1[0] * (255 - num)) / 255);
            //                              dmxData[6] = (uint8_t)((yellow1[1] * (255 - num)) / 255);
            //                              dmxData[7] = (uint8_t)((yellow1[2] * (255 - num)) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  u8rotationValue++;
            //                                  num = go;
            //                                  isFadingOut = 0;
            //                              }
            //                          }
            //                          break;
            //
            //                      case 4: // Green
            //                          if (!isFadingOut) {
            //                              dmxData[5] = (uint8_t)((green1[0] * num) / 255);
            //                              dmxData[6] = (uint8_t)((green1[1] * num) / 255);
            //                              dmxData[7] = (uint8_t)((green1[2] * num) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  isFadingOut = 1;
            //                                  num = go;
            //                              }
            //                          } else {
            //                              dmxData[5] = (uint8_t)((green1[0] * (255 - num)) / 255);
            //                              dmxData[6] = (uint8_t)((green1[1] * (255 - num)) / 255);
            //                              dmxData[7] = (uint8_t)((green1[2] * (255 - num)) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  u8rotationValue++;
            //                                  num = go;
            //                                  isFadingOut = 0;
            //                              }
            //                          }
            //                          break;
            //
            //                      case 5: // Blue
            //                          if (!isFadingOut) {
            //                              dmxData[5] = (uint8_t)((blue1[0] * num) / 255);
            //                              dmxData[6] = (uint8_t)((blue1[1] * num) / 255);
            //                              dmxData[7] = (uint8_t)((blue1[2] * num) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  isFadingOut = 1;
            //                                  num = go;
            //                              }
            //                          } else {
            //                              dmxData[5] = (uint8_t)((blue1[0] * (255 - num)) / 255);
            //                              dmxData[6] = (uint8_t)((blue1[1] * (255 - num)) / 255);
            //                              dmxData[7] = (uint8_t)((blue1[2] * (255 - num)) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  u8rotationValue++;
            //                                  num = go;
            //                                  isFadingOut = 0;
            //                              }
            //                          }
            //                          break;
            //
            //                      case 6: // Navy
            //                          if (!isFadingOut) {
            //                              dmxData[5] = (uint8_t)((nam1[0] * num) / 255);
            //                              dmxData[6] = (uint8_t)((nam1[1] * num) / 255);
            //                              dmxData[7] = (uint8_t)((nam1[2] * num) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  isFadingOut = 1;
            //                                  num = go;
            //                              }
            //                          } else {
            //                              dmxData[5] = (uint8_t)((nam1[0] * (255 - num)) / 255);
            //                              dmxData[6] = (uint8_t)((nam1[1] * (255 - num)) / 255);
            //                              dmxData[7] = (uint8_t)((nam1[2] * (255 - num)) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  u8rotationValue++;
            //                                  num = go;
            //                                  isFadingOut = 0;
            //                              }
            //                          }
            //                          break;
            //
            //                      case 7: // Purple
            //                          if (!isFadingOut) {
            //                              dmxData[5] = (uint8_t)((purple1[0] * num) / 255);
            //                              dmxData[6] = (uint8_t)((purple1[1] * num) / 255);
            //                              dmxData[7] = (uint8_t)((purple1[2] * num) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  isFadingOut = 1;
            //                                  num = go;
            //                              }
            //                          } else {
            //                              dmxData[5] = (uint8_t)((purple1[0] * (255 - num)) / 255);
            //                              dmxData[6] = (uint8_t)((purple1[1] * (255 - num)) / 255);
            //                              dmxData[7] = (uint8_t)((purple1[2] * (255 - num)) / 255);
            //                              dmxData[8] = 0;
            //                              if(num >= 255) {
            //                                  u8rotationValue++;
            //                                  num = go;
            //                                  isFadingOut = 0;
            //                              }
            //                          }
            //                          break;
            //
            //                      case 8: // White
            //                          if (!isFadingOut) {
            //                              dmxData[5] = 0;
            //                              dmxData[6] = 0;
            //                              dmxData[7] = 0;
            //                              dmxData[8] = (uint8_t)((255 * num) / 255);
            //                              if(num >= 255) {
            //                                  isFadingOut = 1;
            //                                  num = go;
            //                              }
            //                          } else {
            //                              dmxData[5] = 0;
            //                              dmxData[6] = 0;
            //                              dmxData[7] = 0;
            //                              dmxData[8] = (uint8_t)((255 * (255 - num)) / 255);
            //                              if(num >= 255) {
            //                                  u8rotationValue = 1;
            //                                  num = go;
            //                                  isFadingOut = 0;
            //                              }
            //                          }
            //                          break;
            //
            //                      default:
            //                          u8rotationValue = 1;
            //                          num = 0;
            //                          isFadingOut = 0;
            //                          break;
            //                  }

            PORTB ^= 0xFF; // when transmit data, toggling leds.
            break;

        default:
            break;
        }

        if (DMAnCON0bits.DGO == 0)
        {
            DMX_sync();
            DMAnCON0bits.SIRQEN = 1;
        }
        num += 1;
        
//        switch(speed)
//        {
//        case 0:
//            __delay_ms(20);
//            break;
//        case 1:
//            __delay_ms(10);
//            break;
//        case 2:
//            __delay_ms(5);
//            break;
//        default:
//            break;
//        }
        __delay_ms(20);

        //        }

        //        if(num >= 255)
        //        {
        //            num = 0;
        //            u8rotationValue = 0;
        //        }
        //            // ?? ????
    }
}
