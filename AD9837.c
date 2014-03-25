#include <xc.h>
#include <stdio.h>
#include <spi.h>
#include "AD9837.h"

unsigned int AD9837_CH0_CTL_ENT(){
    return Clear|D13|D8;
}

unsigned int AD9837_CH0_CTL_EXT(){
    return Clear|D13;
}

unsigned int AD9837_FREQ0_LSB(unsigned long long freq){
    unsigned long long final = freq;
    return final;
}

unsigned int AD9837_FREQ0_MSB(unsigned long long freq){
    unsigned long long final = 16000000/268435456*freq;
    return final>>16;
}

unsigned long long AD9837_FREQ0(double freq){
    double final = (268435456*freq)/16000000;
    return (unsigned long long)final;
}

void AD9837_SND_PKT(unsigned long long freq, unsigned char* packet){
    unsigned int words[5];
    unsigned long long freqPack = AD9837_FREQ0(freq);

    words[0] = AD9837_CH0_CTL_ENT();
    words[1] = (unsigned int)((freqPack&0x3FFF)|0x4000);
    words[2] = (unsigned int)(((freqPack>>14)&0x3FFF)|0x4000);
    words[3] = 0xC000;
    words[4] = AD9837_CH0_CTL_EXT();

    packet[0] = (words[0]&0xFF00)>>8;
    packet[1] = words[0]&0x00FF;
    packet[2] = (words[1]&0xFF00)>>8;
    packet[3] = words[1]&0x00FF;
    packet[4] = (words[2]&0xFF00)>>8;
    packet[5] = words[2]&0x00FF;
    packet[6] = (words[3]&0xFF00)>>8;
    packet[7] = words[3]&0x00FF;
    packet[8] = (words[4]&0xFF00)>>8;
    packet[9] = words[4]&0x00FF;

}
