//
// Created by qw on 25-7-15.
//

#ifndef LED_1BIT_5050_H
#define LED_1BIT_5050_H

// 函数原型声明
unsigned char find_color(const char* name, unsigned char* r, unsigned char* g, unsigned char* b);
void set_color_rgb(unsigned char r, unsigned char g, unsigned char b);
void set_color(const char* color_name);
void set_color_bright(const char* color_name, unsigned char brightness);
void set_color_hex(const char *hex_color);
void set_color_hex_bright(const char *hex_color, unsigned char brightness);
void hsv2rgb(unsigned int h, unsigned char s, unsigned char v,
              unsigned char *r, unsigned char *g, unsigned char *b);
void set_color_rgb_bright(unsigned char r, unsigned char g, unsigned char b,
                             unsigned char brightness);
void breathing_effect(unsigned char r, unsigned char g, unsigned char b);
void breathing_effect_color(const char* color_name);
void rainbow_effect(void);

#endif //LED_1BIT_5050_H
