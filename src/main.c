#include "config.h"
#include "drivers/display/digitron_8_hc164.h"

// 数码管显示函数（修复延时问题）
//void digitron_8_display_show(void) {
//    unsigned long last = -1;
//    for (unsigned long i = 0; i < 100000000; i++) {
//        if (i != last) {
//            set_number(i, 1);
//            last = i;
//        }
//        // 精确延时500ms
//        delay_ms_refresh(100);
//    }
//}

// 主函数
int main(void) {
    while (1) {
        set_number(12345678); // 主循环可以添加其他逻辑
    }
    return 0;
}