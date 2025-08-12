#include "config.h"
#include "app/03_lcd_display/lcd_1602_display.h"
#include "drivers/display/lcd1602.h"

void main() {
    while (1) {
        // 显示数字
        lcd1602_init();
        lcd_1602_display();

        // 其他功能可以在这里添加
        // 例如：LED效果、LCD显示等
    }

}
