#include "config.h"
#if USE_UART
#include "uart.h"

/**
 * @brief 初始化UART串口通信
 *
 * 配置串口工作在模式1（8位数据，可变波特率），使用定时器1产生波特率，
 * 波特率设置为9600（假设晶振频率为11.0592MHz），并使能串口中断和全局中断。
 */
void uart_init(void) {
    SCON = 0x50;
    TMOD &= 0x0F;
    TMOD |= 0x20;
    TH1 = 0xFD;
    TL1 = 0xFD;
    TR1 = 1;
    ES = 1;
    EA = 1;
}

/**
 * @brief 发送一个字节的数据通过UART
 *
 * 将指定的字节写入发送缓冲区，并等待发送完成或超时。
 * 在发送过程中临时禁用全局中断以防止中断干扰标志位。
 *
 * @param byte 要发送的字节数据
 */
void uart_send_byte(unsigned char byte) {
    unsigned int timeout = 0xFFFF;
    SBUF = byte;
    EA = 0;
    while (!TI && --timeout);
    TI = 0;
    EA = 1;
}

/**
 * @brief 接收一个字节的数据通过UART
 *
 * 等待接收完成或超时后，从接收缓冲区读取数据。
 * 在接收过程中临时禁用全局中断以防止中断干扰标志位。
 *
 * @return 接收到的字节数据
 */
unsigned char uart_receive_byte(void) {
    unsigned int timeout = 0xFFFF;
    EA = 0;
    while (!RI && --timeout);
    RI = 0;
    EA = 1;
    return SBUF;
}

/**
 * @brief 发送字符串通过UART
 *
 * 逐个发送字符串中的每个字符直到遇到结束符'\0'。
 *
 * @param str 指向要发送的字符串常量指针
 */
void uart_send_string(const char* str) {
    while (*str) {
        uart_send_byte(*str++);
    }
}

/**
 * @brief UART中断服务函数
 *
 * 占位用的中断服务函数，用于处理串口中断事件。
 * 当前为空实现，可根据需要添加接收处理逻辑。
 */
void uart_isr(void) interrupt 4 {
    // 可在此添加接收处理逻辑
}
#endif // USE_UART


