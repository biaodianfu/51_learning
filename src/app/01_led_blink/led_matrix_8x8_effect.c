#include "config.h"
#include <string.h>
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

#if USE_LED_MATRIX_8x8_HC595
#include "drivers/display/led_matrix_8x8_hc595.h"
void led_matrix_8x8_show(void) {
    show_image(&HEART_SMALL); // 显示小心形图案
    animate_heart(); // 动画演示心形图案
    animate_square(); // 动画演示正方形的变大变小
    show_char('A'); // 显示字符'A'
    scroll_text("Hello, World!", 500); // 滚动显示文本
}
#endif // USE_LED_MATRIX_8x8_HC595

#if USE_LED_MATRIX_8x8_MAX7219x4
#include "drivers/display/led_matrix_8x8_max7219x4.h"
void led_matrix_8x8_show(void) {
    max7219_init(); // 初始化MAX7219
    static int index = 0; // 静态变量记录当前索引
    const char *str = "HELLO WORLD 123"; // 目标字符串
    int len = strlen(str); // 字符串长度
    unsigned char buffer[4]; // 存储4个字符的缓冲区

    while (1) {
        // 填充4个字符到缓冲区
        for (int i = 0; i < 4; i++) {
            int pos = index + i;
            if (pos < len) {
                buffer[i] = str[pos]; // 有效字符
            } else {
                buffer[i] = ' '; // 超出长度时填充空格
            }
        }

        // 调用显示函数
        led_print(buffer[3], buffer[2], buffer[1], buffer[0]);

        // 更新索引（循环逻辑）
        index = (index + 1) % (len + 1); // +1确保滚动到末尾后重置
        delay_ms(1000); // 延时500毫秒
    }
}
#endif