// led_1bit_5050.h
#include "led_1bit_5050.h"
#include "configs/led_1bit_5050_config.h"
#include "utils/delay.h"
#include <string.h> // 为了使用标准字符串函数

// SDCC特定的ROM存储关键字
#define ROM __code

// 颜色定义结构（存储在ROM中）
typedef struct {
    const char * color_name; // 名称字符串
    unsigned char r;
    unsigned char g;
    unsigned char b;
} ColorDef;

// 颜色表（存放在程序存储器）
const ROM ColorDef color_table[] = {
        {"red",    255,   0,     0},
        {"green",  0,     255,   0},
        {"blue",   0,     0,     255},
        {"yellow", 255,   255,   0},
        {"purple", 128,   0,     128},
        {"cyan",   0,     255,   255},
        {"white",  255,   255,   255},
        {"black",  0,     0,     0},
        {"orange", 255,   165,   0}
};

#define COLOR_COUNT (sizeof(color_table)/sizeof(ColorDef))


// 查找颜色函数
unsigned char find_color(const char* name, unsigned char* r,
                         unsigned char* g, unsigned char* b)
{
    unsigned char i;

    for(i = 0; i < COLOR_COUNT; i++) {
        // SDCC支持不同存储空间的字符串比较
        if(strcmp(name, color_table[i].color_name) == 0) {
            *r = color_table[i].r;
            *g = color_table[i].g;
            *b = color_table[i].b;
            return 1; // 成功
        }
    }
    return 0; // 未找到
}

// RGB PWM输出函数
void set_color_rgb(unsigned char r, unsigned char g, unsigned char b) {
    unsigned char i;
    for(i = 0; i < 255; i++) {
        // 假设LED低电平点亮
        LED_R = (i < r) ? 0 : 1;
        LED_G = (i < g) ? 0 : 1;
        LED_B = (i < b) ? 0 : 1;
    }
}

// 名称颜色设置函数
void set_color(const char* color_name) {
    unsigned char r, g, b;

    if(find_color(color_name, &r, &g, &b)) {
        set_color_rgb(r, g, b);
    } else {
        // 未找到时设为白色
        set_color_rgb(255, 255, 255);
    }
}

// 带亮度的名称颜色设置
void set_color_bright(const char* color_name, unsigned char brightness) {
    unsigned char r, g, b;

    if(find_color(color_name, &r, &g, &b)) {
        // 应用亮度缩放
        if(brightness == 0) {
            set_color_rgb(0, 0, 0); // 全黑
        } else {
            // 避免使用浮点运算
            r = ((unsigned int)r * brightness) / 255;
            g = ((unsigned int)g * brightness) / 255;
            b = ((unsigned int)b * brightness) / 255;
            set_color_rgb(r, g, b);
        }
    } else {
        set_color_rgb(255, 255, 255); // 默认白色
    }
}

// 十六进制字符转换
unsigned char hex_char_to_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0; // 非法字符默认为0
}

// 解析十六进制颜色
unsigned char parse_hex_color(const char *hex_str,
                              unsigned char *r,
                              unsigned char *g,
                              unsigned char *b)
{
    unsigned char len = 0;
    const char *p = hex_str;

    // 跳过#号
    if (*hex_str == '#') {
        hex_str++;
        len++;
        p++;
    }

    // 计算长度
    while (*p) {
        p++;
        len++;
    }

    // SDCC要求显示声明变量类型
    unsigned char valid_length = (len == 3 || len == 6);

    if (!valid_length) return 0; // 无效长度

    if (len == 3) {
        // 3位简写格式（如#F00）
        *r = hex_char_to_value(hex_str[0]) * 17;
        *g = hex_char_to_value(hex_str[1]) * 17;
        *b = hex_char_to_value(hex_str[2]) * 17;
        return 1;
    }

    // 6位完整格式（如#FF0000）
    *r = (hex_char_to_value(hex_str[0]) << 4) | hex_char_to_value(hex_str[1]);
    *g = (hex_char_to_value(hex_str[2]) << 4) | hex_char_to_value(hex_str[3]);
    *b = (hex_char_to_value(hex_str[4]) << 4) | hex_char_to_value(hex_str[5]);

    return 1;
}

// 十六进制颜色设置
void set_color_hex(const char *hex_color) {
    unsigned char r, g, b;

    if (parse_hex_color(hex_color, &r, &g, &b)) {
        set_color_rgb(r, g, b);
    } else {
        // 解析失败设为白色
        set_color_rgb(255, 255, 255);
    }
}

// 带亮度的十六进制颜色设置
void set_color_hex_bright(const char *hex_color, unsigned char brightness) {
    unsigned char r, g, b;

    if (parse_hex_color(hex_color, &r, &g, &b)) {
        // 应用亮度缩放
        if (brightness == 0) {
            set_color_rgb(0, 0, 0);
        } else {
            // 整数运算避免浮点
            r = ((unsigned int)r * brightness) / 255;
            g = ((unsigned int)g * brightness) / 255;
            b = ((unsigned int)b * brightness) / 255;
            set_color_rgb(r, g, b);
        }
    } else {
        set_color_rgb(255, 255, 255);
    }
}














//// 呼吸灯效果
//void breathing_effect(Color color) {
//    unsigned char i;
//    Color temp;
//
//    for(i = 0; i < 255; i++) {
//        temp.r = (color.r * i) / 255;
//        temp.g = (color.g * i) / 255;
//        temp.b = (color.b * i) / 255;
//        set_color(temp);
//        delay_ms(10);
//    }
//
//    for(i = 255; i > 0; i--) {
//        temp.r = (color.r * i) / 255;
//        temp.g = (color.g * i) / 255;
//        temp.b = (color.b * i) / 255;
//        set_color(temp);
//        delay_ms(10);
//    }
//}
//
//// 彩虹效果
//void rainbow_effect(void) {
//    Color colors[] = {
//            {255, 0, 0},    // 红
//            {255, 127, 0},  // 橙
//            {255, 255, 0},  // 黄
//            {0, 255, 0},    // 绿
//            {0, 0, 255},    // 蓝
//            {139, 0, 255}   // 紫
//    };
//
//    unsigned char i;
//    for(i = 0; i < 6; i++) {
//        set_color(colors[i]);
//        delay_ms(500);
//    }
//}
//
//// 随机颜色效果
//void random_color(void) {
//    Color random;
//    random.r = TH0;  // 使用定时器的值作为随机数源
//    random.g = TL0;
//    random.b = TH1;
//    set_color(random);
//}
//
//// 颜色渐变效果
//void color_transition(Color from, Color to, unsigned int steps) {
//    int i;
//    Color temp;
//    for(i = 0; i <= steps; i++) {
//        temp.r = from.r + ((to.r - from.r) * i / steps);
//        temp.g = from.g + ((to.g - from.g) * i / steps);
//        temp.b = from.b + ((to.b - from.b) * i / steps);
//        set_color(temp);
//        delay_ms(20);
//    }
//}