
//
// Created by qw on 25-7-12.
//
#include "STC89C5xRC.h"
#include "led_8bit.h"
#include "utils/delay.h"
#include "configs/led_8bit_config.h"

/**
 * 关闭所有LED灯（全灭）
 * 无参数
 * 无返回值
 */
void led_all_off(void) {
    LED_PORT = 0xFF;
}

/**
 * 点亮所有LED灯（全亮）
 * 无参数
 * 无返回值
 */
void led_all_on(void) {
    LED_PORT = 0x00;
}

/**
 * 实现LED从左向右流动效果
 * 无参数
 * 无返回值
 * 说明：逐个点亮LED（从左到右），每次只亮一个灯
 */
void led_flow_left(void) {
    LED_PORT = 0xFF;
    for (unsigned char position = 0; position < 8; position++) {
        LED_PORT = ~(1 << position);
        delay_ms(FLOW_DELAY_MS);
    }
    LED_PORT = 0xFF;
}

/**
 * 实现LED从右向左流动效果
 * 无参数
 * 无返回值
 * 说明：逐个点亮LED（从右到左），每次只亮一个灯
 */
void led_flow_right(void) {
    LED_PORT = 0xFF;
    for (unsigned char position = 7;; position--) {
        LED_PORT = ~(1 << position);
        delay_ms(FLOW_DELAY_MS);
        if (position == 0) break;
    }
    LED_PORT = 0xFF;
}

/**
 * 实现LED双向流动效果（先左后右）
 * 无参数
 * 无返回值
 */
void led_flow(void) {
    led_flow_left();
    led_flow_right();
}

/**
 * 实现LED反向流动效果（先展开后收缩）
 * 无参数
 * 无返回值
 * 说明：第一循环从左向右逐个点亮，第二循环从右向左逐个熄灭
 */
void led_flow_reverse(void) {
    for (unsigned char i = 0; i < 8; i++) {
        LED_PORT = 1 << i;
        delay_ms(FLOW_DELAY_MS);
    }
    for (unsigned char i = 7;; i--) {
        LED_PORT = 1 << i;
        delay_ms(FLOW_DELAY_MS);
        if (i == 0) break;
    }
}

/**
 * 实现所有LED同步闪烁效果
 * 无参数
 * 无返回值
 * 说明：完成两次全亮/全灭的切换
 */
void led_blink_all(void) {
    for (unsigned char i = 0; i < 2; i++) {
        LED_PORT = 0x00;
        delay_ms(BLINK_DELAY_MS);
        LED_PORT = 0xFF;
        delay_ms(BLINK_DELAY_MS);
    }
}

/**
 * 实现LED交替闪烁效果
 * 无参数
 * 无返回值
 * 说明：完成两次交叉亮灭模式的切换（0xAA和0x55）
 */
void led_blink_alternate(void) {
    for (unsigned char i = 0; i < 2; i++) {
        LED_PORT = 0xAA;
        delay_ms(BLINK_DELAY_MS);
        LED_PORT = 0x55;
        delay_ms(BLINK_DELAY_MS);
    }
}

/**
 * 实现LED呼吸灯效果
 * 无参数
 * 无返回值
 * 说明：通过PWM占空比变化实现亮度渐变（先渐亮后渐暗）
 */
void led_breath(void) {
    unsigned char duty;
    // 亮度渐增过程
    for (duty = 0; duty < 100; duty++) {
        LED_PORT = 0x00;
        delay_us(duty * 5);
        LED_PORT = 0xFF;
        delay_us((100 - duty) * 5);
    }

    // 亮度渐减过程
    for (duty = 100; duty > 0; duty--) {
        LED_PORT = 0x00;
        delay_us(duty * 5);
        LED_PORT = 0xFF;
        delay_us((100 - duty) * 5);
    }
}

/**
 * 实现波浪扩散效果（中心向外）
 * 无参数
 * 无返回值
 * 说明：使用预定义模式模拟波浪状亮灭变化
 */
void led_wave(void) {
    static const unsigned char wave_patterns[] = {
            0x00,
            0x81,
            0xC3,
            0xE7,
            0xFF,
            0xE7,
            0xC3,
            0x81,
            0x00
    };
    for (unsigned char i = 0; i < sizeof(wave_patterns); i++) {
        LED_PORT = wave_patterns[i];
        delay_ms(BLINK_DELAY_MS);
    }
}

/**
 * 实现反向波浪效果（外向内收缩）
 * 无参数
 * 无返回值
 * 说明：使用预定义模式模拟反向波浪状亮灭变化
 */
void led_wave_reverse(void) {
    static const unsigned char wave_patterns[] = {
            0xFF,
            0x7E,
            0x3C,
            0x18,
            0x00,
            0x18,
            0x3C,
            0x7E,
            0xFF
    };
    for (unsigned char i = 0; i < sizeof(wave_patterns); i++) {
        LED_PORT = wave_patterns[i];
        delay_ms(BLINK_DELAY_MS);
    }
}

/**
 * 实现潮汐涨落效果（渐进式亮灭）
 * 无参数
 * 无返回值
 * 说明：通过预定义模式模拟类似潮汐的亮度变化
 */
void led_tide(void) {
    LED_PORT = 0xFF;
    static const unsigned char tide_patterns[] = {
            0xFF,
            0xFE,
            0xFC,
            0xF8,
            0xF0,
            0xE0,
            0xC0,
            0x80,
            0x00,
            0x80,
            0xC0,
            0xE0,
            0xF0,
            0xF8,
            0xFC,
            0xFE,
            0xFF
    };
    for (unsigned char i = 0; i < sizeof(tide_patterns); i++) {
        LED_PORT = tide_patterns[i];
        delay_ms(FLOW_DELAY_MS);
    }
}