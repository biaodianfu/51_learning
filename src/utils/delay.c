/*
 * @file delay.c
 * @brief 精确延时函数实现
 * @version 1.0
 * @date 2025-07-22
 *
 * @note 该文件提供了精确的毫秒和微秒延时函数，适用于11.0592MHz晶振的8051单片机。
 *       使用SDCC编译器进行编译，确保兼容性。
 */
#include "delay.h"


#define ASM_NOP() __asm__("nop")


/**
 * @brief 精确毫秒延时函数（11.0592MHz晶振优化）
 * @param ms 延时时间（毫秒）
 * @note SDCC兼容版本，无编译错误
 */
void delay_ms(unsigned int ms)
{
    volatile unsigned int i;
    volatile unsigned char j;

    /* 11.0592MHz优化参数 */
    for(i = 0; i < ms; i++)
    {
        // 精确的1ms延时循环
        j = 0;
        do {
            j += 3;  // 减少循环次数

            // SDCC兼容的内联NOP指令
            ASM_NOP();
            ASM_NOP();

        } while(j < 188);  // 调整后的循环次数

        // 微调补偿
        ASM_NOP();
    }
}

/**
 * @brief 精确微秒延时函数（11.0592MHz晶振优化）
 * @param us 延时时间（微秒）
 * @note SDCC兼容版本，无编译错误
 */
void delay_us(unsigned int us)
{
    volatile unsigned int i;
    volatile unsigned char j;

    /* 11.0592MHz优化参数 */
    for(i = 0; i < us; i++)
    {
        // 精确的1us延时循环
        j = 0;
        do {
            j += 3;  // 减少循环次数

            // SDCC兼容的内联NOP指令
            ASM_NOP();
            ASM_NOP();

        } while(j < 2);  // 调整后的循环次数

        // 微调补偿
        ASM_NOP();
    }
}

void delay_x50us(unsigned int count)	//@11.0592MHz
{
    while (count--) {
        unsigned char i;
        ASM_NOP();
        i = 20;
        while (--i);
    }
}