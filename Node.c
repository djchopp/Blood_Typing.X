/*
 * File:   lcd18f.c
 * Author: Huggie
 *
 * Created on November 6, 2012, 3:49 PM
 */

#define USE_AND_OR

#include <xc.h>
#include <p24F08KL200.h>
#include <stdio.h>
#include <spi.h>
#include <timer.h>
#include "Node.h"
#include <libpic30.h>
#include "SPI_Helper.h"
#include "AD9837.h"


#pragma config FNOSC = FRC
#pragma config MCLRE = ON


int count = 0;
unsigned long long freq = 10000;
unsigned int TimerTime = 0xFF00; //0xEDC0

/********Testing Methods*****************************/
int main(void)
{

    int i;
    unsigned char packet[10];
    //unsigned int Timer1Config = T1_ON | T1_PS_1_256 | T1_SOURCE_INT;

    TRISA=0;
    TRISB=0;

    __delay_ms(10);

    CE = 1;
    __delay_ms(10);
    SPI_Init();
    __delay_ms(10);

    //ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_1);
    //OpenTimer1(Timer1Config, TimerTime);

    while(1){

        AD9837_SND_PKT(freq,packet);
        CE = 0;
        for(i=0;i<10;i++){
            WriteSPI1(0x00);
            while(SPI1_Tx_Buf_Full);
        }
        CE = 1;
        __delay_ms(100);
        __delay_ms(100);
        __delay_ms(100);
        __delay_ms(100);
        __delay_ms(100);
        freq+=8000;
    }
    
}


void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt (void)
{
    if(freq<=1200000)
    {
        int i;
        unsigned char packet[10];

        AD9837_SND_PKT(freq,packet);

        CE = 0;
        for(i=0;i<10;i++)SPI_Write(packet[i]);
        CE = 1;

        count++;
        freq+=8000;

        T1_Clear_Intr_Status_Bit;
        WriteTimer1(0);
    }
    else if(freq>1200000){

    }
}
