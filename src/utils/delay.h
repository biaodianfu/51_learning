//
// Created by qw on 25-7-12.
//

#ifndef DELAY_H
#define DELAY_H

/**
 * @brief 精确毫秒延时函数
 * @param ms 延时时间（0-65535毫秒）
 */
void delay_ms(unsigned int ms);
void delay_us(unsigned int us);
void delay_x50us(unsigned int count);
#endif //DELAY_H
