#include "config.h"
#include "drivers/display/lcd_12864_parallel.h"
void main() {
    // 初始化LCD
    lcd_init();

    // 清屏
    lcd_clear();

    while (1) {
        // 主循环，保持程序运行
        lcd_set_position(0, 0);
        lcd_print("Hello, World!");
        delay_ms(1000); // 延时1秒
        lcd_set_position(1, 0);
        lcd_print("51 Learning");
        delay_ms(1000); // 延时1秒
        lcd_set_position(2, 0);
        lcd_print("你好，世界！"); // 需要将代码文件转化为GB2312编码
        delay_ms(1000); // 延时1秒
    }
}