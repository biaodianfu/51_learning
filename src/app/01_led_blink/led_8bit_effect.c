#include "config.h"
// LED效果展示模块
#if USE_LED_8BIT
#include "led_8bit_effect.h"
#include "drivers/display/led_8bit.h"

// 效果执行辅助函数
static void run_effect(void (*effect_func)(void), unsigned char times) {
    for (unsigned char i = 0; i < times; i++) {
        effect_func();
    }
    delay_ms(1000);
}

// LED效果展示模块
void led_8bit_effect_run(void) {
    // 定义效果列表：{效果函数, 执行次数}
    struct {
        void (*func)(void);
        unsigned char times;
    } effects[] = {
        {led_all_off, 1},          // 关闭所有LED
        {led_all_on, 1},            // 全部点亮
        {led_flow_left, 3},         // 左流动
        {led_flow_right, 3},        // 右流动
        {led_flow, 3},              // 流水灯
        {led_flow_reverse, 3},      // 反向流水灯
        {led_blink_all, 3},         // 全闪烁
        {led_blink_alternate, 3},   // 交替闪烁
        {led_breath, 3},            // 呼吸灯
        {led_wave, 3},              // 波浪效果
        {led_wave_reverse, 3},      // 反向波浪
        {led_tide, 3}               // 潮汐效果
    };

    // 按顺序执行所有效果
    for (unsigned int i = 0; i < sizeof(effects)/sizeof(effects[0]); i++) {
        run_effect(effects[i].func, effects[i].times);
    }
}
#endif // USE_LED_8BIT

