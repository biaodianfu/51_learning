#include "config.h"
#if USE_UART
#include "uart.h"


void uart_init(void) {
    SCON = 0x50; // 设置串口工作在模式1：8位数据，可变波特率
    TMOD |= 0x20; // 设置定时器1为模式2：8位自动重载
    TH1 = 0xFD; // 设置波特率为9600（假设晶振频率为11.0592MHz）
    TL1 = 0xFD; // 初始化定时器1的计数值
    TR1 = 1; // 启动定时器1
    ES = 1; // 使能串口中断
    EA = 1; // 全局中断使能
}

void uart_send_byte(unsigned char byte) {
    SBUF = byte; // 将数据写入串口缓冲区，开始发送
    while (!TI); // 等待发送完成
    TI = 0; // 清除发送完成标志
}
unsigned char uart_receive_byte(void) {
    while (!RI); // 等待接收完成
    RI = 0; // 清除接收完成标志
    return SBUF; // 返回接收到的数据
}

void uart_send_string(const char* str) {
    while (*str) {
        uart_send_byte(*str++);
    }
}
#endif // USE_UART

