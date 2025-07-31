#include "config.h"
#include "digitron_8_display.h"

#if USE_DIGITRON_8_HC164
#include "drivers/display/digitron_8_hc164.h"
void digitron_8_display_show(void) {
    unsigned long last = -1;
    for (unsigned long i = 0; i < 100000000; i++) {
        if (i != last) {
            set_number(i, 0);
            last = i;
        }
        // 精确延时500ms
        delay_ms_refresh(100);
    }
}
#endif // USE_DIGITRON_8_HC164

#if USE_DIGITRON_8_MAX7219
#include "drivers/display/digitron_8_max7219.h"
void digitron_8_display_show(void) {
    unsigned long last = -1;
    for (unsigned long i = 0; i < 100000000; i++) {
        if (i != last) {
            set_number(i, 1);
            last = i;
        }
        // 精确延时500ms
        delay_ms_refresh(100);
    }
}
#endif // USE_DIGITRON_8_MAX7219

