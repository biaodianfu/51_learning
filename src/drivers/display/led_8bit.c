//
// Created by qw on 25-7-12.
//
#include "STC89C5xRC.h"
#include "led_8bit.h"
#include "utils/delay.h"
#include "configs/led_8bit_config.h"

void led_all_off(void) {
    LED_PORT = 0xFF; // 全暗
}

void led_all_on(void) {
    LED_PORT = 0x00; // 全亮
}

void led_flow_left(void) {
    LED_PORT = 0xFF;
    for (unsigned char position = 0; position < 8; position++) {
        LED_PORT = ~(1 << position);
        delay_ms(FLOW_DELAY_MS);
    }
    LED_PORT = 0xFF; // 恢复关闭
}

void led_flow_right(void) {
    LED_PORT = 0xFF;
    for (unsigned char position = 7;; --position) {
        LED_PORT = ~(1 << position);
        delay_ms(FLOW_DELAY_MS);
        if (position == 0) break;
    }
    LED_PORT = 0xFF;
}

void led_flow(void) {
    led_flow_left();
    led_flow_right();
}

void led_flow_reverse(void) {
    for (unsigned char i = 0; i < 8; i++) {
        LED_PORT = 1 << i; // 点亮一个LED
        delay_ms(FLOW_DELAY_MS);
    }
    for (unsigned char i = 7;; i--) {
        LED_PORT = 1 << i; // 点亮一个LED
        delay_ms(FLOW_DELAY_MS);
        if (i == 0) break;
    }
}

void led_blink_all(void) {
    for (unsigned char i = 0; i < 2; i++) {
        LED_PORT = 0x00; // 全亮
        delay_ms(BLINK_DELAY_MS);
        LED_PORT = 0xFF; // 全灭
        delay_ms(BLINK_DELAY_MS);
    }
}

void led_blink_alternate(void) {
    for (unsigned char i = 0; i < 2; i++) {
        LED_PORT = 0xAA; // 10101010
        delay_ms(BLINK_DELAY_MS);
        LED_PORT = 0x55; // 01010101
        delay_ms(BLINK_DELAY_MS);
    }
}

void led_breath(void) {
    unsigned char duty; // 占空比控制变量
    // 从暗到亮：占空比0-100
    for (duty = 0; duty < 100; duty++) {
        LED_PORT = 0x00;          // LED全亮
        delay_us(duty * 5);    // 亮的时间
        LED_PORT = 0xFF;          // LED全灭
        delay_us((100 - duty) * 5); // 灭的时间
    }

    // 从亮到暗：占空比100-0
    for (duty = 100; duty > 0; duty--) {
        LED_PORT = 0x00;          // LED全亮
        delay_us(duty * 5);    // 亮的时间
        LED_PORT = 0xFF;          // LED全灭
        delay_us((100 - duty) * 5); // 灭的时间
    }
}

void led_wave(void) {
    static const unsigned char wave_patterns[] = {
            0x00, // 00000000
            0x81, // 10000001
            0xC3, // 11000011
            0xE7, // 11100111
            0xFF, // 11111111
            0xE7, // 11100111
            0xC3, // 11000011
            0x81, // 10000001
            0x00  // 00000000
    };
    for (unsigned char i = 0; i < sizeof(wave_patterns); i++) {
        LED_PORT = wave_patterns[i];
        delay_ms(BLINK_DELAY_MS); // 每个波形显示100毫秒
    }
}

void led_wave_reverse(void) {
    static const unsigned char wave_patterns[] = {
            0xFF, // 11111111
            0x7E, // 01111110
            0x3C, // 00111100
            0x18, // 00011000
            0x00, // 00000000
            0x18, // 00011000
            0x3C, // 00111100
            0x7E, // 01111110
            0xFF  // 11111111
    };
    for (unsigned char i = 0; i < sizeof(wave_patterns); i++) {
        LED_PORT = wave_patterns[i];
        delay_ms(BLINK_DELAY_MS); // 每个波形显示100毫秒
    }
}

void led_tide(void) {
    LED_PORT = 0xFF;
    static const unsigned char tide_patterns[] = {
            0xFF, // 11111111
            0xFE, // 11111110
            0xFC, // 11111100
            0xF8, // 11111000
            0xF0, // 11110000
            0xE0, // 11100000
            0xC0, // 11000000
            0x80, // 10000000
            0x00, // 00000000
            0x80, // 10000000
            0xC0, // 11000000
            0xE0, // 11100000
            0xF0, // 11110000
            0xF8, // 11111000
            0xFC, // 11111100
            0xFE, // 11111110
            0xFF  // 11111111
    };
    for (unsigned char i = 0; i < sizeof(tide_patterns); i++) {
        LED_PORT = tide_patterns[i];
        delay_ms(FLOW_DELAY_MS); // 每个波形显示100毫秒
    }
}