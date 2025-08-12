#include "config.h"
#if USE_DIGITRON_4_uart && USE_UART
#include "drivers/display/digitron_4_uart.h"
#include "drivers/communication/uart.h"

#define CR 0x0D     // \r
#define LF 0x0A     // \n

void sent_number_via_uart(unsigned int number) {
    char buffer[4]; // 用于存储4位数字和结束符

    // 将数字转换为字符串，确保是4位，不足前面补0
    for (int i = 3; i >= 0; i--) {
        buffer[i] = (number % 10) + '0';
        number /= 10;
    }

    uart_send_byte('S');
    uart_send_byte('=');
    uart_send_byte(buffer[0]); // 第1位
    uart_send_byte(buffer[1]); // 第2位
    uart_send_byte(buffer[2]); // 第3位
    uart_send_byte(buffer[3]); // 第4位
    uart_send_byte(CR);       // \r
    uart_send_byte(LF);       // \n

}

#endif
