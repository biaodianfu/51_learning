//
// Created by qw on 25-8-14.
//

#ifndef INC_51_LEARNING_OLED_12864_I2C_H
#define INC_51_LEARNING_OLED_12864_I2C_H
void oled_12864_init(void);
void oled_12864_clear(void);
void oled_12864_display_on(void);
void oled_12864_display_off(void);
void oled_12864_set_cursor(unsigned char page, unsigned char column);
void oled_12864_write_data(unsigned char data);
void oled_12864_write_string(unsigned char page, unsigned char column, const char *str);
void oled_12864_write_char(unsigned char page, unsigned char column, unsigned char ch);
//void oled_12864_write_number(unsigned char page, unsigned char column, unsigned int num);
//void oled_12864_write_chinese_string(unsigned char page, unsigned char column, const unsigned char *chinese_str, unsigned char len);


#endif //INC_51_LEARNING_OLED_12864_I2C_H
