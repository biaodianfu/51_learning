#ifndef UART_H
#define UART_H

/**
 * @brief 初始化UART串口通信
 *
 * 配置UART的波特率、数据位、停止位和校验位等参数，
 * 使能UART模块，准备进行串口数据收发。
 */
void uart_init(void);

/**
 * @brief 发送一个字节数据
 *
 * 通过UART串口发送指定的字节数据。
 *
 * @param byte 要发送的字节数据
 */
void uart_send_byte(unsigned char byte);

/**
 * @brief 接收一个字节数据
 *
 * 从UART串口接收一个字节数据。
 *
 * @return 接收到的字节数据
 */
unsigned char uart_receive_byte(void);

/**
 * @brief 发送字符串
 *
 * 通过UART串口发送以null结尾的字符串。
 *
 * @param str 指向要发送的字符串的指针
 */
void uart_send_string(const char* str);

#endif //UART_H

