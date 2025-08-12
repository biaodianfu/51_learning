#include "config.h"
#include "drivers/communication/uart.h"
#include "app/02_digitron_display/digitron_4_display.h"

void main() {
    uart_init();
    while (1) {
        // 显示数字
        digitron_4_display_show();

        // 其他功能可以在这里添加
        // 例如：LED效果、LCD显示等
    }

}
