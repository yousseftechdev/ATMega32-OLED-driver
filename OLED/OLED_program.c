/********************************************************************************************/
/* File:        OLED_program.c                                                              */
/* Author:      Youssef Mostafa                                                             */
/* Description: A high level abstraction layer for the I2C interface to control an OLED.    */
/********************************************************************************************/

#include "OLED_interface.h"
#include "TWI_interface.h"

void OLED_vInit(void)
{
    TWI_vInit(400000, TWI_ENABLE_INTERRUPT);
}

void OLED_bSendCmd(u8 u8Cmd)
{
    u8 buffer[2] = {OLED_CTL_CMD_SHOT, u8Cmd};
    while (TWI_bIsBusy())
        ;
    TWI_bSendData(OLED_ADDRESS, buffer, 2);
    while (TWI_bIsBusy())
        ;
}

void OLED_bSendData(u8 u8Data)
{
    u8 buffer[2] = {OLED_CTL_DATA_SHOT, u8Data};
    while (TWI_bIsBusy())
        ;
    TWI_bSendData(OLED_ADDRESS, buffer, 2);
    while (TWI_bIsBusy())
        ;
}

void OLED_bStreamCmds(u8 *pCmd, u8 u8Size)
{
    while (TWI_bIsBusy())
        ;
    TWI_vSetAutoStop(TWI_MANUAL_STOP);
    TWI_bSendDataShot(OLED_ADDRESS, OLED_CTL_CMD_STREAM);
    TWI_bSendData(OLED_ADDRESS, pCmd, u8Size);
    TWI_vEndTransmission();
    TWI_vSetAutoStop(TWI_AUTO_STOP);
    while (TWI_bIsBusy())
        ;
}

void OLED_bStreamData(u8 *pData, u8 u8Size)
{
    while (TWI_bIsBusy())
        ;
    TWI_vSetAutoStop(TWI_MANUAL_STOP);
    TWI_bSendDataShot(OLED_ADDRESS, OLED_CTL_DATA_STREAM);
    TWI_bSendData(OLED_ADDRESS, pData, u8Size);
    TWI_vEndTransmission();
    TWI_vSetAutoStop(TWI_AUTO_STOP);
    while (TWI_bIsBusy())
        ;
}

void OLED_vFill(u8 u8Byte)
{
    u8 buffer[128];

    for (u8 i = 0; i < 128; i++)
    {
        buffer[i] = u8Byte;
    }

    OLED_bStreamCmds((u8 *){0x21, 0x00, 0x7F, 0x22, 0x00, 0x07}, 6);

    for (u8 page = 0; page < 8; page++)
    {
        OLED_bStreamData(buffer, 128);
    }
}