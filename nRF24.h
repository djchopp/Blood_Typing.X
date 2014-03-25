/* 
 * File:   NRF24L01P.h
 * Author: DC
 *
 * Created on July 17, 2013, 7:47 PM
 */

#ifndef NRF24_H
#define	NRF24_H

#include <p18f2550.h>
#include <stdio.h>
#include "SPI_Helper.h"

#define CSN PORTCbits.RC1
#define CE PORTCbits.RC2
#define IRQ PORTCbits.RC6


/*Commands*/
#define NRF_R_REGISTER          0x00
#define NRF_W_REGISTER          0x20
#define NRF_R_RX_PAYLOAD        0x61
#define NRF_W_TX_PAYLOAD        0xA0
#define NRF_FLUSH_TX            0xE1
#define NRF_FLUSH_RX            0xE2
#define NRF_REUSE_TX_PL         0xE3
#define NRF_NOP                 0xFF

/*Registers*/
#define NRF_CONFIG              0x00
#define NRF_EN_AA               0x01
#define NRF_EN_RXADDR           0x02
#define NRF_SETUP_AW            0x03
#define NRF_SETUP_RETR          0x04
#define NRF_RF_CH               0x05
#define NRF_RF_SETUP            0x06
#define NRF_STATUS              0x07
#define NRF_OBSERVE_TX          0x08
#define NRF_RPD                 0x09
#define NRF_RX_ADDR_P0          0x0A
#define NRF_RX_ADDR_P1          0x0B
#define NRF_RX_ADDR_P2          0x0C
#define NRF_RX_ADDR_P3          0x0D
#define NRF_RX_ADDR_P4          0x0E
#define NRF_RX_ADDR_P5          0x0F
#define NRF_TX_ADDR             0x10
#define NRF_RX_PW_P0            0x11
#define NRF_RX_PW_P1            0x12
#define NRF_RX_PW_P2            0x13
#define NRF_RX_PW_P3            0x14
#define NRF_RX_PW_P4            0x15
#define NRF_RX_PW_P5            0x16
#define NRF_FIFO_STATUS         0x17

/*Register Default Values*/
#define NRF_CONFIG_DEF          0x08
#define NRF_EN_AA_DEF           0x3F
#define NRF_EN_RXADDR_DEF       0x03
#define NRF_SETUP_AW_DEF        0x03
#define NRF_SETUP_RETR_DEF      0x03
#define NRF_RF_CH_DEF           0x02
#define NRF_RF_SETUP_DEF        0x0F
#define NRF_STATUS_DEF          0x0E
#define NRF_OBSERVE_TX_DEF      0x00
#define NRF_RPD_DEF             0x00
#define NRF_RX_ADDR_P0_B0_DEF	0xE7
#define NRF_RX_ADDR_P0_B1_DEF	0xE7
#define NRF_RX_ADDR_P0_B2_DEF	0xE7
#define NRF_RX_ADDR_P0_B3_DEF	0xE7
#define NRF_RX_ADDR_P0_B4_DEF	0xE7
#define NRF_RX_ADDR_P1_B0_DEF	0xC2
#define NRF_RX_ADDR_P1_B1_DEF	0xC2
#define NRF_RX_ADDR_P1_B2_DEF	0xC2
#define NRF_RX_ADDR_P1_B3_DEF	0xC2
#define NRF_RX_ADDR_P1_B4_DEF   0xC2
#define NRF_RX_ADDR_P2_DEF      0xC3
#define NRF_RX_ADDR_P3_DEF      0xC4
#define NRF_RX_ADDR_P4_DEF      0xC5
#define NRF_RX_ADDR_P5_DEF      0xC6
#define NRF_TX_ADDR_B0_DEF      0xE7
#define NRF_TX_ADDR_B1_DEF      0xE7
#define NRF_TX_ADDR_B2_DEF      0xE7
#define NRF_TX_ADDR_B3_DEF      0xE7
#define NRF_TX_ADDR_B4_DEF      0xE7
#define NRF_RX_PW_P0_DEF        0x00
#define NRF_RX_PW_P1_DEF        0x00
#define NRF_RX_PW_P2_DEF        0x00
#define NRF_RX_PW_P3_DEF        0x00
#define NRF_RX_PW_P4_DEF        0x00
#define NRF_RX_PW_P5_DEF        0x00
#define NRF_FIFO_STATUS_DEF     0x11

/*Register Settings*/
//CONFIG register bitwise definitions
#define NRF_CONFIG_RESERVED	0x80
#define	NRF_CONFIG_MASK_RX_DR	0x40
#define	NRF_CONFIG_MASK_TX_DS	0x20
#define	NRF_CONFIG_MASK_MAX_RT	0x10
#define	NRF_CONFIG_EN_CRC	0x08
#define	NRF_CONFIG_CRCO		0x04
#define	NRF_CONFIG_PWR_UP	0x02
#define	NRF_CONFIG_PRIM_RX	0x01

