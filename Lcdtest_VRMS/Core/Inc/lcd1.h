/*
 * lcd1.h
 *
 *  Created on: Sep 11, 2023
 *      Author: fervi
 */

#ifndef SRC_LCD1_H_
#define SRC_LCD1_H_

#include "main.h"
#include "stdio.h"
#include <stdarg.h>
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);
void LCD_Printf(const char *format, ...) ;
#endif /* SRC_LCD1_H_ */


