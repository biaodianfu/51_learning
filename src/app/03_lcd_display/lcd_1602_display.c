#include "config.h"
#if USE_LCD_1602
#include "lcd_1602_display.h"
#include "drivers/display/lcd_1602.h"
void lcd1602_display(void){
    lcd1602_write_string("Hello, World!");
    delay_ms(1000);
    lcd1602_set_cursor(1, 0); // 设置光标到第二行
    lcd1602_write_string("STC89C52RC");
    delay_ms(1000);
    lcd1602_clear();
    lcd1602_set_cursor(0, 0); // 设置光标到第二行
    lcd1602_write_string("Count:");
    delay_ms(1000);
    for (unsigned int i = 0; i <= 9999; i++) {
        lcd1602_set_cursor(1, 0); // 设置光标到第二行
        lcd1602_write_number(i);
        delay_ms(500);
        lcd1602_clear();
    }
}
#endif // USE_LCD_1602
#if USE_LCD_1602_I2C
#include "lcd_1602_display.h"
#include "drivers/display/lcd_1602_i2c.h"

void lcd1602_display(void){
    lcd1602_display_string("Hello, World!");
    delay_ms(1000);
    lcd1602_set_cursor(1, 0); // 设置光标到第二行
    lcd1602_display_string("STC89C52RC");
    delay_ms(1000);
    lcd1602_clear();
    lcd1602_set_cursor(0, 0); // 设置光标到第二行
    lcd1602_display_string("Count:");
    delay_ms(1000);
    for (unsigned int i = 0; i <= 9999; i++) {
        lcd1602_set_cursor(1, 0); // 设置光标到第二行
        lcd1602_display_number(i);
        delay_ms(500);
        lcd1602_clear();
    }
}
#endif // USE_LCD_1602_I2C
