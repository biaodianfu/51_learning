#ifndef INC_51_LEARNING_DIGITRON_8_MAX7219_H
#define INC_51_LEARNING_DIGITRON_8_MAX7219_H

/**
 * 设置要在数码管上显示的数字
 * @param num 要显示的数字值
 * @param leading_zero 是否显示前导零，0表示不显示，非0表示显示
 */
void set_number(unsigned long num, unsigned char leading_zero);

/**
 * 延时函数，用于刷新显示
 * @param ms 延时的毫秒数
 */
void delay_ms_refresh(unsigned int ms);

#endif //INC_51_LEARNING_DIGITRON_8_MAX7219_H

