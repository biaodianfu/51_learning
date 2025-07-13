//
// Created by qw on 25-7-12.
//
#include "STC89C5xRC.h"
#include "led_8bit.h"
#include "utils/delay.h"
#include "configs/led_8bit_config.h"

static LedEffect current_effect = LED_EFFECT_ALL_OFF;

void set_led_effect(LedEffect effect) {
    current_effect = effect;
}

void run_flow_left(void) {
    static unsigned char position = 0;
    static unsigned int last_update = 0;

    // 检查是否达到更新时间
    if (last_update < FLOW_DELAY_MS) {
        return;
    }
    last_update = 0;

    // 更新位置
    position = (position + 1) % 8;

    // 设置LED状态
    LED_PORT = ~(1 << position); // 点亮对应位置的LED
}

void led_run_effect(void) {
    switch (current_effect) {
        case LED_EFFECT_ALL_OFF:
            LED_PORT = 0xFF; // 全暗
            break;
        case LED_EFFECT_ALL_ON:
            LED_PORT = 0x00; // 全亮
            break;
        case LED_EFFECT_FLOW_LEFT:
        LED_PORT = 0xFE; // 11111110
            run_flow_left();
        break;
        case LED_EFFECT_ALTERNATE:
            LED_PORT = 0xAA;

            break;
        case LED_EFFECT_BLINK_ALL:
            LED_PORT = 0x00;
            break;
        case LED_EFFECT_BREATH:
            LED_PORT = 0x00;

    }
}

























