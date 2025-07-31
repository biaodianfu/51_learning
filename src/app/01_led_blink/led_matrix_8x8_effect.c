#include "config.h"
#include "led_matrix_8x8_effect.h"

#if USE_LED_MATRIX_8x8_MAX7219
#include "drivers/display/led_matrix_8x8_max7219.h"
void led_matrix_8x8_show(void) {
    // 示例：心形图案（行优先数据）
    unsigned char heart[8] = {
            0x00,  // ░░░░░░░░
            0x66,  // ░▓▓░░▓▓░
            0xFF,  // ▓▓▓▓▓▓▓▓
            0xFF,  // ▓▓▓▓▓▓▓▓
            0x7E,  // ░▓▓▓▓▓▓░
            0x3C,  // ░░▓▓▓▓░░
            0x18,  // ░░░▓▓░░░
            0x00,  // ░░░░░░░░
    };
    display_matrix(heart); // 显示心形图案
//    while (1);               // 主循环，保持显示
}
#endif
