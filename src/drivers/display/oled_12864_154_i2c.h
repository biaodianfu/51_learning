//#ifndef INC_51_LEARNING_OLED_12864_154_I2C_H
//#define INC_51_LEARNING_OLED_12864_154_I2C_H
///**
// * @brief 初始化OLED显示屏
// *
// * 该函数完成OLED的初始化配置，包括复位、设置显示参数、清屏等操作。
// * 主要配置包括：显示时钟分频、多路复用比、显示偏移、起始行地址、
// * 段/列映射、行扫描方向、COM引脚配置、对比度控制、预充电周期、
// * VCOMH设置等。
// *
// * @param 无
// * @return 无
// */
//void oled_init(void);
//
///**
// * @brief 清除OLED屏幕显示内容
// *
// * 该函数将OLED屏幕的所有像素点设置为0，实现清屏功能。
// * 通过遍历所有页和列，向每个位置写入0x00数据。
// *
// * @param 无
// * @return 无
// */
//void oled_clear(void);
//
///**
// * @brief 设置OLED显示光标位置
// *
// * 该函数设置OLED的显示光标位置，用于指定后续显示内容的位置。
// * 参数col表示列地址(0-127)，page表示页地址(0-7)。
// *
// * @param col 列地址，取值范围0-127
// * @param page 页地址，取值范围0-7
// * @return 无
// */
//void oled_set_cursor(unsigned char col, unsigned char page);
//
///**
// * @brief 开启OLED显示
// *
// * 该函数通过控制DCDC和显示使能位来开启OLED显示。
// *
// * @param 无
// * @return 无
// */
//void oled_display_on(void);
//
///**
// * @brief 关闭OLED显示
// *
// * 该函数通过控制DCDC和显示使能位来关闭OLED显示。
// *
// * @param 无
// * @return 无
// */
//void oled_display_off(void);
//
///**
// * @brief 向OLED写入一个字节数据
// *
// * 该函数通过I2C接口向OLED发送一个字节的数据或命令。
// * 根据mode参数决定是发送数据还是命令。
// *
// * @param dat 要发送的数据字节
// * @param mode 发送模式，OLED_CMD表示命令模式，OLED_DATA表示数据模式
// * @return 无
// */
//void oled_write_byte(unsigned char dat, unsigned char mode);
//
///**
// * @brief 在指定位置显示一个字符
// *
// * 该函数在OLED的指定位置显示一个字符。
// * 字符通过查找字体表获取点阵数据进行显示。
// *
// * @param col 列地址，取值范围0-127
// * @param page 页地址，取值范围0-7
// * @param ch 要显示的字符
// * @return 无
// */
//void oled_show_char(unsigned char col, unsigned char page, char ch);
//
///**
// * @brief 在指定位置显示字符串
// *
// * 该函数在OLED的指定位置显示一个字符串。
// * 通过逐个显示字符实现字符串显示功能。
// *
// * @param col 列地址，取值范围0-127
// * @param page 页地址，取值范围0-7
// * @param str 要显示的字符串指针
// * @return 无
// */
//void oled_show_string(unsigned char col, unsigned char page, const char *str);
//
///**
// * @brief 在指定位置显示数字
// *
// * 该函数在OLED的指定位置显示一个无符号整数。
// * 通过将数字转换为字符串后调用字符串显示函数实现。
// *
// * @param col 列地址，取值范围0-127
// * @param page 页地址，取值范围0-7
// * @param num 要显示的无符号整数
// * @return 无
// */
//void oled_show_number(unsigned char col, unsigned char page, unsigned int num);
//
//void oled_display_inverse(unsigned char mode);
//
//#endif //INC_51_LEARNING_OLED_12864_154_I2C_H
