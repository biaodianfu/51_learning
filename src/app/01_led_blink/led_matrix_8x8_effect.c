#include "config.h"
#include "led_matrix_8x8_effect.h"

#if USE_LED_MATRIX_8x8_MAX7219
#include "drivers/display/led_matrix_8x8_max7219.h"
void led_matrix_8x8_show(void) {
    max7219_init(); // 初始化MAX7219芯片
    show_image(&HEART); // 显示心形图案
    delay_ms(1000);
    animate_heart(); // 动画演示心形图案
    delay_ms(1000);
    animate_matrix(); // 动画演示8x8矩阵的点亮效果
    delay_ms(1000);
    animate_square(); // 动画演示正方形的变大变小
    delay_ms(1000);
    show_char('A'); // 显示字符'A'
    delay_ms(1000);
    scroll_text("Hello, World!", 500); // 滚动显示文本
    delay_ms(1000);
}
#endif // USE_LED_MATRIX_8x8_MAX7219
