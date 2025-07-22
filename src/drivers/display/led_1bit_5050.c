#include "config.h"
/*
 * 1位5050 RGB LED驱动程序
 * 支持通过颜色名称、十六进制字符串或HSV值设置颜色
 * 包含呼吸灯和彩虹渐变效果
 *
 * 适用于使用1位PWM模拟RGB LED的应用场景
 */
#if USE_LED_1BIT_5050
#include "led_1bit_5050.h"
#include <string.h> // 为了使用标准字符串函数
#include <lint.h>

// 颜色定义结构体（存储在ROM中）
// 用于存储颜色名称及其对应的RGB分量值
typedef struct {
    const char *color_name; // 颜色名称字符串
    unsigned char r;        // 红色分量值(0-255)
    unsigned char g;        // 绿色分量值(0-255)
    unsigned char b;        // 蓝色分量值(0-255)
} ColorDef;

// 预定义颜色查找表（存放在程序存储器）
// 包含常见颜色名称及其对应的RGB值
const __code ColorDef color_table[] = {
        {"red",    255, 0,   0},
        {"green",  0,   255, 0},
        {"blue",   0,   0,   255},
        {"yellow", 255, 255, 0},
        {"purple", 128, 0,   128},
        {"cyan",   0,   255, 255},
        {"white",  255, 255, 255},
        {"black",  0,   0,   0},
        {"orange", 255, 165, 0}
};

// 计算颜色表中定义的颜色数量
#define COLOR_COUNT (sizeof(color_table)/sizeof(ColorDef))


/**
 * 在预定义颜色表中查找指定颜色名称
 *
 * @param name 要查找的颜色名称字符串
 * @param r    输出参数，存储查找到的红色分量值
 * @param g    输出参数，存储查找到的绿色分量值
 * @param b    输出参数，存储查找到的蓝色分量值
 * @return 查找成功返回1，未找到返回0
 */
unsigned char find_color(const char *name, unsigned char *r,
                         unsigned char *g, unsigned char *b) {
    unsigned char i;
    // 遍历颜色表进行名称匹配
    for (i = 0; i < COLOR_COUNT; i++) {
        // 比较输入名称与表中颜色名称
        if (strcmp(name, color_table[i].color_name) == 0) {
            // 找到匹配项，提取RGB分量值
            *r = color_table[i].r;
            *g = color_table[i].g;
            *b = color_table[i].b;
            return 1; // 成功
        }
    }
    return 0; // 未找到
}

/**
 * 设置RGB LED颜色（使用1位PWM模拟）
 *
 * @param r 红色分量值(0-255)
 * @param g 绿色分量值(0-255)
 * @param b 蓝色分量值(0-255)
 *
 * 说明：通过循环计数实现伪PWM效果，低电平点亮LED
 */
void set_color_rgb(unsigned char r, unsigned char g, unsigned char b) {
    unsigned char i;
    // 通过255次循环实现PWM效果
    for (i = 0; i < 255; i++) {
        // 当计数值小于分量值时输出低电平（点亮），否则高电平
        LED_R = (i < r) ? 0 : 1;
        LED_G = (i < g) ? 0 : 1;
        LED_B = (i < b) ? 0 : 1;
    }
}

/**
 * 设置带亮度调节的RGB颜色
 *
 * @param r          红色分量值(0-255)
 * @param g          绿色分量值(0-255)
 * @param b          蓝色分量值(0-255)
 * @param brightness 亮度值(0-255)，0为全灭
 */
void set_color_rgb_bright(unsigned char r, unsigned char g, unsigned char b,
                          unsigned char brightness) {
    // 亮度为0时关闭所有LED
    if (brightness == 0) {
        LED_R = 1;
        LED_G = 1;
        LED_B = 1;
    } else {
        // 使用整数运算缩放RGB值（避免浮点运算）
        r = ((unsigned int) r * brightness) / 255;
        g = ((unsigned int) g * brightness) / 255;
        b = ((unsigned int) b * brightness) / 255;
        set_color_rgb(r, g, b);
    }
}

/**
 * 通过颜色名称设置LED颜色
 *
 * @param color_name 预定义的颜色名称字符串
 *
 * 说明：如果名称未在表中找到，则默认显示白色
 */
void set_color(const char *color_name) {
    unsigned char r, g, b;

    // 尝试查找颜色名称
    if (find_color(color_name, &r, &g, &b)) {
        set_color_rgb(r, g, b);
    } else {
        // 未找到时设为白色
        set_color_rgb(255, 255, 255);
    }
}

/**
 * 通过颜色名称设置带亮度的LED颜色
 *
 * @param color_name 预定义的颜色名称字符串
 * @param brightness 亮度值(0-255)
 */
