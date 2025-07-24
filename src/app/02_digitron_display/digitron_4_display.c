#include "config.h"

#if USE_DIGITRON_4
#include "digitron_4_display.h"
#include "utils/delay.h"
#include "drivers/display/digitron_4.h"

void digitron_4_display_show(void) {
    unsigned int i;
    for (i = 0; i < 9999; i++) {
        set_number(i,0);           // 设置当前数字
        delay_ms_refresh(500);   // 延时并持续刷新数码管
    }
}
#endif // USE_DIGITRON_4


#if USE_DIGITRON_4_HC595
#include "digitron_4_display.h"
#include "utils/delay.h"
#include "drivers/display/digitron_4_hc595.h"

void digitron_4_display_show(void) {
    unsigned int i;
    for (i = 0; i < 9999; i++) {
        set_number(i,0);           // 设置当前数字
        delay_ms_refresh(500);   // 延时并持续刷新数码管
    }
}
#endif // USE_DIGITRON_4
