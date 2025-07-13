//
// Created by qw on 25-7-12.
//

#ifndef LED_LINE_8_H
#define LED_LINE_8_H

// LED效果枚举
typedef enum {
    LED_EFFECT_ALL_OFF,      // 全暗
    LED_EFFECT_ALL_ON,       // 全亮
    LED_EFFECT_FLOW_LEFT,    // 左流水灯
    LED_EFFECT_FLOW_RIGHT,   // 右流水灯
    LED_EFFECT_BLINK_ALL,    // 全体闪烁
    LED_EFFECT_ALTERNATE,    // 交替闪烁
    LED_EFFECT_BREATH,       // 呼吸灯
    LED_EFFECT_WAVE,        // 波浪效果
    LED_EFFECT_TIDE          // 潮汐效果
} LedEffect;

// 设置LED效果
void led_set_effect(LedEffect effect);

// 运行当前效果
void led_run_effect(void);

#endif //LED_LINE_8_H
