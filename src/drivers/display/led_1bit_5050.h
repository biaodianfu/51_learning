//
// Created by qw on 25-7-15.
//

#ifndef INC_51_LEARNING_LED_1BIT_5050_H
#define INC_51_LEARNING_LED_1BIT_5050_H


// 基础函数声明
// 函数原型声明
unsigned char find_color(const char* name, unsigned char* r, unsigned char* g, unsigned char* b);
void set_color_rgb(unsigned char r, unsigned char g, unsigned char b);
void set_color(const char* color_name);
void set_color_bright(const char* color_name, unsigned char brightness);
void set_color_hex(const char *hex_color);
void set_color_hex_bright(const char *hex_color, unsigned char brightness);

#endif //INC_51_LEARNING_LED_1BIT_5050_H
