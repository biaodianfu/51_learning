
#include "drivers/display/led_1bit_5050.h"
#include "utils/delay.h"

int main(void) {

    while (1) {
//        // 名称颜色设置
//        set_color("blue");
//        delay_ms(1000); // 等待1秒
//        set_color_bright("green", 128); // 50%亮度绿色
//        delay_ms(1000); // 等待1秒
//
//// 十六进制颜色设置
//        set_color_hex("FF0000");       // 红色
//        delay_ms(1000); // 等待1秒
//        set_color_hex("#00FF00");      // 绿色
//        delay_ms(1000); // 等待1秒
//        set_color_hex_bright("0000FF", 64); // 25%亮度蓝色
//        delay_ms(1000); // 等待1秒
//
//// 简写格式
//        set_color_hex("#F00");         // 红色
//        delay_ms(1000); // 等待1秒
//        set_color_hex_bright("#0F0", 192); // 75%亮度绿色
//        delay_ms(1000); // 等待1秒
        // 呼吸灯效果
        breathing_effect_color("purple");
        delay_ms(2000); // 等待2秒

        // 彩虹效果
        rainbow_effect();
        delay_ms(2000); // 等待2秒

        // 其他LED效果可以在这里调用
    }

}