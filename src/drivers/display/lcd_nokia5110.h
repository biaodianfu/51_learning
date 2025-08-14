#ifndef LCD_NOKIA5110_H
#define LCD_NOKIA5110_H
void lcd_write_byte(unsigned char dat, unsigned char cmd);
void lcd_init(void);
void lcd_set_cursor(unsigned char x, unsigned char y);
void lcd_clear(void);
void lcd_write_char(unsigned char ch);
void lcd_write_string(unsigned char x, unsigned char y, char *str);
void lcd_write_number(unsigned char x, unsigned char y, unsigned int num);
void lcd_write_chinese_string(unsigned char x, unsigned char y, unsigned char ch_width, unsigned char num, unsigned char line,unsigned char line_space );


#endif //LCD_NOKIA5110_H
