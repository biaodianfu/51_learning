#include "config.h"
#if USE_DIGITRON_4_uart && USE_UART
#include "drivers/display/digitron_4_uart.h"
#include "drivers/communication/uart.h"

#define CR 0x0D     // \r
#define LF 0x0A     // \n
#define DIGIT_COUNT 4

/**
 * 通过UART发送一个数字到四位数码管显示模块
 *
 * 该函数将一个无符号整数转换为四位数字格式的字符串，
 * 并通过UART接口发送到数码管显示模块进行显示。
 * 数字范围被限制在0000~9999之间，超出范围的数字将被截断为9999。
 * 发送格式为：S=XXXX\r\n，其中XXXX为四位数字。
 *
 * @param number 要发送的无符号整数，有效范围为0~9999
 */
void sent_number_via_uart(unsigned int number) {
    char buffer[DIGIT_COUNT + 1]; // 多分配一个字节用于字符串结束符 '\0'

    // 限制数字范围，确保最多显示四位数（0000~9999）
    if (number > 9999) {
        number = 9999; // 可根据实际需求改为返回错误码或记录日志
    }

    // 将数字转换为固定宽度的字符串（高位补0）
    for (unsigned char i = DIGIT_COUNT - 1; i >= 0; i--) {
        buffer[i] = (number % 10) + '0';
        number /= 10;
    }
    buffer[DIGIT_COUNT] = '\0'; // 确保字符串以 '\0' 结尾

    // 发送数码管显示命令前缀
    uart_send_byte('S');
    uart_send_byte('=');

    // 逐位发送数字字符
    for (unsigned char i = 0; i < DIGIT_COUNT; ++i) {
        uart_send_byte(buffer[i]);
    }

    // 发送命令结束符
    uart_send_byte(CR); // \r
    uart_send_byte(LF); // \n
}

#endif


