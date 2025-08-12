#include "config.h"
#include "app/03_lcd_display/lcd_1602_display.h"
#include "drivers/display/lcd_1602_i2c.h"

void main() {
    lcd1602_init();
    lcd1602_backlight_on(); // 打开背光
    while (1) {
        lcd1602_display();
        // 其他功能可以在这里添加
        // 例如：LED效果、LCD显示等
    }

}
