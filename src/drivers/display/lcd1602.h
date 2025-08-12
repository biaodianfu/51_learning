//
// Created by qw on 25-7-12.
//

#ifndef LCD1602_H
#define LCD1602_H
void lcd1602_init(void);
void lcd1602_write_char(unsigned char data);
void lcd1602_write_string(const char* str);
void lcd1602_set_cursor(unsigned char row, unsigned char col);
void led1602_wirte_string_by_row(const char* str, unsigned char row);
void lcd1602_clear(void);
void lcd_send_command(unsigned char command);
void lcd1602_display_number(unsigned int number);
void lcd1602_display_string(const char* str);

#endif //LCD1602_H
