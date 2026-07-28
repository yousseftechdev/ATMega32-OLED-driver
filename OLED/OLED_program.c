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
    u8 buffer64[26] =
        {
            OLED_CTL_CMD_STREAM,
            0xAE, // Display OFF

            0xD5, // Set Display Clock Divide Ratio
            0x80, // Default ratio

            0xA8, // Set Multiplex Ratio
            0x3F, // 1/64 duty (for 64px height)

            0xD3, // Set Display Offset
            0x00, // No offset

            0x40, // Set display start line to 0

            0x8D, // Charge Pump Setting
            0x14, // Enable Charge Pump (CRITICAL for brightness)

            0x20,                 // Set Memory Addressing Mode
            OLED_HORIZONTAL_ADDRESSING, // DEFAULT = OLED_PAGE_ADDRESSING

            0xA1, // Segment Re-map (Column 127 mapped to SEG0)
            0xC8, // COM Output Scan Direction (Remapped)
            // Note: If your screen is upside down or mirrored, toggle A1<->A0 and C8<->C0

            0xDA, // Set COM Pins Hardware Configuration
            0x12, // Alternative COM pin config (for 128x64)

            0x81, // Set Contrast Control
            0xCF, // Medium-High contrast

            0xD9, // Set Pre-charge Period
            0xF1,

            0xDB, // Set VCOMH Deselect Level
            0x40,

            0xA4, // Entire Display ON (Resume to RAM content)

            0xA6, // Normal Display (Not Inverse)

            0xAF // Display ON
        };
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

    OLED_vSetWindow(0x00, 0x7F, 0x00, 0x07);

    for (u8 i = 1; i < 129; i++)
    {
        buffer[i] = u8Byte;
    }

    for (u8 page = 0; page < 8; page++)
    {
        OLED_vStreamData(buffer, 129);
    }
}

void OLED_vClear(void)
{
    u8 buffer[129];
    buffer[0] = OLED_CTL_DATA_STREAM;
    OLED_vSetWindow(0x00, 0x7F, 0x00, 0x07);
    for (u8 i = 1; i < 129; i++)
    {
        buffer[i] = 0x00;
    }

    for (u8 page = 0; page < 8; page++)
    {
        OLED_vStreamData(buffer, 129);
    }
}

void OLED_vSetWindow(u8 u8StartCol, u8 u8EndCol, u8 u8StartPage, u8 u8EndPage)
{
    u8 cmd[7] = {
        OLED_CTL_CMD_STREAM,
        0x21,
        u8StartCol & 0x7F,
        u8EndCol & 0x7F,
        0x22,
        u8StartPage & 0x07,
        u8EndPage & 0x07};

    OLED_vStreamCmds(cmd, 7);
}

void OLED_vSquare(u8 u8Width, u8 u8Length)
{
    u8 buffer[129];
    u8 pattern = 0;

    if (u8Width > 127)
        u8Width = 127;

    if (u8Length > 8)
        u8Length = 8;

    for (u8 i = 0; i < u8Length; i++)
    {
        pattern |= (u8)(1U << i);
    }

    buffer[0] = OLED_CTL_DATA_STREAM;
    for (u8 i = 1; i < 129; i++)
    {
        buffer[i] = 0x00;
    }

    for (u8 i = 1; i <= u8Width; i++)
    {
        buffer[i] = pattern;
    }

    OLED_vSetWindow(0, u8Width, 0, 0);
    OLED_vStreamData(buffer, u8Width + 1);
}