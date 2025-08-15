#ifndef LCD1602_H
#define LCD1602_H

/**
 * @brief 初始化LCD1602显示屏
 *
 * 配置LCD1602的工作模式和初始状态
 */
void lcd1602_init(void);

/**
 * @brief 向LCD1602写入单个字符
 *
 * @param data 要写入的字符数据
 */
void lcd1602_write_char(unsigned char data);

/**
 * @brief 向LCD1602写入字符串
 *
 * @param str 指向要写入的字符串的指针
 */
void lcd1602_write_string(const char* str);

/**
 * @brief 设置LCD1602光标位置
 *
 * @param row 行号(0-1)
 * @param col 列号(0-15)
 */
void lcd1602_set_cursor(unsigned char row, unsigned char col);

/**
 * @brief 清除LCD1602显示屏
 *
 * 清空屏幕显示内容并重置光标位置
 */
void lcd1602_clear(void);

/**
 * @brief 向LCD1602发送命令
 *
 * @param command 要发送的命令字节
 */
void lcd_send_command(unsigned char command);

/**
 * @brief 在LCD1602上显示数字
 *
 * @param number 要显示的无符号整数
 */
void lcd1602_write_number(unsigned int number);

#endif //LCD1602_H
