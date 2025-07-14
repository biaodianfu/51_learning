//
// Created by qw on 25-7-12.
//
#include "led_effect_show.h"
#include "utils/delay.h"
#include "../../drivers/display/led_8bit.h"

// LED效果展示模块
void led_effect_module_run(void) {
    // 关闭所有LED
    led_all_off();
    delay_ms(1000); // 等待1秒

    // 全部点亮
    led_all_on();
    delay_ms(1000); // 等待1秒

    for (unsigned char i = 0; i < 3; i++) {
        led_flow_left();
    }
    delay_ms(1000); // 等待1秒

    for (unsigned char i = 0; i < 3; i++) {
        led_flow_right();
    }
    delay_ms(1000); // 等待1秒

    // 流水灯效果
    for (unsigned char i = 0; i < 3; i++) {
        led_flow();
    }
    delay_ms(1000); // 等待1秒

    // 流水灯暗模式
    for (unsigned char i = 0; i < 3; i++) {
        led_flow_reverse();
    }
    delay_ms(1000); // 等待1秒

    // 闪烁效果
    for (unsigned char i = 0; i < 3; i++) {
        led_blink_all();
    }
    delay_ms(1000); // 等待1秒

    // 交替闪烁效果
    for( unsigned char i = 0; i < 3; i++) {
        led_blink_alternate();
    }
    delay_ms(1000); // 等待1秒

    // 呼吸灯效果
    for (unsigned char i = 0; i < 3; i++) {
        led_breath();
    }
    delay_ms(1000); // 等待1秒

    // 波浪效果
    for (unsigned char i = 0; i < 3; i++) {
        led_wave();
    }
    delay_ms(1000); // 等待1秒
    // 波浪效果2
    for (unsigned char i = 0; i < 3; i++) {
        led_wave_reverse();
    }
    delay_ms(1000); // 等待1秒

    // 潮汐效果
    for (unsigned char i = 0; i < 3; i++) {
        led_tide();
    }
    delay_ms(1000); // 等待1秒
}
