#ifndef INC_51_LEARNING_DIGITRON_8_HC164_H
#define INC_51_LEARNING_DIGITRON_8_HC164_H

/**
 * 设置要在数码管上显示的数字
 * @param num 要显示的数字值
 * @param leading_zero 是否显示前导零，0表示不显示，非0表示显示
 */
void set_number(unsigned long num, unsigned char leading_zero);

/**
 * 延时刷新函数
 * @param t 延时时间，单位为毫秒
 */
void delay_ms_refresh(unsigned int t);

#endif //INC_51_LEARNING_DIGITRON_8_HC164_H

