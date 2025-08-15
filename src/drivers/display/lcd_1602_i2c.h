#ifndef INC_51_LEARNING_LCD_1602_I2C_H
#define INC_51_LEARNING_LCD_1602_I2C_H

/**
 * @brief 初始化LCD1602模块
 *
 * 包括初始化I2C接口、延时等待LCD上电稳定，
 * 执行特殊的初始化序列以确保进入4位模式，
 * 并设置显示参数。
 */
void lcd1602_init(void);

/**
 * @brief 向LCD发送命令
 *
 * @param cmd 要发送的命令
 */
void lcd1602_cmd(unsigned char cmd);

/**
 * @brief 向LCD发送一个字符数据
 *
 * @param data 要发送的字符数据
 */
void lcd1602_write_char(unsigned char data);

/**
 * @brief 在LCD上显示字符串
 *
 * @param str 指向要显示的字符串的指针
 */
void lcd1602_write_string(const char* str);

/**
 * @brief 设置LCD光标位置
 *
 * @param row 行号（0或1）
 * @param col 列号（0~15）
 */
void lcd1602_set_cursor(unsigned char row, unsigned char col);

/**
 * @brief 清除LCD屏幕
 */
void lcd1602_clear(void);

/**
 * @brief 在LCD上显示无符号整数
 *
 * @param number 要显示的数字
 */
void lcd1602_display_number(unsigned int number);

/**
 * @brief 在LCD上显示字符串（与lcd1602_write_string功能相同）
 *
 * @param str 指向要显示的字符串的指针
 */
void lcd1602_display_string(const char* str);

/**
 * @brief 打开LCD背光
 */
void lcd1602_backlight_on(void);

/**
 * @brief 关闭LCD背光
 */
void lcd1602_backlight_off(void);

/**
 * @brief 控制LCD背光开关
 *
 * @param on 1表示打开背光，0表示关闭背光
 */
void lcd1602_backlight_control(unsigned char on);

#endif //INC_51_LEARNING_LCD_1602_I2C_H
