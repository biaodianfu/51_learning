#ifndef INC_51_LEARNING_LCD_12864_SERIAL_H
#define INC_51_LEARNING_LCD_12864_SERIAL_H
void lcd_send_byte(unsigned char dat, unsigned char mode);
void lcd_init(void);
void lcd_clear(void);
void lcd_set_position(unsigned char row, unsigned char col);
void lcd_print(const char *str);
#endif //INC_51_LEARNING_LCD_12864_SERIAL_H
