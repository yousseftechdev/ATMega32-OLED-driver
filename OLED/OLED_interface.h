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
 */
void OLED_vStreamCmds(u8 *pCmd, u8 u8Size);

/**
 * @brief Stream data bytes
 * @param pData  Array pointer for data bytes to be sent
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
 * @brief Draws a square with the current cursor position being the top right corner of the square
 * @param u8Width  Number of pixels on the X axis
 * @param u8Length Number of pixels on the Y axis
 */
void OLED_vSquare(u8 u8Width, u8 u8Length);