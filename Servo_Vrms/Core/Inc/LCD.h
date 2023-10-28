/*
 * LCD.h
 *
 *  Created on: Sep 9, 2023
 *      Author: fervi
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

void lcd_init (void);

void lcd_send_cmd(char cmd);

void lcd_send_data(char data);

void lcd_send_string(char *str);

void lcd_put_cur(int row, int col);

void lcd_clear(void );

#endif /* INC_LCD_H_ */


