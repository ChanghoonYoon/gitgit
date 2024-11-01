/*
 * File:   dmx.c
 * Author: rnd
 *
 * Created on September 17, 2024, 8:54 PM
 */
#include <xc.h>
#include "main.h"
#include "dmx.h"
#include "mcc_generated_files/uart/uart1.h"

void DMX_Initialize(void)
{
    //UART module settings
    U1CON0bits.MODE = 0b1010; //Select DMX mod
    U1CON0bits.TXEN = 1; //Enable transmitter
    U1CON0bits.RXEN = 0; //Disable receiver
    U1CON2bits.TXPOL = 0; //Standard polarity, TX pin will idle high
    U1CON2bits.STP = 0x2; //2 stop bits    
    
    U1ERRIR = 0x00;
    U1ERRIE = 0x00;
    U1UIR = 0x00;
    U1FIFO = 0x01;
    
    //DMX data packet settings
    U1P1 = (NODES * COLOR_COUNT) - 1; //Total number of data bytes - 1
    U1P2 = 0x00; //Not used in DMX controller
    U1P3 = 0x00; //Not used in DMX controller
 
    // Baud rate generator settings 
    U1CON0bits.U1BRGS = 1; //High speed baud generation
    U1BRG = 0x3F; //Value for U1BRG for Fosc = 64MHz
    U1RXB = 0x00;
    U1TXB = 0x00;
    
    //PPS settings for TX functionality on pin RC6 
    //ANSELCbits.ANSELC6 = 0; //Make RC6 a digital I/O
    TRISCbits.TRISC6 = 0; //Make RC6 an output 
    RC6PPS = 0x15; //Assign TX functionality to RC6
    U1ON = 0x01; //Turn on UART module

    U1TXCHK = 0x00;
    U1RXCHK = 0x00;    
}

// Ensures synchronization between DMX hardware & software
void DMX_sync(void){
    U1CON0bits.TXEN = 0; while(U1CON0bits.TXEN != 0);
    U1CON0bits.TXEN = 1;
}

void DMX_send_byte(uint8_t data){
    U1TXB = data;  
    while(U1TXMTIF==0); // wait for byte to finish sending
}

void DMX_send_bytes(uint8_t *data, uint8_t len){
    for(uint8_t i = 0; i < len; i++){
        DMX_send_byte(data[i]);
    }
}

void DMX_transsmision(uint8_t start_code, uint8_t *data, uint8_t data_len){
    DMX_send_byte(start_code);
    DMX_send_bytes(data, data_len);
    DMX_sync();
}
