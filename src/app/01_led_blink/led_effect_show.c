//
// Created by qw on 25-7-12.
//
#include "led_effect_show.h"
#include "utils/delay.h"
#include "drivers/display/led_8bit.h"
#include "configs/led_8bit_config.h"

// LED效果演示序列
static const LedEffect effect_sequence[] = {
#if EFFECT_ALL_OFF
        LED_EFFECT_ALL_OFF,
#endif

#if EFFECT_ALL_ON
        LED_EFFECT_ALL_ON,
#endif

#if EFFECT_FLOW_LEFT
        LED_EFFECT_FLOW_LEFT,
#endif

#if EFFECT_FLOW_RIGHT
        LED_EFFECT_FLOW_RIGHT,
#endif

#if EFFECT_BLINK_ALL
        LED_EFFECT_BLINK_ALL,
#endif

#if EFFECT_ALTERNATE
        LED_EFFECT_ALTERNATE,
#endif

#if EFFECT_BREATH
        LED_EFFECT_BREATH,
#endif

#if EFFECT_WAVE
        LED_EFFECT_WAVE,
#endif
};

// 当前效果索引
static unsigned char current_effect_index = 0;
static unsigned int effect_start_time = 0;
static unsigned int system_time = 0;

// 初始化LED效果
void led_effect_init(void) {
    if (sizeof(effect_sequence) > 0) {
        led_set_effect(effect_sequence[0]);
        effect_start_time = 0;
    }
}

// 运行LED效果（在主循环中调用）
void led_effect_run(unsigned int current_time) {
    // 设置开始时间
    if (effect_start_time == 0) {
        effect_start_time = current_time;
    }

    // 每3秒切换一次效果
    if (current_time - effect_start_time > 3000) {
        effect_start_time = current_time;

        // 切换到下一个效果
        current_effect_index = (current_effect_index + 1) % (sizeof(effect_sequence) / sizeof(LedEffect));
        led_set_effect(effect_sequence[current_effect_index]);
    }

    // 运行当前效果
    led_run_effect();
}

// 新增运行函数 - 包含完整的循环逻辑
void led_effect_module_run(void) {
    led_init();
    led_effect_init();
    while (1) {
        system_time++;
        led_effect_run(system_time);
        delay_ms(1);
    }
}

