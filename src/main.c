#include "config.h"
#include "app/02_digitron_display/digitron_8_display.h"

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
        digitron_8_display_show(); // 调用数码管显示函数
        delay_ms(100); // 延时100ms，避免过快刷新
    }
    return 0;
}