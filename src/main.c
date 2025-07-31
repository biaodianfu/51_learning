#include "config.h"
#include "app/01_led_blink/led_matrix_8x8_effect.h"

// 主函数
int main(void) {
    while (1) {
        led_matrix_8x8_show(); // 调用数码管显示函数
        delay_ms(100); // 延时100ms，避免过快刷新
    }
    return 0;
}