#ifndef INC_51_LEARNING_DIGITRON_4_UART_H
#define INC_51_LEARNING_DIGITRON_4_UART_H

/**
 * 通过UART串口发送数字
 *
 * @param number 要发送的无符号整数
 *
 * @note 该函数将数字转换为字符串并通过UART串口发送出去
 */
void sent_number_via_uart(unsigned int number);

#endif //INC_51_LEARNING_DIGITRON_4_UART_H
