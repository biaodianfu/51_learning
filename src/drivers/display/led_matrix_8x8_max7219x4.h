#ifndef INC_51_LEARNING_LED_MATRIX_8X8_MAX7219X4_H
#define INC_51_LEARNING_LED_MATRIX_8X8_MAX7219X4_H

// 结构体定义
typedef struct {
    unsigned char data[8];
} Image;

/**
 * @brief 初始化MAX7219芯片
 * 配置解码模式、亮度、扫描位数、工作模式和显示测试
 */
void max7219_init(void);

/**
 * @brief 在LED矩阵上显示四个字符
 * @param dat1 第一个字符
 * @param dat2 第二个字符
 * @param dat3 第三个字符
 * @param dat4 第四个字符
 */
void led_print(unsigned char dat1, unsigned char dat2, unsigned char dat3, unsigned char dat4);

#endif //INC_51_LEARNING_LED_MATRIX_8X8_MAX7219X4_H
