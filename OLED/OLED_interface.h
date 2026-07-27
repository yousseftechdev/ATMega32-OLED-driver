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
#define OLED_CTL_CMD_SHOT 0xC0    /* Control byte for sending 1 command byte */
#define OLED_CTL_DATA_SHOT 0x80   /* Control byte for sending 1 data byte */
#define OLED_CTL_CMD_STREAM 0x40  /* Control byte for sending a stream of command bytes */
#define OLED_CTL_DATA_STREAM 0x00 /* Control byte for sending a stream of data bytes */

/**
 * @brief Initialize I2C communication with the OLED and set up the internal configuration.
 */
void OLED_vInit(void);

/**
 * @brief Sends a command byte
 * @param u8Cmd  Command byte to be sent
 */
void OLED_bSendCmd(u8 u8Cmd);

/**
 * @brief Sends data byte
 * @param u8Data Data byte to be sent
 */
void OLED_bSendData(u8 u8Data);

/**
 * @brief Stream command bytes
 * @param pCmd  Array pointer for command bytes to be sent
 */
void OLED_bStreamCmds(u8 *pCmd, u8 u8Size);

/**
 * @brief Stream data bytes
 * @param pData  Array pointer for data bytes to be sent
 */
void OLED_bStreamData(u8 *pData, u8 u8Size);

/**
 * @brief Fills screen (Writes entire GDDRAM)
 * @param u8Byte Byte to be written for every pixel
 */
void OLED_vFill(u8 u8Byte);