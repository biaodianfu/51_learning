//
// Created by qw on 25-7-28.
//
#include "config.h"
#include "digitron_8_display.h"

#if USE_DIGITRON_8_HC164
#include "drivers/display/digitron_8_hc164.h"
void digitron_8_display_show(void) {
    unsigned long last = -1;
    for (unsigned long i = 0; i < 100000000; i++) {
        if (i != last) {
            set_number(i); // 显示数字
            last = i;
        }
    }
}
#endif // USE_DIGITRON_8_HC164

