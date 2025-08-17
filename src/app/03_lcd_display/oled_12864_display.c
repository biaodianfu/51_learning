#include "config.h"
#if USE_OLED_12864_I2C
#include "oled_12864_display.h"
#include "drivers/display/oled_12864_i2c.h"

void oled_12864_display(void) {
    oled_init();
    oled_clear();

    // 初始显示
    oled_display_string(0, 0, "Init Success!");
    delay_ms(1000);
    oled_clear();
    oled_display_turn(1); // 旋转180度显示

    while(1) {
        oled_display_inverse(0);
        oled_display_string(0, 1, "Hello World!");
        oled_display_string(0, 2, "51 Learning");
        oled_display_string(0, 3, "STC89C52RC");
        delay_ms(1000);
        oled_clear();
        oled_display_inverse(1);
        oled_display_string(0, 1, "Hello World!");
        oled_display_string(0, 2, "51 Learning");
        oled_display_string(0, 3, "STC89C52RC");
        oled_display_string(0, 4, "inverse!");
        delay_ms(1000);
        oled_clear();
        }
}

#endif // USE_OLED_12864_154_I2C
