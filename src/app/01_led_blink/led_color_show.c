//
// Created by qw on 25-7-17.
//

#include "led_color_show.h"
#include "../../drivers/display/led_1bit_5050.h"
#include "../../utils/delay.h"

void led_color_show(void) {
    // 颜色定义：红色、绿色、蓝色
    unsigned char colors[][3] = {
        {255, 0, 0},   // 红色
        {0, 255, 0},   // 绿色
        {0, 0, 255}    // 蓝色
    };

    // 循环显示每种颜色
    for (unsigned char i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        set_color_rgb(colors[i][0], colors[i][1], colors[i][2]);
        delay_ms(1000); // 每种颜色显示1秒
    }
}

void led_color_show_bright(void) {
    // 颜色定义：红色、绿色、蓝色，带亮度
    unsigned char colors[][3] = {
        {255, 0, 0},   // 红色
        {0, 255, 0},   // 绿色
        {0, 0, 255}    // 蓝色
    };
    unsigned char brightness = 128; // 设置亮度为50%

    // 循环显示每种颜色
    for (unsigned char i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        set_color_rgb_bright(colors[i][0], colors[i][1], colors[i][2], brightness);
        delay_ms(1000); // 每种颜色显示1秒
    }
}

void led_color_show_hex(void) {
    // 十六进制颜色定义：红色、绿色、蓝色
    const char *colors[] = {
        "#FF0000", // 红色
        "#00FF00", // 绿色
        "#0000FF"  // 蓝色
    };

    // 循环显示每种颜色
    for (unsigned char i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        set_color_hex(colors[i]);
        delay_ms(1000); // 每种颜色显示1秒
    }
}

void led_color_show_hex_bright(void) {
    // 十六进制颜色定义：红色、绿色、蓝色，带亮度
    const char *colors[] = {
        "#FF0000", // 红色
        "#00FF00", // 绿色
        "#0000FF"  // 蓝色
    };
    unsigned char brightness = 128; // 设置亮度为50%

    // 循环显示每种颜色
    for (unsigned char i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        set_color_hex_bright(colors[i], brightness);
        delay_ms(1000); // 每种颜色显示1秒
    }
}

void led_color_show_breathing(void) {
    // 呼吸灯效果：红色、绿色、蓝色
    unsigned char colors[][3] = {
        {255, 0, 0},   // 红色
        {0, 255, 0},   // 绿色
        {0, 0, 255}    // 蓝色
    };

    // 循环显示每种颜色的呼吸灯效果
    for (unsigned char i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        breathing_effect_rgb(colors[i][0], colors[i][1], colors[i][2]);
        delay_ms(1000); // 每种颜色显示1秒
    }
}

void led_color_show_breathing_hex(void) {
    // 十六进制颜色定义：红色、绿色、蓝色
    const char *colors[] = {
        "#FF0000", // 红色
        "#00FF00", // 绿色
        "#0000FF"  // 蓝色
    };

    // 循环显示每种颜色的呼吸灯效果
    for (unsigned char i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        breathing_effect_color(colors[i]);
        delay_ms(1000); // 每种颜色显示1秒
    }
}

void led_color_show_rainbow(void) {
    // 彩虹渐变效果
    rainbow_effect();
    delay_ms(1000); // 效果持续1秒
}

void led_color_show_all(void) {
    // 显示所有颜色效果
    led_color_show();
    led_color_show_bright();
    led_color_show_hex();
    led_color_show_hex_bright();
    led_color_show_breathing();
    led_color_show_breathing_hex();
    led_color_show_rainbow();
}