#ifndef CONFIG_H
#define CONFIG_H

# include "common.h"
# include "STC89C5xRC.h"
# include "utils/delay.h"

// 功能模块开关
#define USE_LED_8BIT  0
#define USE_LED_1BIT_5050 0
#define USE_DIGITRON_1 1

// LED效果配置
#if USE_LED_8BIT
#define LED_PORT P2
#define FLOW_DELAY_MS      100     // 流水灯切换间隔
#define BLINK_DELAY_MS     500     // 闪烁间隔
#endif

// LED 1位5050配置
#if USE_LED_1BIT_5050
#define LED_R P20
#define LED_B P21
#define LED_G P22
#endif

// 1位数码管配置
#if USE_DIGITRON_1
// 数码管1位数字显示的引脚定义
// 1位共阳数码管的段码定义
#define DIG_1 P1
#define DIG_A P10
#define DIG_B P11
#define DIG_C P12
#define DIG_D P13
#define DIG_E P14
#define DIG_F P15
#define DIG_G P16
#define DIG_DP P17 // 小数点引脚
#endif // USE_DIGITRON_1




#endif //CONFIG_H

