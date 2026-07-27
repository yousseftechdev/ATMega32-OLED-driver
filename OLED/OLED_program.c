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
    u8 buffer64[26] = {OLED_CTL_CMD_STREAM, 0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0x8D, 0x14, 0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6, 0xAF};
    OLED_vStreamCmds(buffer64, 26);
}

void OLED_vSendCmd(u8 u8Cmd)
{
    u8 buffer[2] = {OLED_CTL_CMD_SHOT, u8Cmd};
    while (TWI_bIsBusy())
        ;
    TWI_bSendData(OLED_ADDRESS, buffer, 2);
    while (TWI_bIsBusy())
        ;
}

void OLED_vSendData(u8 u8Data)
{
    u8 buffer[2] = {OLED_CTL_DATA_SHOT, u8Data};
    while (TWI_bIsBusy())
        ;
    TWI_bSendData(OLED_ADDRESS, buffer, 2);
    while (TWI_bIsBusy())
        ;
}

void OLED_vStreamCmds(u8 *pCmd, u8 u8Size)
{
    while (TWI_bIsBusy())
        ;
    pCmd[0] = OLED_CTL_CMD_STREAM;
    TWI_bSendData(OLED_ADDRESS, pCmd, u8Size);
    while (TWI_bIsBusy())
        ;
}

void OLED_vStreamData(u8 *pData, u8 u8Size)
{
    while (TWI_bIsBusy())
        ;
    pData[0] = OLED_CTL_DATA_STREAM;
    TWI_bSendData(OLED_ADDRESS, pData, u8Size);
    while (TWI_bIsBusy())
        ;
}

void OLED_vFill(u8 u8Byte)
{
    u8 buffer[129];
    buffer[0] = OLED_CTL_DATA_STREAM;
    u8 cmdArray[7] = {OLED_CTL_CMD_STREAM, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x07};
    for (u8 i = 1; i < 129; i++)
    {
        buffer[i] = u8Byte;
    }

    OLED_vStreamCmds(cmdArray, 7);

    for (u8 page = 0; page < 8; page++)
    {
        OLED_vStreamData(buffer, 129);
    }
}

void OLED_vClear(void)
{
    u8 buffer[129];
    buffer[0] = OLED_CTL_DATA_STREAM;
    u8 cmdArray[7] = {OLED_CTL_CMD_STREAM, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x07};
    for (u8 i = 1; i < 129; i++)
    {
        buffer[i] = 0x00;
    }

    OLED_vStreamCmds(cmdArray, 7);

    for (u8 page = 0; page < 8; page++)
    {
        OLED_vStreamData(buffer, 129);
    }
}

void OLED_vSquare(u8 u8Width, u8 u8Length)
{
    u8 buffer[u8Width + 1];
    buffer[0] = OLED_CTL_DATA_STREAM;
    u8 u8LengthByte = ~(255 << u8Length);
    for (u8 i = 1; i < u8Width + 1; i++)
    {
        buffer[i] = u8LengthByte;
    }
    OLED_vStreamData(buffer, u8Width + 1);
}