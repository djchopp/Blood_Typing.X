/* 
 * File:   SPI_Helper.h
 * Author: DC
 *
 * Created on August 3, 2013, 5:42 PM
 */

#ifndef SPI_HELPER_H
#define	SPI_HELPER_H

#define SPI_CONFIG1 SPI_FOSC_8
#define SPI_CONFIG2 SPI_BUFF_OVRWRT_DISABLE
#define SPI_CONFIG3 SPI_SMPMID
#define SPI_CONFIG4 0x00
#define Sync_Mode SPI_FOSC_8
#define Bus_Mode SPI_MODE_10
#define SMP_Phase SPI_SMPMID

#define CE PORTAbits.RA2

void SPI_Init(void);
void SPI_Write(unsigned char data);
unsigned char SPI_Read(void);

#endif	/* SPI_HELPER_H */

