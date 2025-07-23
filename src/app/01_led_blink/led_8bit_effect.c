#include "config.h"

#if USE_LED_8BIT
#include "led_8bit_effect.h"
#include "drivers/display/led_8bit.h"

static void run_effect(void (*effect_func)(void), unsigned char times) {
    for (unsigned char i = 0; i < times; i++) {
        effect_func();
    }
    delay_ms(1000);
}

// 不使用结构体数组，改为硬编码顺序执行
void led_8bit_effect_run(void) {
    // 1. 关闭所有 LED
    run_effect(led_all_off, 1);

    // 2. 全部点亮
    run_effect(led_all_on, 1);

    // 3. 左流动
    run_effect(led_flow_left, 3);

    // 4. 右流动
    run_effect(led_flow_right, 3);

    // 5. 流水灯
    run_effect(led_flow, 3);

    // 6. 反向流水灯
    run_effect(led_flow_reverse, 3);

    // 7. 全闪烁
    run_effect(led_blink_all, 3);

    // 8. 交替闪烁
    run_effect(led_blink_alternate, 3);

    // 9. 呼吸灯
    run_effect(led_breath, 3);

    // 10. 波浪效果
    run_effect(led_wave, 3);

    // 11. 反向波浪
    run_effect(led_wave_reverse, 3);

    // 12. 潮汐效果
    run_effect(led_tide, 3);
}

#endif // USE_LED_8BIT

