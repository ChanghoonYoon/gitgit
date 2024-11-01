/*
 * File:   dmx.c
 * Author: rnd
 *
 * Created on September 17, 2024, 8:55 PM
 */
#include <xc.h>
#include "main.h"
#include "mcc_generated_files/uart/uart1.h"
#define NODE 2
void DMX_Initialize(void)
{
    //UART module settings 
    U1CON0bits.MODE = 0b1010; //Select DMX mode
    U1CON0bits.TXEN = 0; //Disable transmitter 
    U1CON0bits.RXEN = 1; //Enable receiver
    U1CON2bits.RXPOL = 0; //Standard polarity, RX pin will idle high 
    U1CON2bits.STP = 0b10; //Recevie and verify 2 stop bits 
    
    U1ERRIE = 0x0E;
    U1FIFO = 0x20;
    
    //DMX data packet settings
    U1P1 = 0x00; //Not used in DMX receiver 
    U1P2 = ((NODE-1)*COLOR_COUNT); //Address of first byte of interest
    U1P3 = (NODE-1)*COLOR_COUNT + (COLOR_COUNT-1); //Address of last byte of interest
    // Baud rate generator settings 
    U1CON0bits.U1BRGS = 1; //High speed baud generation
    U1BRG = 0x3F; //Value for U1BRG for Fosc = 64MHz 

    //PPS settings for RX functionality on pin RC5
    //ANSELCbits.ANSELC7 = 0; //Make RC7 a digital I/O
    TRISCbits.TRISC5 = 1; //Make RC5 an input 
     U1RXPPS = 0x15; //Assign RX functionality to RC5
    U1ON = 0x01; //Turn on UART module
    
    PIE4bits.U1EIE = 1;    
}
