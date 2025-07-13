//#include "app/01_led_blink/led_effect_show.h"
//
//// LED模块开关
//#define LED_EFFECT_SHOW_ENABLE 1
//
//
//int main(void) {
//    // 只需一行即可初始化并运行模块（如果启用）
//#if LED_EFFECT_SHOW_ENABLE
//    led_effect_module_run();
//#else
//    // 如果未启用，可以添加其他初始化和逻辑
//    while(1) {
//        ;  // 空操作
//    }
//#endif // LED_MODULE_ENABLE
//    return 0;
//}
#include "drivers/display/led_8bit.h"
#include "utils/delay.h"
int main(void) {
    led_init();
    while(1) {
        led_set_effect(LED_EFFECT_TIDE);
        led_run_effect();
    }
 }