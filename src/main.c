#include "config.h"
#include "app/01_led_blink/led_matrix_8x8_effect.h"

int main(void) {
    while (1) {
        led_matrix_8x8_show(); // 调用数码管显示函数
    }
    return 0;
}