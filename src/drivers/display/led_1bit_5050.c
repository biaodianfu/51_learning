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

void set_color_rgb_bright(unsigned char r, unsigned char g, unsigned char b,
                            unsigned char brightness) {
    if (brightness == 0) {
        // 全黑
        LED_R = 1;
        LED_G = 1;
        LED_B = 1;
    } else {
        // 避免使用浮点运算，使用整数缩放
        r = ((unsigned int)r * brightness) / 255;
        g = ((unsigned int)g * brightness) / 255;
        b = ((unsigned int)b * brightness) / 255;
        set_color_rgb(r, g, b);
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

// HSV转RGB的转换函数（H:0-359°, S:0-255, V:0-255）
void hsv2rgb(unsigned int h, unsigned char s, unsigned char v,
             unsigned char *r, unsigned char *g, unsigned char *b) {
    // 使用位域和计算优化减少变量
    unsigned char region = (h % 360) / 60;
    unsigned char rem = (h % 60) * 4;

    if (s == 0) {
        *r = *g = *b = v;
        return;
    }

    // 合并计算减少中间变量
    unsigned char p = (v * (255 - s)) / 255;
    unsigned char temp;

    // 使用位运算替代 switch 结构
    unsigned char case_id = region % 6;

    // case 0: *r = v; *g = t; *b = p;
    if (case_id == 0) {
        temp = (s * (256 - rem)) / 256;
        *r = v;
        *g = (v * (255 - temp)) / 255;
        *b = p;
    }
        // case 1: *r = q; *g = v; *b = p;
    else if (case_id == 1) {
        temp = (s * rem) / 256;
        *r = (v * (255 - temp)) / 255;
        *g = v;
        *b = p;
    }
        // case 2: *r = p; *g = v; *b = t;
    else if (case_id == 2) {
        temp = (s * (256 - rem)) / 256;
        *r = p;
        *g = v;
        *b = (v * (255 - temp)) / 255;
    }
        // case 3: *r = p; *g = q; *b = v;
    else if (case_id == 3) {
        temp = (s * rem) / 256;
        *r = p;
        *g = (v * (255 - temp)) / 255;
        *b = v;
    }
        // case 4: *r = t; *g = p; *b = v;
    else if (case_id == 4) {
        temp = (s * (256 - rem)) / 256;
        *r = (v * (255 - temp)) / 255;
        *g = p;
        *b = v;
    }
        // case 5: *r = v; *g = p; *b = q;
    else {
        temp = (s * rem) / 256;
        *r = v;
        *g = p;
        *b = (v * (255 - temp)) / 255;
    }
}



// HSV格式的PWM输出函数
void set_color_hsv(unsigned int h, unsigned char s, unsigned char v) {
    unsigned char r, g, b;

    // 第一步：将HSV参数转换为RGB值
    hsv2rgb(h, s, v, &r, &g, &b);
    set_color_rgb(r, g, b);
}

void breathing_effect(unsigned char r, unsigned char g, unsigned char b) {
    unsigned char i;
    unsigned char tr, tg, tb;  // 使用单独变量代替结构体

    // 渐亮
    for (i = 0; i < 255; i++) {
        tr = (r * i) / 255;
        tg = (g * i) / 255;
        tb = (b * i) / 255;
        set_color_rgb(tr, tg, tb);
        delay_ms(10);
    }

    // 渐暗
    for (i = 255; i > 0; i--) {
        tr = (r * i) / 255;
        tg = (g * i) / 255;
        tb = (b * i) / 255;
        set_color_rgb(tr, tg, tb);
        delay_ms(10);
    }
}

void breathing_effect_color(const char* color_name) {
    unsigned char r, g, b;

    if (find_color(color_name, &r, &g, &b)) {
        breathing_effect(r, g, b);
    } else {
        // 未找到颜色时使用白色
        breathing_effect(255, 255, 255);
    }
}



void rainbow_effect(void) {
    unsigned char r, g, b;
    unsigned char i;
    unsigned int h;

    for (i = 0; i < 255; i += 32) {  // 减少亮度步进值
        for (h = 0; h < 360; h += 60) {  // 减少色相步进值
            hsv2rgb(h, 255, i, &r, &g, &b);
            set_color_rgb(r, g, b);
            delay_ms(20);
        }
    }
}