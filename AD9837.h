/*
 * File:   Node.h
 * Author: DC
 *
 * Created on July 11, 2013, 10:33 AM
 */

#ifndef AD9837_H
#define	AD9837_H

#define Clear 0x00
#define D15 0x8000
#define D14 0x4000
#define D13 0x2000 //B28
#define D12 0x1000 //HLB
#define D11 0x0800 //FSEL
#define D10 0x0400 //PSEL
#define D9 0x0200 //Reserved
#define D8 0x0100 //RESET
#define D7 0x0080 //SLEEP1
#define D6 0x0040 //SLEEP12
#define D5 0x0020 //OPBITEN
#define D4 0x0010 //Reserved
#define D3 0x0008 //DIV2
#define D2 0x0004 //Reserved
#define D1 0x0002 //MODE
#define D0 0x0001 //Reserved

unsigned int AD9837_CH0_CTL_ENT();
unsigned int AD9837_CH0_CTLU_EXT();
unsigned int AD9837_FREQ0_LSB(unsigned long long freq);
unsigned int AD9837_FREQ0_MSB(unsigned long long freq);
unsigned long long AD9837_FREQ0(double freq);
void AD9837_SND_PKT(unsigned long long freq, unsigned char* packet);

#endif	/* AD9837_H */

