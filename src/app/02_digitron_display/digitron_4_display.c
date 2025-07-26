#include "config.h"
#include "digitron_4_display.h"

#if USE_DIGITRON_4
#include "drivers/display/digitron_4.h"
#elif USE_DIGITRON_4_HC595
#include "drivers/display/digitron_4_hc595.h"
#elif USE_DIGITRON_4_HC595x4
#include "drivers/display/digitron_4_hc595x4.h"
#endif

#if USE_DIGITRON_4 || USE_DIGITRON_4_HC595
void digitron_4_display_show(void) {
    unsigned int i;
    for (i = 0; i < 9999; i++) {
        set_number(i, 0);           // 设置当前数字
        delay_ms_refresh(500);   // 延时并持续刷新数码管
    }
}
#endif

#if USE_DIGITRON_4_HC595x4
void digitron_4_display_show(void) {
    unsigned int i;
    for (i = 0; i < 9999; i++) {
        set_number(i, 0);           // 设置当前数字
        delay_ms(500);   // 延时并持续刷新数码管
    }
}
#endif

#if USE_DIGITRON_4_TM1637
#include "drivers/display/digitron_4_tm1637.h"
void digitron_4_display_show(void) {
    unsigned int i;
    TM1637_init(); // 初始化TM1637
    for (i = 0; i < 9999; i++) {
        TM1637_display_number(i, 1); // 显示当前数字，前导零
        delay_ms(500); // 延时500毫秒
    }
}
#endif