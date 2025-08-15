/c++
#ifndef LCD_NOKIA5110_H
#define LCD_NOKIA5110_H

/**
 * @brief 初始化Nokia 5110 LCD显示屏
 *
 * 该函数完成LCD的初始化操作，包括复位、配置显示模式、清屏等步骤。
 * 根据供电电压（5V或3.3V）设置不同的偏置电压。
 */
void lcd_init(void);

/**
 * @brief 向LCD写入一个字节数据或命令
 *
 * @param dat 要写入的数据
 * @param cmd 命令标志：0表示写命令，1表示写数据
 *
 * 通过模拟SPI方式将数据/命令逐位发送到LCD控制器。
 */
void lcd_write_byte(unsigned char dat, unsigned char cmd);

/**
 * @brief 设置LCD显示光标位置
 *
 * @param x 列地址 (0-83)
 * @param y 行地址 (0-5)，每行8像素高
 *
 * 将LCD的显示光标定位到指定的行列位置。
 */
void lcd_set_cursor(unsigned char x, unsigned char y);

/**
 * @brief 清除LCD屏幕内容
 *
 * 将整个LCD屏幕内容清零，即显示为空白。
 */
void lcd_clear(void);

/**
 * @brief 在LCD上显示一个字符
 *
 * @param ch 要显示的字符ASCII码值
 *
 * 显示字符前会减去32以匹配字体数组索引。
 */
void lcd_write_char(unsigned char ch);

/**
 * @brief 在LCD指定位置显示字符串
 *
 * @param x 起始列地址
 * @param y 起始行地址
 * @param str 指向要显示的字符串指针
 *
 * 从指定位置开始依次显示字符串中的每个字符。
 */
void lcd_write_string(unsigned char x, unsigned char y, char *str);

/**
 * @brief 在LCD指定位置显示数字
 *
 * @param x 起始列地址
 * @param y 起始行地址
 * @param num 要显示的无符号整数
 *
 * 将数字转换为字符串后在LCD上显示。
 */
void lcd_write_number(unsigned char x, unsigned char y, unsigned int num);

/**
 * @brief 在LCD上显示中文字符串
 *
 * @param x 起始列地址
 * @param y 起始行地址
 * @param ch_width 每个汉字的宽度（像素）
 * @param num 要显示的汉字数量
 * @param line 字库中汉字的起始行号
 * @param line_space 汉字之间的间隔像素数
 *
 * 支持12x12点阵汉字显示，根据LCD扫描方式处理上下半部分显示。
 */
void lcd_write_chinese_string(unsigned char x, unsigned char y, unsigned char ch_width, unsigned char num,
                              unsigned char line, unsigned char line_space);

/**
 * @brief 在LCD上绘制位图
 *
 * @param x 起始列地址
 * @param y 起始行地址
 * @param width 位图宽度（像素）
 * @param height 位图高度（像素）
 * @param map 指向位图数据的指针
 *
 * 根据位图高度计算占用行数，并逐行写入位图数据。
 */
void lcd_draw_bmp_pixel(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char *map);

#endif //LCD_NOKIA5110_H
