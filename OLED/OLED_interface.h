/********************************************************************************************/
/* File:        OLED_interface.h                                                            */
/* Author:      Youssef Mostafa                                                             */
/* Description: An API to expose the driver's functions to                                  */
/* rest of the project, contains function definitions and docs.                             */
/********************************************************************************************/

/* Includes */
#include <stdbool.h>
#include "TWI_interface.h"

/* Definitions */
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

#define OLED_ADDRESS 0x3C         /* Standard OLED I2C Address */
#define OLED_SEC_ADDRESS 0x3D     /* Secondary OLED I2C Address */
#define OLED_CTL_CMD_SHOT 0x80    /* Single Command */
#define OLED_CTL_DATA_SHOT 0xC0   /* Single Data    */
#define OLED_CTL_CMD_STREAM 0x00  /* Stream Commands */
#define OLED_CTL_DATA_STREAM 0x40 /* Stream Data    */

/* Addressing modes */
#define OLED_HORIZONTAL_ADDRESSING 0x00
#define OLED_VERTICAL_ADDRESSING 0x01
#define OLED_PAGE_ADDRESSING 0x02

/* Addressing modes */
#define OLED_HORIZONTAL_ADDRESSING 0x00
#define OLED_VERTICAL_ADDRESSING 0x01
#define OLED_PAGE_ADDRESSING 0x02

/**
 * @brief Initialize I2C communication with the OLED and set up the internal configuration.
 */
void OLED_vInit(void);

/**
 * @brief Sends a command byte
 * @param u8Cmd  Command byte to be sent
 */
void OLED_vSendCmd(u8 u8Cmd);

/**
 * @brief Sends data byte
 * @param u8Data Data byte to be sent
 */
void OLED_vSendData(u8 u8Data);

/**
 * @brief Stream command bytes
 * @param pCmd  Array pointer for command bytes to be sent
 * @note The first item in the input array WILL BE REPLACED with the appropriate command byte, please make sure the data at index 0 of your array is empty or not important
 */
void OLED_vStreamCmds(u8 *pCmd, u8 u8Size);

/**
 * @brief Stream data bytes
 * @param pData  Array pointer for data bytes to be sent
 * @note The first item in the input array WILL BE REPLACED with the appropriate command byte, please make sure the data at index 0 of your array is empty or not important
 */
void OLED_vStreamData(u8 *pData, u8 u8Size);

/**
 * @brief Fills screen (Writes entire GDDRAM)
 * @param u8Byte Byte to be written for every pixel
 */
void OLED_vFill(u8 u8Byte);

/**
 * @brief Clears screen (Clears entire GDDRAM)
 */
void OLED_vClear(void);

/**
 * @brief Resets OLED memory window.
 * @param u8StartCol Index of start Colum (0 - 127)
 * @param u8EndCol Index of end Colum (0 - 127)
 * @param u8StartPage Index of start Page (0 - 7)
 * @param u8EndPage Index of end Page (0 - 7)
 */
void OLED_vSetWindow(u8 u8StartCol, u8 u8EndCol, u8 u8StartPage, u8 u8EndPage);

/**
 * @brief Resets OLED memory window.
 * @param u8StartCol Index of start Colum (0 - 127)
 * @param u8EndCol Index of end Colum (0 - 127)
 * @param u8StartPage Index of start Page (0 - 7)
 * @param u8EndPage Index of end Page (0 - 7)
 */
void OLED_vSetWindow(u8 u8StartCol, u8 u8EndCol, u8 u8StartPage, u8 u8EndPage);

/**
 * @brief Draws a horizontal line
 * @param u8x X coordinate of left terminal of line
 * @param u8y Y coordinate of left terminal of line
 * @param u8Length Number of pixels the line will be in length
 */
void OLED_vLineH(u8 u8x, u8 u8y, u8 u8Length);

/**
 * @brief Draws a vertical line
 * @param u8x X coordinate of upper left corner
 * @param u8y Y coordinate of upper left corner
 * @param u8Length Number of pixels the line will be in length
 */
void OLED_vLineV(u8 u8x, u8 u8y, u8 u8Length);

/**
 * @brief Draws a square
 * @param u8x X coordinate of upper left corner
 * @param u8y Y coordinate of upper left corner
 * @param u8Width  Number of pixels on the X axis
 * @param u8Height Number of pixels on the Y axis
 */
void OLED_vFillRectangle(u8 u8x, u8 u8y, u8 u8Width, u8 u8Height);

/**
 * @brief Draws a hollow square
 * @param u8x X coordinate of upper left corner
 * @param u8y Y coordinate of upper left corner
 * @param u8Width  Number of pixels on the X axis
 * @param u8Length Number of pixels on the Y axis
 * @param u8OutlineWidth Width of the outline
 */
void OLED_vRectangle(u8 u8x, u8 u8y, u8 u8Width, u8 u8Height, u8 u8OutlineWidth);

/**
 * @brief Draws a single pixel
 * @param u8x X coordinate of pixel
 * @param u8y Y coordinate of pixel
 */
void OLED_vPixel(u8 u8x, u8 u8y);