#include "config.h"

#if USE_NOKIA_5110_LCD
#include "lcd_nokia5110_display.h"
#include "drivers/display/lcd_nokia5110.h"
#include <stdio.h>

void lcd_nokia5110_display(void) {
    lcd_init();
    lcd_clear();
    while(1){
        lcd_write_string(0, 0, "Hello, World!");
        lcd_write_string(0, 1, "51 Learning");
        lcd_write_string(0, 2, "Nokia 5110 LCD");
        lcd_write_number(0, 3, 12345);
        lcd_write_chinese_string(0,4,12,4,0,5); // 显示中文字符
        delay_ms(1000); // 延时1秒
    }
}
#endif // USE_NOKIA_5110_LCD
