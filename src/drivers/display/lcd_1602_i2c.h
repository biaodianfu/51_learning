//
// Created by qw on 25-8-12.
//

#ifndef INC_51_LEARNING_LCD_1602_I2C_H
#define INC_51_LEARNING_LCD_1602_I2C_H
static void lcd1602_send_init_byte(unsigned char byte);
static void lcd1602_write_4bit(unsigned char data_value, unsigned char rs);
void lcd1602_cmd(unsigned char cmd);
void lcd1602_init(void);
void lcd1602_write_char(unsigned char data);
void lcd1602_write_string(const char* str);
void lcd1602_set_cursor(unsigned char row, unsigned char col);
void lcd1602_clear(void);
void lcd1602_display_number(unsigned int number);
void lcd1602_display_string(const char* str);
void lcd1602_backlight_on(void);

#endif //INC_51_LEARNING_LCD_1602_I2C_H
