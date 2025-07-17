#ifndef LED_1BIT_5050_H
#define LED_1BIT_5050_H

/**
 * 根据颜色名称查找对应的RGB值
 * @param name 输入的颜色名称字符串
 * @param r 输出参数，存储红色分量值
 * @param g 输出参数，存储绿色分量值
 * @param b 输出参数，存储蓝色分量值
 * @return 查找成功返回1，失败返回0
 */
unsigned char find_color(const char* name, unsigned char* r, unsigned char* g, unsigned char* b);

/**
 * 设置RGB颜色（无亮度调节）
 * @param r 红色分量值（0-255）
 * @param g 绿色分量值（0-255）
 * @param b 蓝色分量值（0-255）
 */
void set_color_rgb(unsigned char r, unsigned char g, unsigned char b);

/**
 * 通过颜色名称设置颜色（无亮度调节）
 * @param color_name 预定义的颜色名称字符串
 */
void set_color(const char* color_name);

/**
 * 通过颜色名称设置带亮度的颜色
 * @param color_name 预定义的颜色名称字符串
 * @param brightness 亮度值（0-255）
 */
void set_color_bright(const char* color_name, unsigned char brightness);

/**
 * 通过十六进制颜色码设置颜色（无亮度调节）
 * @param hex_color 十六进制颜色字符串（格式如"#RRGGBB"）
 */
void set_color_hex(const char *hex_color);

/**
 * 通过十六进制颜色码设置带亮度的颜色
 * @param hex_color 十六进制颜色字符串（格式如"#RRGGBB"）
 * @param brightness 亮度值（0-255）
 */
void set_color_hex_bright(const char *hex_color, unsigned char brightness);

/**
 * 设置带亮度调节的RGB颜色
 * @param r 红色分量值（0-255）
 * @param g 绿色分量值（0-255）
 * @param b 蓝色分量值（0-255）
 * @param brightness 亮度值（0-255）
 */
void set_color_rgb_bright(unsigned char r, unsigned char g, unsigned char b,
                             unsigned char brightness);

/**
 * 对指定RGB颜色进行呼吸灯效果控制
 * @param r 红色分量值（0-255）
 * @param g 绿色分量值（0-255）
 * @param b 蓝色分量值（0-255）
 */
void breathing_effect_rgb(unsigned char r, unsigned char g, unsigned char b);

/**
 * 通过颜色名称进行呼吸灯效果控制
 * @param color_name 预定义的颜色名称字符串
 */
void breathing_effect_color(const char* color_name);

/**
 * 彩虹色流动效果控制
 */
void rainbow_effect(void);

/**
 * 通过HSV颜色空间设置LED颜色
 * @param h 色相值（0-360）
 * @param s 饱和度（0-255）
 * @param v 明度（0-255）
 */
void set_color_hsv(unsigned int h, unsigned char s, unsigned char v);

#endif //LED_1BIT_5050_H