void set_color_bright(const char *color_name, unsigned char brightness) {
    unsigned char r, g, b;

    if (find_color(color_name, &r, &g, &b)) {
        // 亮度为0时直接关闭LED
        if (brightness == 0) {
            set_color_rgb(0, 0, 0);
        } else {
            // 使用整数运算缩放RGB值
            r = ((unsigned int) r * brightness) / 255;
            g = ((unsigned int) g * brightness) / 255;
            b = ((unsigned int) b * brightness) / 255;
            set_color_rgb(r, g, b);
        }
    } else {
        // 未找到颜色时设为白色
        set_color_rgb(255, 255, 255);
    }
}

/**
 * 将十六进制字符转换为对应的数值
 *
 * @param c 输入的十六进制字符(0-9, A-F, a-f)
 * @return  对应的数值(0-15)，非法字符返回0
 */
unsigned char hex_char_to_value(char c) {
    // 处理数字字符
    if (c >= '0' && c <= '9') return c - '0';
    // 处理大写字母
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    // 处理小写字母
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0; // 非法字符默认为0
}

/**
 * 解析十六进制格式的颜色字符串
 *
 * @param hex_str 十六进制颜色字符串(支持#RGB或#RRGGBB格式)
 * @param r       输出参数，存储解析出的红色分量
 * @param g       输出参数，存储解析出的绿色分量
 * @param b       输出参数，存储解析出的蓝色分量
 * @return        解析成功返回1，无效格式返回0
 */
unsigned char parse_hex_color(const char *hex_str,
                              unsigned char *r,
                              unsigned char *g,
                              unsigned char *b) {
    unsigned char len = 0;
    const char *p = hex_str;

    // 检查并跳过开头的'#'符号
    if (*hex_str == '#') {
        hex_str++;
        len++;
        p++;
    }

    // 计算字符串长度
    while (*p) {
        p++;
        len++;
    }

    // 验证长度有效性（3位或6位）
    unsigned char valid_length = (len == 3 || len == 6);

    if (!valid_length) return 0; // 无效长度

    if (len == 3) {
        // 处理3位简写格式（如#F00）
        *r = hex_char_to_value(hex_str[0]) * 17;  // 乘以17转换为8位值
        *g = hex_char_to_value(hex_str[1]) * 17;
        *b = hex_char_to_value(hex_str[2]) * 17;
        return 1;
    }

    // 处理6位完整格式（如#FF0000）
    *r = (hex_char_to_value(hex_str[0]) << 4) | hex_char_to_value(hex_str[1]);
    *g = (hex_char_to_value(hex_str[2]) << 4) | hex_char_to_value(hex_str[3]);
    *b = (hex_char_to_value(hex_str[4]) << 4) | hex_char_to_value(hex_str[5]);

    return 1;
}

/**
 * 通过十六进制字符串设置LED颜色
 *
 * @param hex_color 十六进制颜色字符串
 *
 * 说明：解析失败时默认显示白色
 */
void set_color_hex(const char *hex_color) {
    unsigned char r, g, b;

    if (parse_hex_color(hex_color, &r, &g, &b)) {
        set_color_rgb(r, g, b);
    } else {
        // 解析失败设为白色
        set_color_rgb(255, 255, 255);
    }
}

/**
 * 通过十六进制字符串设置带亮度的LED颜色
 *
 * @param hex_color  十六进制颜色字符串
 * @param brightness 亮度值(0-255)
 */
void set_color_hex_bright(const char *hex_color, unsigned char brightness) {
    unsigned char r, g, b;

    if (parse_hex_color(hex_color, &r, &g, &b)) {
        // 应用亮度缩放
        if (brightness == 0) {
            set_color_rgb(0, 0, 0);
        } else {
            // 整数运算避免浮点
            r = ((unsigned int) r * brightness) / 255;
            g = ((unsigned int) g * brightness) / 255;
            b = ((unsigned int) b * brightness) / 255;
            set_color_rgb(r, g, b);
        }
    } else {
        set_color_rgb(255, 255, 255);
    }
}

/**
 * 将HSV颜色空间转换为RGB颜色空间
 *
 * @param h 色相值(0-359度)
 * @param s 饱和度(0-255)
 * @param v 亮度值(0-255)
 * @param r 输出参数，转换后的红色分量
 * @param g 输出参数，转换后的绿色分量
 * @param b 输出参数，转换后的蓝色分量
 *
 * 说明：使用整数运算避免浮点，色相环分为6个60度区域
 */
