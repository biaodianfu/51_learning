#ifndef INC_51_LEARNING_OLED_12864_I2C_H
#define INC_51_LEARNING_OLED_12864_I2C_H

/**
 * @brief 初始化OLED 12864显示屏
 *
 * 该函数通过I2C接口对OLED显示屏进行初始化配置，包括显示控制、显示区域、
 * 硬件参数、时序和电压设置等。初始化完成后开启显示功能。
 */
void oled_12864_init(void);

/**
 * @brief 清除OLED屏幕内容
 *
 * 该函数将整个OLED屏幕的显存清零，使屏幕显示为空白。
 */
void oled_12864_clear(void);

/**
 * @brief 打开OLED显示屏
 *
 * 该函数启用OLED的显示功能，使屏幕恢复正常显示状态。
 */
void oled_12864_display_on(void);

/**
 * @brief 关闭OLED显示屏
 *
 * 该函数关闭OLED的显示功能，但不丢失显存中的内容。
 */
void oled_12864_display_off(void);

/**
 * @brief 设置OLED光标位置
 *
 * @param page 页地址，范围0~7
 * @param col 列地址，范围0~127
 *
 * 该函数用于设置OLED写入数据的起始位置。
 */
void oled_12864_set_cursor(unsigned char page, unsigned char col);

/**
 * @brief 在指定位置写入单个字符
 *
 * @param page 页地址，范围0~7
 * @param col 列地址，范围0~127
 * @param ch 要显示的字符
 *
 * 该函数在指定位置显示一个字符，字符宽度为6像素。
 */
void oled_12864_write_char(unsigned char page, unsigned char col, unsigned char ch);

/**
 * @brief 在指定位置写入字符串
 *
 * @param page 页地址，范围0~7
 * @param col 列地址，范围0~127
 * @param str 要显示的字符串
 *
 * 该函数在指定位置显示字符串，自动处理换行和边界检查。
 */
void oled_12864_write_string(unsigned char page, unsigned char col, const char *str);

#endif // INC_51_LEARNING_OLED_12864_I2C_H