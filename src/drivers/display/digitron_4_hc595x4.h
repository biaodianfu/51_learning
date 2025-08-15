#ifndef INC_51_LEARNING_DIGITRON_4_HC595x4
#define INC_51_LEARNING_DIGITRON_4_HC595x4

/**
 * 设置要在数码管上显示的数字
 * @param num 要显示的数字，范围为0-9999
 * @param leading_zero 是否显示前导零，0表示不显示前导零，非0表示显示前导零
 */
void set_number(unsigned int num, unsigned char leading_zero);

/**
 * 延时函数，用于刷新显示
 * @param t 延时时间，单位为毫秒
 */
void delay_ms_refresh(unsigned int t);

#endif //INC_51_LEARNING_DIGITRON_4_HC595x4

