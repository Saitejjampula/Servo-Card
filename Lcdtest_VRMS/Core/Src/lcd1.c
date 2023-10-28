/*
 * lcd1.c
 *
 *  Created on: Sep 11, 2023
 *      Author: fervi
 */
// Function to send a command to the LCD
#include "lcd1.h"
void LCD_SendCommand(uint8_t cmd) {
    // Set RS (Register Select) low for command mode
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);

    // Send the higher nibble of the command
    HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (cmd >> 4) & 0x01);
    HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (cmd >> 5) & 0x01);
    HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (cmd >> 6) & 0x01);
    HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (cmd >> 7) & 0x01);

    // Toggle the EN (Enable) Pin
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);

    // Send the lower nibble of the command
    HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (cmd >> 0) & 0x01);
    HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (cmd >> 1) & 0x01);
    HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (cmd >> 2) & 0x01);
    HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (cmd >> 3) & 0x01);

    // Toggle the EN (Enable) Pin
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);

    // Delay for the command to complete
    HAL_Delay(2);
}

// Function to send data to the LCD
void LCD_SendData(uint8_t data) {
    // Set RS (Register Select) high for data mode
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);

    // Send the higher nibble of the data
    HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (data >> 4) & 0x01);
    HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (data >> 5) & 0x01);
    HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (data >> 6) & 0x01);
    HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (data >> 7) & 0x01);

    // Toggle the EN (Enable) Pin
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);

    // Send the lower nibble of the data
    HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (data >> 0) & 0x01);
    HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (data >> 1) & 0x01);
    HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (data >> 2) & 0x01);
    HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (data >> 3) & 0x01);

    // Toggle the EN (Enable) Pin
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);

    // Delay for data to be written
    HAL_Delay(2);
}

// Initialize the LCD
void LCD_Init(void) {
    // Initialize GPIO Pins for control and data lines
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    GPIO_InitStruct.Pin = RS_Pin | RW_Pin | E_Pin | D4_Pin | D5_Pin | D6_Pin | D7_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    HAL_GPIO_Init(LCD_GPIO_Port, &GPIO_InitStruct);

    // Initialize the LCD in 4-bit mode
    HAL_Delay(15); // Wait for power-up
    LCD_SendCommand(0x33); // Initialize
    LCD_SendCommand(0x32); // Set to 4-bit mode
    LCD_SendCommand(0x28); // 2 lines, 5x8 font
    LCD_SendCommand(0x0C); // Display on, cursor off, blink off
    LCD_SendCommand(0x01); // Clear display
    HAL_Delay(2); // Clear display delay
    LCD_SendCommand(0x06); // Entry mode: Increment cursor position, no display shift
}

// Clear the LCD display
void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(2); // Clear display delay
}

// Set the cursor position (row and column)
void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t row_offsets[] = {0x00, 0x40};
    if (row >= 2) {
        row = 1; // Avoid out-of-bounds access
    }
    LCD_SendCommand(0x80 | (col + row_offsets[row]));
}

// Print a string to the LCD
void LCD_Print(char *str) {
    while (*str) {
        LCD_SendData(*str);
        str++;
    }
}
//Printf
void LCD_Printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Format the string
    char buffer[256]; // Choose an appropriate buffer size
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    // Print the formatted string to LCD
    LCD_Print(buffer);
}