//
//
//// 当前效果状态
//static LedEffect current_effect = LED_EFFECT_ALL_OFF;
//
//
//
//
//
//
//static unsigned char led_pattern = 0xFF;  // 当前LED图案
//static unsigned int last_update = 0;
//static unsigned char flow_position = 0;
//static unsigned char wave_index = 0;
//static unsigned char blink_state = 0;
//
//// 初始化LED
//void led_init(void) {
//    LED_PORT = 0xFF; // 初始全灭
//}
//
//// 设置当前效果
//void led_set_effect(LedEffect effect) {
//    current_effect = effect;
//
//    // 重置状态
//    switch (effect) {
//        case LED_EFFECT_ALL_OFF:
//            led_pattern = 0xFF;
//            break;
//        case LED_EFFECT_BREATH:
//            led_pattern = 0xFF;
//            break;
//        case LED_EFFECT_TIDE:
//            led_pattern = 0xFF;
//            break;
//        case LED_EFFECT_ALL_ON:
//            led_pattern = 0x00;
//            break;
//        case LED_EFFECT_FLOW_LEFT:
//            led_pattern = 0xFE; // 11111110
//            flow_position = 0;
//            break;
//        case LED_EFFECT_FLOW_RIGHT:
//            led_pattern = 0x7F; // 01111111
//            flow_position = 0;
//            break;
//        case LED_EFFECT_BLINK_ALL:
//            blink_state = 0;
//            break;
//        case LED_EFFECT_ALTERNATE:
//            led_pattern = 0xAA; // 10101010
//            break;
//        case LED_EFFECT_WAVE:
//            wave_index = 0;
//            break;
//        default:
//            break;
//    }
//
//    // 立即更新LED状态
//    LED_PORT = led_pattern;
//}
//
//// 运行流水灯效果
//static void run_flow(void) {
//    static unsigned int last_flow_update = 0;
//
//    // 检查是否达到更新时间
//    if (last_update - last_flow_update < FLOW_DELAY_MS) {
//        return;
//    }
//    last_flow_update = last_update;
//
//    // 更新流水灯位置
//    flow_position = (flow_position + 1) % 8;
//
//    // 根据方向设置图案
//    if (current_effect == LED_EFFECT_FLOW_LEFT) {
//        led_pattern = (0xFE << flow_position) | (0xFE >> (8 - flow_position));
//    } else {
//        led_pattern = (0x7F >> flow_position) | (0x7F << (8 - flow_position));
//    }
//
//    LED_PORT = led_pattern;
//}
//
//// 运行呼吸效果
//static void run_breath(void) {
//    unsigned char duty; // 占空比控制变量
//    // 从暗到亮：占空比0-100
//    for (duty = 0; duty < 100; duty++) {
//        LED_PORT = 0x00;          // LED全亮
//        delay_us(duty * 5);    // 亮的时间
//        LED_PORT = 0xFF;          // LED全灭
//        delay_us((100 - duty) * 5); // 灭的时间
//    }
//
//    // 从亮到暗：占空比100-0
//    for (duty = 100; duty > 0; duty--) {
//        LED_PORT = 0x00;          // LED全亮
//        delay_us(duty * 5);    // 亮的时间
//        LED_PORT = 0xFF;          // LED全灭
//        delay_us((100 - duty) * 5); // 灭的时间
//    }
//}
//
//// 运行波浪效果
//static void run_wave(void) {
//    static unsigned int last_wave_update = 0;
//    static const unsigned char wave_patterns[] = {
//            0x81, // 10000001
//            0xC3, // 11000011
//            0xE7, // 11100111
//            0xFF, // 11111111
//            0xE7, // 11100111
//            0xC3, // 11000011
//            0x81  // 10000001
//    };
//
//    // 检查是否达到更新时间
//    if (last_update - last_wave_update < FLOW_DELAY_MS) {
//        return;
//    }
//    last_wave_update = last_update;
//
//    // 更新波浪位置
//    wave_index = (wave_index + 1) % (sizeof(wave_patterns) / sizeof(wave_patterns[0]));
//    LED_PORT = wave_patterns[wave_index];
//}
//
//// 运行潮汐灯效果
//static void run_tide(void) {
//    // 静态变量保存状态（初始值：1个LED，递增方向）
//    static unsigned char led_count = 1;
//    static unsigned char direction = 0; // 0=递增，1=递减
//
//    // 计算LED显示模式
//    LED_PORT = 0xFF;           // 先熄灭所有LED
//    LED_PORT <<= (8 - led_count); // 移位操作点亮指定数量的LED
//
//    // 更新状态
//    if (direction == 0) {
//        if (++led_count >= 8) direction = 1; // 递增到8后转为递减
//    } else {
//        if (--led_count <= 1) direction = 0; // 递减到1后转为递增
//    }
//}
//
//// 运行闪烁效果
//static void run_blink(void) {
//    static unsigned int last_blink_update = 0;
//
//    // 检查是否达到更新时间
//    if (last_update - last_blink_update < BLINK_DELAY_MS) {
//        return;
//    }
//    last_blink_update = last_update;
//
//    // 切换闪烁状态
//    blink_state = !blink_state;
//
//    if (current_effect == LED_EFFECT_BLINK_ALL) {
//        LED_PORT = blink_state ? 0x00 : 0xFF; // 全亮或全灭
//    } else {
//        LED_PORT = blink_state ? 0xAA : 0x55; // 交替模式
//    }
//}
//
//// 运行当前效果
//void led_run_effect(void) {
//    // 更新时间计数器
//    last_update++;
//
//    // 根据当前效果执行对应函数
//    switch (current_effect) {
//#if EFFECT_FLOW_LEFT || EFFECT_FLOW_RIGHT
//        case LED_EFFECT_FLOW_LEFT:
//        case LED_EFFECT_FLOW_RIGHT:
//            run_flow();
//            break;
//#endif
//
//#if EFFECT_BREATH
//        case LED_EFFECT_BREATH:
//            run_breath();
//            break;
//#endif
//
//#if EFFECT_WAVE
//        case LED_EFFECT_WAVE:
//            run_wave();
//            break;
//#endif
//
//#if EFFECT_BLINK_ALL || EFFECT_ALTERNATE
//            case LED_EFFECT_BLINK_ALL:
//            case LED_EFFECT_ALTERNATE:
//                run_blink();
//                break;
//#endif
//#if EFFECT_TIDE
//            case LED_EFFECT_TIDE:
//                run_tide();
//                break;
//#endif
//            // 全亮和全灭不需要额外处理
//        case LED_EFFECT_ALL_OFF:
//        case LED_EFFECT_ALL_ON:
//        default:
//            break;
//    }
//}
