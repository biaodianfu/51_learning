#include "config.h"
#if USE_DIGITRON_1
#include "drivers/display/digitron_1.h"
#include "digitron_1_display.h"
void digitron_1_display_show() {
    for(unsigned char i = 0; i < 10; i++) {
        show_number(i, 0);
        delay_ms(1000); // 显示每个数字500毫秒
    }
    for(unsigned char i = 0; i < 10; i++) {
        show_number(i, 1); // 显示小数点
        delay_ms(1000); // 显示小数点500毫秒
    }
}

#endif // USE_DIGITRON_1
