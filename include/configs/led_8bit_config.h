//
// Created by qw on 25-7-12.
//

#ifndef LED_CONFIG_H
#define LED_CONFIG_H

// LED连接端口配置
#define LED_PORT P2


// 流水灯参数
#define FLOW_DELAY_MS      100     // 流水灯切换间隔

// 闪烁参数
#define BLINK_DELAY_MS     500     // 闪烁间隔

// 效果启用开关
#define EFFECT_ALL_OFF      1
#define EFFECT_ALL_ON       1
#define EFFECT_FLOW_LEFT    1
#define EFFECT_FLOW_RIGHT   1
#define EFFECT_BLINK_ALL    1
#define EFFECT_ALTERNATE    1
#define EFFECT_BREATH       1
#define EFFECT_WAVE         1
#define EFFECT_TIDE         1
#endif //LED_CONFIG_H
