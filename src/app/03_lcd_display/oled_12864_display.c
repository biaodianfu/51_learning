#include "config.h"
#if USE_OLED_12864_I2C
#include "oled_12864_display.h"
#include "drivers/display/oled_12864_i2c.h"
void oled_12864_display(void) {
    oled_12864_init(); // 初始化OLED显示
    oled_12864_clear(); // 清屏
    while (1) {
       oled_12864_write_string(0, 0, "Hello, World!");
       oled_12864_write_string(1, 0, "51 Learning");
       oled_12864_write_string(2, 0, "OLED 128x64 I2C");
    }

    // 显示字符串


//    // 显示数字
//    oled_12864_write_number(3, 0, 12345);
//
//
//
//    // 显示中文字符（假设有相应的汉字数据）
//    unsigned char chinese_str[] = {0xB2, 0xE2, 0xB3, 0xA3}; // 示例中文字符GBK编码
//    oled_12864_write_chinese_string(4, 0, chinese_str, sizeof(chinese_str) / 2);
//
//    while (1) {
//        // 循环显示内容
//    }
}
#endif // USE_OLED_12864_I2C