void hsv2rgb(unsigned int h, unsigned char s, unsigned char v,
             __idata unsigned char *r, __idata unsigned char *g, __idata unsigned char *b) {

    __idata unsigned char region;
    __idata unsigned char rem;
    __idata unsigned char p;
    __idata unsigned char temp;
    __idata unsigned char case_id;

    // 计算色相所在区域(0-5)和剩余值
    region = (h % 360) / 60;
    rem = (h % 60) * 4;

    // 饱和度为0时直接输出灰度值
    if (s == 0) {
        *r = *g = *b = v;
        return;
    }

    // 计算基础值p
    p = (v * (255 - s)) / 255;
    case_id = region % 6;

    // 根据色相区域计算RGB分量
    if (case_id == 0) {
        temp = (s * (256 - rem)) / 256;
        *r = v;
        *g = (v * (255 - temp)) / 255;
        *b = p;
    } else if (case_id == 1) {
        temp = (s * rem) / 256;
        *r = (v * (255 - temp)) / 255;
        *g = v;
        *b = p;
    } else if (case_id == 2) {
        temp = (s * (256 - rem)) / 256;
        *r = p;
        *g = v;
        *b = (v * (255 - temp)) / 255;
    } else if (case_id == 3) {
        temp = (s * rem) / 256;
        *r = p;
        *g = (v * (255 - temp)) / 255;
        *b = v;
    } else if (case_id == 4) {
        temp = (s * (256 - rem)) / 256;
        *r = (v * (255 - temp)) / 255;
        *g = p;
        *b = v;
    } else {
        temp = (s * rem) / 256;
        *r = v;
        *g = p;
        *b = (v * (255 - temp)) / 255;
    }
}


/**
 * 通过HSV参数设置LED颜色
 *
 * @param h 色相值(0-359度)
 * @param s 饱和度(0-255)
 * @param v 亮度值(0-255)
 */
void set_color_hsv(unsigned int h, unsigned char s, unsigned char v) {
    unsigned char r, g, b;

    // 第一步：将HSV参数转换为RGB值
    hsv2rgb(h, s, v, &r, &g, &b);
    set_color_rgb(r, g, b);
}

/**
 * 实现指定RGB颜色的呼吸灯效果
 *
 * @param r 红色分量值(0-255)
 * @param g 绿色分量值(0-255)
 * @param b 蓝色分量值(0-255)
 *
 * 说明：包含渐亮和渐暗两个阶段，每个阶段255步
 */
void breathing_effect_rgb(unsigned char r, unsigned char g, unsigned char b) {
    unsigned char i;
    unsigned char tr, tg, tb;  // 临时存储当前步的RGB值

    // 渐亮阶段：亮度从0%到100%
    for (i = 0; i < 255; i++) {
        // 计算当前亮度的RGB值
        tr = (r * i) / 255;
        tg = (g * i) / 255;
        tb = (b * i) / 255;
        set_color_rgb(tr, tg, tb);
        delay_ms(5);  // 控制渐变速度
    }

    // 渐暗阶段：亮度从100%到0%
    for (i = 255; i > 0; i--) {
        tr = (r * i) / 255;
        tg = (g * i) / 255;
        tb = (b * i) / 255;
        set_color_rgb(tr, tg, tb);
        delay_ms(5);
    }
}

/**
 * 通过颜色名称实现呼吸灯效果
 *
 * @param color_name 预定义的颜色名称字符串
 *
 * 说明：未找到颜色名称时使用白色呼吸效果
 */
void breathing_effect_color(const char *color_name) {
    unsigned char r, g, b;

    if (find_color(color_name, &r, &g, &b)) {
        breathing_effect_rgb(r, g, b);
    } else {
        // 未找到颜色时使用白色
        breathing_effect_rgb(255, 255, 255);
    }
}


/**
 * 彩虹渐变效果（包含亮度变化）
 *
 * 说明：在色相环上循环，同时改变亮度实现彩虹呼吸效果
 */
void rainbow_effect(void) {
    __idata unsigned char r, g, b;
    unsigned char brightness;
    unsigned int hue;
    unsigned char step = 1;  // 亮度变化步长（减少频闪）

    // 亮度上升阶段：从0到255
    for (brightness = 0; brightness < 255; brightness += step) {
        // 遍历色相环（0-359度），步进5度
        for (hue = 0; hue < 360; hue += 5) {
            // 转换当前HSV值为RGB
            hsv2rgb(hue, 255, brightness, &r, &g, &b);
            set_color_rgb(r, g, b);
            delay_ms(2);  // 控制效果速度
        }
    }

    // 亮度下降阶段：从255到0
    for (brightness = 255; brightness > 0; brightness -= step) {
        // 更细的色相步进（1度）增强平滑度
        for (hue = 0; hue < 360; hue += 1) {
            hsv2rgb(hue, 255, brightness, &r, &g, &b);
            set_color_rgb(r, g, b);
            delay_ms(2);
        }
    }
}
#endif