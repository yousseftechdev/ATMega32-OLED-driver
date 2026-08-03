/********************************************************************************************/
/* File:        OLED_program.c                                                              */
/* Author:      Youssef Mostafa                                                             */
/* Description: A high level abstraction layer for the I2C interface to control an OLED.    */
/********************************************************************************************/

#include "OLED_interface.h"
#include "TWI_interface.h"
#include <avr/pgmspace.h>
#include <util/delay.h>

/*
   Compact 5x7 Font (ASCII 32 ' ' to 126 '~')
   Each character is 5 bytes (columns). 0 bits are off, 1 bits are on.
*/
static const u8 Font5x7[][5] PROGMEM = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 32: Space
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // 33: !
    {0x00, 0x07, 0x00, 0x07, 0x00}, // 34: "
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, // 35: #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // 36: $
    {0x23, 0x13, 0x08, 0x64, 0x62}, // 37: %
    {0x36, 0x49, 0x55, 0x22, 0x50}, // 38: &
    {0x00, 0x05, 0x03, 0x00, 0x00}, // 39: '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // 40: (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // 41: )
    {0x14, 0x08, 0x3E, 0x08, 0x14}, // 42: *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // 43: +
    {0x00, 0x50, 0x30, 0x00, 0x00}, // 44: ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // 45: -
    {0x00, 0x60, 0x60, 0x00, 0x00}, // 46: .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // 47: /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 48: 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 49: 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 50: 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 51: 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 52: 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 53: 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 54: 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 55: 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 56: 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 57: 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // 58: :
    {0x00, 0x56, 0x36, 0x00, 0x00}, // 59: ;
    {0x08, 0x14, 0x22, 0x41, 0x00}, // 60: <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // 61: =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // 62: >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // 63: ?
    {0x32, 0x49, 0x79, 0x41, 0x3E}, // 64: @
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // 65: A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // 66: B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // 67: C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // 68: D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // 69: E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // 70: F
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // 71: G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // 72: H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // 73: I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // 74: J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // 75: K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // 76: L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // 77: M
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, // 78: N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 79: O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // 80: P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // 81: Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // 82: R
    {0x46, 0x49, 0x49, 0x49, 0x31}, // 83: S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // 84: T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // 85: U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // 86: V
    {0x3F, 0x40, 0x38, 0x40, 0x3F}, // 87: W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // 88: X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // 89: Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // 90: Z
    /* TODO: Add lowercase letters */
};

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

            0x20,                       // Set Memory Addressing Mode
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
    _delay_ms(10);
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
    static u8 buffer[129];
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
    static u8 buffer[129];
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

void OLED_vLineH(u8 u8X, u8 u8Y, u8 u8Length)
{
    OLED_vFillRectangle(u8X, u8Y, u8Length, 1);
}

void OLED_vLineV(u8 u8X, u8 u8Y, u8 u8Length)
{
    OLED_vFillRectangle(u8X, u8Y, 1, u8Length);
}

void OLED_vFillRectangle(u8 u8X, u8 u8Y, u8 u8Width, u8 u8Height)
{
    static u8 buffer[129];
    buffer[0] = OLED_CTL_DATA_STREAM;
    u8 pattern;

    /* Bounds */
    if (u8X >= 128 || u8Y >= 64 || u8Width == 0 || u8Height == 0)
        return;
    if ((u16)u8X + u8Width > 128)
        u8Width = 128 - u8X;

    if ((u16)u8Y + u8Height > 64)
        u8Height = 64 - u8Y;

    u8 u8StartPage = u8Y / 8;
    u8 u8StartBit = u8Y % 8;
    u8 u8EndPage = (u8Y + u8Height - 1) / 8;
    u8 u8EndBit = (u8Y + u8Height - 1) % 8;

    for (u8 page = u8StartPage; page <= u8EndPage; page++)
    {
        pattern = 0;

        if (u8StartPage == u8EndPage)
        {
            pattern = (u8)(((1U << u8Height) - 1U) << u8StartBit);
        }
        else if (page == u8StartPage)
        {
            pattern = (u8)(0xFF << u8StartBit);
        }
        else if (page == u8EndPage)
        {
            pattern = (u8)((1U << (u8EndBit + 1)) - 1U);
        }
        else
        {
            pattern = 0xFF;
        }

        for (u8 byte = 1; byte <= u8Width; byte++)
        {
            buffer[byte] = pattern;
        }

        OLED_vSetWindow(u8X, u8X + u8Width - 1, page, page);
        OLED_vStreamData(buffer, u8Width + 1);
    }
}

