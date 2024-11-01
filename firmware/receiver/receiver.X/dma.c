/*
 * File:   dma.c
 * Author: rnd
 *
 * Created on September 17, 2024, 8:54 PM
 */
#include <xc.h>
#include "main.h"
#include "dmx.h"
#include "dma.h"

extern uint8_t rxData[COLOR_COUNT+1]; // Holds mode, then 3 bytes of data depending on the mode

void DMA_Initialize(void){
    // DMA setup for DMX (UART1)
    
    // Select DMA Instance 0 for DMX (UART))
    DMASELECT = 0x00;
    
    // DMA moves data from the RX buffer to the data array
    DMAnSSA = (uint24_t)&U1RXB;
    DMAnDSA = (uint16_t)&rxData;
    
    DMAnCON1bits.SMR = 0x00; // Source is in SFR/GPR data space (location of data memory))
    //DMAnCON1bits.DSTP = 1; // Don't transmit more data when a transmission finishes
    
    DMAnCON1bits.SMODE = 0x00; // Source ptr stays the same after each transfer (always points to the RX buffer)
    DMAnCON1bits.DMODE = 0x01; // Dest ptr incremements after each transfer to iterate through array
    
    // Source is always 1 byte
    DMAnSSZ = 0x01;
    DMAnDSZ = (COLOR_COUNT+1); // Destination is 5 bytes
    
    // Enable hardware trigger for starting DMA transfer
    DMAnSIRQ = IRQ_U1RX;
    
    DMAnCON0bits.SIRQEN = 1;
    DMAnCON0bits.EN = 1;
}
