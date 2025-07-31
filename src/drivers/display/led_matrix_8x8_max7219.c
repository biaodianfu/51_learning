#include "config.h"
#if USE_LED_MATRIX_8x8_MAX7219
#include "led_matrix_8x8_max7219.h"

/**
 * @brief 向MAX7219发送一个字节数据，带延时以确保信号稳定。
 *
 * 该函数通过软件模拟SPI方式逐位发送数据。在每个时钟周期中，
 * 先拉低时钟线，设置数据线，插入短延时后拉高时钟线完成一位传输。
 *
 * @param data 要发送的字节数据
 */
void write_max7219_byte_with_delay(unsigned char data) {
    for (unsigned char i = 0; i < 8; i++) {
        MAX7219_CLK = 0;
        MAX7219_DIN = (data & 0x80) ? 1 : 0;
        data <<= 1;

        // 短延时确保信号稳定
        ASM_NOP(); ASM_NOP(); ASM_NOP();
        ASM_NOP(); ASM_NOP(); ASM_NOP();

        MAX7219_CLK = 1;
        ASM_NOP(); ASM_NOP(); ASM_NOP();
    }
}

/**
 * @brief 向MAX7219写入指定地址的数据。
 *
 * 通过CS片选控制开始和结束通信过程，依次发送地址和数据两个字节。
 *
 * @param addr 寄存器地址
 * @param data 要写入的数据
 */
void max7219_write(unsigned char addr, unsigned char data) {
    MAX7219_CS = 0;
    write_max7219_byte_with_delay(addr);
    write_max7219_byte_with_delay(data);
    MAX7219_CS = 1;
    MAX7219_CLK = 0;
}

/**
 * @brief 初始化MAX7219芯片。
 *
 * 配置MAX7219的工作参数，包括译码模式、亮度、扫描位数、工作模式及显示测试状态。
 */
void max7219_init() {
    max7219_write(0x09, 0x00);   // 解码模式：不译码
    max7219_write(0x0A, 0x01);   // 亮度设置（范围0x00-0x0F）
    max7219_write(0x0B, 0x07);   // 扫描位数：8位（0-7）
    max7219_write(0x0C, 0x01);   // 工作模式：正常
    max7219_write(0x0F, 0x00);   // 显示测试：关闭
}

/**
 * @brief 显示8x8点阵图案。
 *
 * 将传入的图案数组按行写入到MAX7219对应的显示寄存器中。
 * 每个数组元素对应一行的显示内容。
 *
 * @param pattern 指向包含8个字节的数组，每个字节代表一行的显示数据
 */
void display_matrix(unsigned char *pattern) {
    if (pattern == NULL) {
        return; // 防止空指针访问
    }

    for (unsigned char i = 0; i < 8; i++) {
        max7219_write(i + 1, pattern[i]); // 行地址从1开始（DIG0对应地址0x01）
    }
}
#endif