void OLED_vRectangle(u8 u8X, u8 u8Y, u8 u8Width, u8 u8Height, u8 u8OutlineWidth)
{
    // Safety check
    if (u8Width <= (u8OutlineWidth * 2) || u8Height <= (u8OutlineWidth * 2))
    {
        return;
    }

    OLED_vFillRectangle(u8X, u8Y, u8OutlineWidth, u8Height); /* Left side */

    OLED_vFillRectangle(u8X + u8Width - u8OutlineWidth, u8Y, u8OutlineWidth, u8Height); /* Right side */

    OLED_vFillRectangle(u8X + u8OutlineWidth, u8Y, u8Width - (u8OutlineWidth * 2), u8OutlineWidth); /* Top */

    OLED_vFillRectangle(u8X + u8OutlineWidth, u8Y + u8Height - u8OutlineWidth,
                        u8Width - (u8OutlineWidth * 2), u8OutlineWidth); /* Bottom side*/
}

void OLED_vPixel(u8 u8X, u8 u8Y)
{
    if (u8X < 128 && u8Y < 64)
    {
        OLED_vFillRectangle(u8X, u8Y, 1, 1);
    }
}

void OLED_vChar(u8 u8X, u8 u8Y, s8 s8C)
{
    if (u8X >= 128 || u8Y >= 64)
        return;

    u8 buffer[6];
    bool bHasData;

    u8 u8FontIdx = (s8C < ' ' || s8C > 'Z' ? 0 : (s8C - ' '));

    u8 u8StartPage = u8Y / 8;
    u8 u8BitOffeset = u8Y % 8;
    u8 u8CurrentPage = 0;
    u8 u8CharCol;
    u8 u8ByteToDraw;

    u8 u8PagesToDraw = (u8BitOffeset == 0) ? 1 : 2;

    for (u8 page = 0; page < u8PagesToDraw; page++)
    {
        u8CurrentPage = u8StartPage + page;
        if (u8CurrentPage > 7)
            break;

        buffer[0] = OLED_CTL_DATA_STREAM;
        bHasData = false;

        for (u8 col = 0; col < 5; col++)
        {
            u8CharCol = pgm_read_byte(&(Font5x7[u8FontIdx][col]));
            u8ByteToDraw = 0;

            if (page == 0)
            {
                u8ByteToDraw = u8CharCol << u8BitOffeset;
            }
            else
            {
                u8ByteToDraw = u8CharCol >> (8 - u8BitOffeset);
            }

            if (u8ByteToDraw != 0)
                bHasData = true;
            buffer[col + 1] = u8ByteToDraw;
        }

        if (bHasData || page == 0)
        {
            OLED_vSetWindow(u8X, u8X + 4, u8CurrentPage, u8CurrentPage);
            OLED_vStreamData(buffer, 6);
        }
    }
}

void OLED_vText(u8 u8X, u8 u8Y, const s8 *str)
{
    while (*str)
    {
        OLED_vChar(u8X, u8Y, *str);
        u8X += 6;
        if (u8X > 123)
            break;
        str++;
    }
}

void OLED_vFontShowcase(void)
{
    char character = 32;
    for (u8 i = 0; i < 64; i += 8)
    {
        for (u8 j = 0; j < 123; j += 6)
        {
            OLED_vChar(j, i, character);
            character++;
            if (character >= 91)
                break;
        }
        if (character >= 91)
            break;
    }
}

void OLED_vCircle(s8 s8X0, s8 s8Y0, u8 u8Radius)
{
    s8 s8X = u8Radius;
    s8 s8Y = 0;
    s8 s8Error = 0;

    while (s8X >= s8Y)
    {
        OLED_vPixel(s8X0 + s8X, s8Y0 + s8Y);
        OLED_vPixel(s8X0 + s8Y, s8Y0 + s8X);
        OLED_vPixel(s8X0 - s8Y, s8Y0 + s8X);
        OLED_vPixel(s8X0 - s8X, s8Y0 + s8Y);
        OLED_vPixel(s8X0 - s8X, s8Y0 - s8Y);
        OLED_vPixel(s8X0 - s8Y, s8Y0 - s8X);
        OLED_vPixel(s8X0 + s8Y, s8Y0 - s8X);
        OLED_vPixel(s8X0 + s8X, s8Y0 - s8Y);

        s8Y++;
        if (s8Error <= 0)
        {
            s8Error += 2 * s8Y + 1;
        }

        if (s8Error > 0)
        {
            s8X--;
            s8Error -= 2 * s8X + 1;
        }
    }
}

void OLED_vScrollH(bool bDirection, u8 u8StartPage, u8 u8EndPage, u8 u8Speed)
{
    u8 cmd[8] =
    {
        OLED_CTL_CMD_STREAM,
        (bDirection == OLED_SCROLL_RIGHT) ? 0x26 : 0x27,
        0x00, // Dummy byte
        (u8)(u8StartPage & 0x07),
        (u8)(u8Speed & 0x07),
        (u8)(u8EndPage & 0x07),
        0x00, // Dummy byte
        0xFF  // Dummy byte
    };
    OLED_vStreamCmds(cmd, 8);
    OLED_vSendCmd(0x2F);
}

void OLED_vScrollStop(void) {
    OLED_vSendCmd(0x2E);
}