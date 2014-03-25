#include "SPI_Helper.h"
#include <spi.h>

void SPI_Init(void)
{
    CloseSPI1(); // Turn off SPI modules if was previosly on
    OpenSPI1(SPI_CONFIG1, SPI_CONFIG2, SPI_CONFIG3, SPI_CONFIG4, Sync_Mode, Bus_Mode, SMP_Phase);
}


void SPI_Write(unsigned char data)
{
    WriteSPI1(data);
}

unsigned char SPI_Read(void)
{
    return ReadSPI1();
}