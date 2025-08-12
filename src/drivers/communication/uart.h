//
// Created by qw on 25-7-12.
//

#ifndef UART_H
#define UART_H

void uart_init(void);
void uart_send_byte(unsigned char byte);
unsigned char uart_receive_byte(void);
void uart_send_string(const char* str);

#endif //UART_H