//STATUS register bitwise definitions
#define NRF_STATUS_RESERVED			0x80
#define NRF_STATUS_RX_DR			0x40
#define NRF_STATUS_TX_DS			0x20
#define NRF_STATUS_MAX_RT			0x10
#define NRF_STATUS_RX_P_NO			0x0E
#define NRF_STATUS_RX_P_NO_RX_FIFO_NOT_EMPTY	0x0E
#define NRF_STATUS_RX_P_NO_UNUSED		0x0C
#define NRF_STATUS_RX_P_NO_5                    0x0A
#define NRF_STATUS_RX_P_NO_4			0x08
#define NRF_STATUS_RX_P_NO_3			0x06
#define NRF_STATUS_RX_P_NO_2			0x04
#define NRF_STATUS_RX_P_NO_1			0x02
#define NRF_STATUS_RX_P_NO_0			0x00
#define NRF_STATUS_TX_FULL                  0x01

/*Register User Values*/
#define NRF_CONFIG_USR          (NRF_CONFIG_DEF | NRF_CONFIG_PRIM_RX | NRF_CONFIG_PWR_UP)
#define NRF_EN_AA_USR           0x00
#define NRF_EN_RXADDR_USR       NRF_EN_RXADDR_DEF
#define NRF_SETUP_AW_USR        NRF_SETUP_AW_DEF
#define NRF_SETUP_RETR_USR      NRF_SETUP_RETR_DEF
#define NRF_RF_CH_USR           NRF_RF_CH_DEF
#define NRF_RF_SETUP_USR        NRF_RF_SETUP_DEF
#define NRF_STATUS_USR          NRF_STATUS_DEF
#define NRF_RX_ADDR_P0_B0_USR	NRF_RX_ADDR_P0_B0_DEF
#define NRF_RX_ADDR_P0_B1_USR	NRF_RX_ADDR_P0_B1_DEF
#define NRF_RX_ADDR_P0_B2_USR	NRF_RX_ADDR_P0_B2_DEF
#define NRF_RX_ADDR_P0_B3_USR	NRF_RX_ADDR_P0_B3_DEF
#define NRF_RX_ADDR_P0_B4_USR	NRF_RX_ADDR_P0_B4_DEF
#define NRF_RX_ADDR_P1_B0_USR	NRF_RX_ADDR_P1_B0_DEF
#define NRF_RX_ADDR_P1_B1_USR	NRF_RX_ADDR_P1_B1_DEF
#define NRF_RX_ADDR_P1_B2_USR	NRF_RX_ADDR_P1_B2_DEF
#define NRF_RX_ADDR_P1_B3_USR	NRF_RX_ADDR_P1_B3_DEF
#define NRF_RX_ADDR_P1_B4_USR   NRF_RX_ADDR_P1_B4_DEF
#define NRF_RX_ADDR_P2_USR      NRF_RX_ADDR_P2_DEF
#define NRF_RX_ADDR_P3_USR      NRF_RX_ADDR_P3_DEF
#define NRF_RX_ADDR_P4_USR      NRF_RX_ADDR_P4_DEF
#define NRF_RX_ADDR_P5_USR      NRF_RX_ADDR_P5_DEF
#define NRF_TX_ADDR_B0_USR      NRF_TX_ADDR_B0_DEF
#define NRF_TX_ADDR_B1_USR      NRF_TX_ADDR_B1_DEF
#define NRF_TX_ADDR_B2_USR      NRF_TX_ADDR_B2_DEF
#define NRF_TX_ADDR_B3_USR      NRF_TX_ADDR_B3_DEF
#define NRF_TX_ADDR_B4_USR      NRF_TX_ADDR_B4_DEF
#define NRF_RX_PW_P0_USR        0x01
#define NRF_RX_PW_P1_USR        NRF_RX_PW_P1_DEF
#define NRF_RX_PW_P2_USR        NRF_RX_PW_P2_DEF
#define NRF_RX_PW_P3_USR        NRF_RX_PW_P3_DEF
#define NRF_RX_PW_P4_USR        NRF_RX_PW_P4_DEF
#define NRF_RX_PW_P5_USR        NRF_RX_PW_P5_DEF
#define NRF_FIFO_STATUS_USR     NRF_FIFO_STATUS_DEF


/*Prototypes*/
void nRF24_Init(void);
void nRF24_Write_Register(unsigned char reg, unsigned char * data, int size);
void nRF24_Read_Register(unsigned char reg, unsigned char * data, int size);
void nRF24_Transmit_Data(unsigned char * data, int size);
void nRF24_Receive_Data(unsigned char * data, int size);
unsigned char nRF24_Get_Status(void);
char nRF24_IRQ_Active(void);
char nRF24_IRQ_RX(void);
char nRF24_IRQ_TX(void);
void nRF24_IRQ_Clear(void);

#endif	/* NRF24_H */

