//
// Created by qw on 25-7-12.
//
#ifndef LED_LINE_8_H
#define LED_LINE_8_H

/**
 * 关闭所有LED灯
 */
void led_all_off(void);

/**
 * 点亮所有LED灯
 */
void led_all_on(void);

/**
 * LED流水灯效果（向左流动）
 */
void led_flow_left(void);

/**
 * LED流水灯效果（向右流动）
 */
void led_flow_right(void);

/**
 * 默认方向流水灯效果
 */
void led_flow(void);

/**
 * 反向流水灯效果
 */
void led_flow_reverse(void);

/**
 * 所有LED同步闪烁效果
 */
void led_blink_all(void);

/**
 * LED交替闪烁效果（奇偶位交替）
 */
void led_blink_alternate(void);

/**
 * LED呼吸灯效果（亮度平滑渐变）
 */
void led_breath(void);

/**
 * LED潮汐效果（类似呼吸灯但具有方向性）
 */
void led_tide(void);

/**
 * LED波浪效果（多个灯依次渐变）
 */
void led_wave(void);

/**
 * 反向波浪效果
 */
void led_wave_reverse(void);

#endif //LED_LINE_8_H

