#include "nRF24.h"
#include "Node.h"

void nRF24_Init(void)
{
    unsigned char data[5];
    SPI_Init();
    CSN = 0;

    //Transmit, CE = 0. Receive, CE = 1
    CE = 1;

    data[0] = NRF_EN_AA_USR;
    nRF24_Write_Register(NRF_EN_AA, data, 1);

    data[0] = NRF_EN_RXADDR_USR;
    nRF24_Write_Register(NRF_EN_RXADDR, data, 1);

    data[0] = NRF_SETUP_AW_USR;
    nRF24_Write_Register(NRF_SETUP_AW, data, 1);

    data[0] = NRF_SETUP_RETR_USR;
    nRF24_Write_Register(NRF_SETUP_RETR, data, 1);

    data[0] = NRF_RF_CH_USR;
    nRF24_Write_Register(NRF_RF_CH, data, 1);

    data[0] = NRF_RF_SETUP_USR;
    nRF24_Write_Register(NRF_RF_SETUP, data, 1);

    data[0] = NRF_STATUS_USR;
    nRF24_Write_Register(NRF_STATUS, data, 1);

    data[0] = NRF_RX_ADDR_P0_B0_USR;
    data[1] = NRF_RX_ADDR_P0_B1_USR;
    data[2] = NRF_RX_ADDR_P0_B2_USR;
    data[3] = NRF_RX_ADDR_P0_B3_USR;
    data[4] = NRF_RX_ADDR_P0_B4_USR;
    nRF24_Write_Register(NRF_RX_ADDR_P0, data, 5);

    data[0] = NRF_RX_ADDR_P1_B0_USR;
    data[1] = NRF_RX_ADDR_P1_B1_USR;
    data[2] = NRF_RX_ADDR_P1_B2_USR;
    data[3] = NRF_RX_ADDR_P1_B3_USR;
    data[4] = NRF_RX_ADDR_P1_B4_USR;
    nRF24_Write_Register(NRF_RX_ADDR_P1, data, 5);

    data[0] = NRF_RX_ADDR_P2_USR;
    nRF24_Write_Register(NRF_RX_ADDR_P2, data, 1);

    data[0] = NRF_RX_ADDR_P3_USR;
    nRF24_Write_Register(NRF_RX_ADDR_P3, data, 1);

    data[0] = NRF_RX_ADDR_P4_USR;
    nRF24_Write_Register(NRF_RX_ADDR_P4, data, 1);

    data[0] = NRF_RX_ADDR_P5_USR;
    nRF24_Write_Register(NRF_RX_ADDR_P5, data, 1);

    data[0] = NRF_TX_ADDR_B0_USR;
    data[1] = NRF_TX_ADDR_B1_USR;
    data[2] = NRF_TX_ADDR_B2_USR;
    data[3] = NRF_TX_ADDR_B3_USR;
    data[4] = NRF_TX_ADDR_B4_USR;
    nRF24_Write_Register(NRF_TX_ADDR, data, 5);

    data[0] = NRF_RX_PW_P0_USR;
    nRF24_Write_Register(NRF_RX_PW_P0, data, 1);

    data[0] = NRF_RX_PW_P1_USR;
    nRF24_Write_Register(NRF_RX_PW_P1, data, 1);

    data[0] = NRF_RX_PW_P2_USR;
    nRF24_Write_Register(NRF_RX_PW_P2, data, 1);

    data[0] = NRF_RX_PW_P3_USR;
    nRF24_Write_Register(NRF_RX_PW_P3, data, 1);
    
    data[0] = NRF_RX_PW_P4_USR;
    nRF24_Write_Register(NRF_RX_PW_P4, data, 1);

    data[0] = NRF_RX_PW_P5_USR;
    nRF24_Write_Register(NRF_RX_PW_P5, data, 1);

    data[0] = NRF_CONFIG_USR;
    nRF24_Write_Register(NRF_CONFIG, data, 1);
}

void nRF24_Write_Register(unsigned char reg, unsigned char * data, int size)
{
    CSN = 0;

    SPI_Write(reg | NRF_W_REGISTER);

    for(int k = 0; k<size;k++){
        SPI_Write(data[k]);
    }

    CSN = 1;
}

void nRF24_Read_Register(unsigned char reg, unsigned char * data, int size)
{
    CSN = 0;

    SPI_Write(reg | NRF_R_REGISTER);

    for(int k = 0; k<size;k++){
        data[k] = SPI_Read();
    }

    CSN = 1;
}

void nRF24_Transmit_Data(unsigned char * data, int size)
{
    CSN = 0;

    SPI_Write(NRF_W_TX_PAYLOAD);

    for(int k = 0; k<size;k++){
        SPI_Write(data[k]);
    }

    CSN = 1;

    CE = 1;
    __delay_us(10);
    CE = 0;
}

void nRF24_Receive_Data(unsigned char * data, int size)
{
    CE = 0;
    CSN = 0;

    SPI_Write(NRF_R_RX_PAYLOAD);

    for(int k = 0; k<size;k++){
        data[k] = SPI_Read();
    }

    CSN = 1;
    CE = 1;
}

unsigned char nRF24_Get_Status(void)
{
    CSN = 0;
    unsigned char data = SPI_Read();
    CSN = 1;
    return data;
}

char nRF24_IRQ_Active(void)
{
    if(IRQ == 1)return 0;
    else return 1;
}

char nRF24_IRQ_RX(void)
{
    unsigned char status = nRF24_Get_Status();

    if((status & NRF_STATUS_RX_DR) == NRF_STATUS_RX_DR)return 1;
    else return 0;
}

char nRF24_IRQ_TX(void)
{
    unsigned char status = nRF24_Get_Status();

    if((status & NRF_STATUS_TX_DS) == NRF_STATUS_TX_DS)return 1;
    else return 0;
}

void nRF24_IRQ_Clear(void)
{
    unsigned char data = NRF_STATUS_RX_DR | NRF_STATUS_TX_DS | NRF_STATUS_MAX_RT;

    nRF24_Write_Register(NRF_STATUS, &data, 1);
}