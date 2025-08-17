#ifndef INC_51_LEARNING_OLED_12864_I2C_H
#define INC_51_LEARNING_OLED_12864_I2C_H

void oled_write_byte(unsigned char dat, unsigned char mode);
void oled_init(void);
void oled_clear(void);
void oled_display_on(void);
void oled_display_off(void);
void oled_set_cursor(unsigned char col, unsigned char page);
void oled_display_char(unsigned char col, unsigned char page, char ch);
void oled_display_string(unsigned char col, unsigned char page, const char *str);
void oled_display_inverse(unsigned char mode);
void oled_display_turn(unsigned char mode);

#endif // INC_51_LEARNING_OLED_12864_I2C_H