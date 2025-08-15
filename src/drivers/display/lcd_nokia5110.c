#include "config.h"

#if USE_NOKIA_5110_LCD

#include "lcd_nokia5110.h"
#include "font.h"

/**
 * @brief 初始化Nokia 5110 LCD显示屏
 * 
 * 该函数完成LCD的初始化操作，包括复位、配置显示模式、清屏等步骤。
 * 根据供电电压（5V或3.3V）设置不同的偏置电压。
 */
void lcd_init(void) {
    LCD_RST = 0;
    delay_us(1);
    LCD_RST = 1;
    // 关闭LCD
    LCD_CE = 0;
    delay_us(1);
    // 使能LCD
    LCD_CE = 1;
    delay_us(1);

    lcd_write_byte(0x21, 0);    // 使用扩展命令设置LCD模式
    lcd_write_byte(0xBE, 0);    // 设置偏置电压  /*5110接5V时偏置电压改为（0xBE,0）,接3.3V时改为（0xc0,0）*/
    lcd_write_byte(0x06, 0);    // 温度校正
    lcd_write_byte(0x13, 0);    // 1:48
    lcd_write_byte(0x20, 0);    // 使用基本命令
    lcd_clear();            // 清屏
    lcd_write_byte(0x0C, 0);    // 设定显示模式，正常显示
    // 关闭LCD
    LCD_CE = 0;
}

/**
 * @brief 向LCD写入一个字节数据或命令
 * 
 * @param dat 要写入的数据
 * @param cmd 命令标志：0表示写命令，1表示写数据
 * 
 * 通过模拟SPI方式将数据/命令逐位发送到LCD控制器。
 */
void lcd_write_byte(unsigned char dat, unsigned char cmd) {
    LCD_CE = 0;
    LCD_DC = (cmd == 0) ? 0 : 1;
    for (unsigned char i = 0; i < 8; i++) {
        SDIN = (dat >> 7) & 0x01;
        SCLK = 0;
        delay_us(1);
        dat = dat << 1;
        SCLK = 1;
        delay_us(1);
    }
    LCD_CE = 1;
}

/**
 * @brief 设置LCD显示光标位置
 * 
 * @param x 列地址 (0-83)
 * @param y 行地址 (0-5)，每行8像素高
 * 
 * 将LCD的显示光标定位到指定的行列位置。
 */
void lcd_set_cursor(unsigned char x, unsigned char y) {
    lcd_write_byte(0x80 | x, 0);
    lcd_write_byte(0x40 | y, 0);
}

/**
 * @brief 清除LCD屏幕内容
 * 
 * 将整个LCD屏幕内容清零，即显示为空白。
 */
void lcd_clear(void) {
    lcd_set_cursor(0, 0);
    for (unsigned char row = 0; row < LCD_WIDTH; row++) {
        for (unsigned char col = 0; col < LCD_ROW; col++) {
            lcd_write_byte(0x00, 1);
        }
    }
}

/**
 * @brief 在LCD上显示一个字符
 * 
 * @param ch 要显示的字符ASCII码值
 * 
 * 显示字符前会减去32以匹配字体数组索引。
 */
void lcd_write_char(unsigned char ch) {
    ch -= 32;
    for (unsigned char line = 0; line < LCD_ROW; line++) {
        lcd_write_byte(FONT_8X6[ch][line], 1);
    }
}

/**
 * @brief 在LCD指定位置显示字符串
 * 
 * @param x 起始列地址
 * @param y 起始行地址
 * @param str 指向要显示的字符串指针
 * 
 * 从指定位置开始依次显示字符串中的每个字符。
 */
void lcd_write_string(unsigned char x, unsigned char y, char *str) {
    lcd_set_cursor(x, y);
    while (*str)
        lcd_write_char(*str++);
}

/**
 * @brief 在LCD指定位置显示数字
 * 
 * @param x 起始列地址
 * @param y 起始行地址
 * @param num 要显示的无符号整数
 * 
 * 将数字转换为字符串后在LCD上显示。
 */
void lcd_write_number(unsigned char x, unsigned char y, unsigned int num) {
    unsigned char str[8];
    unsigned char i = 0;

    // 处理特殊情况：num = 0
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        lcd_write_string(x, y, (char *) str);
        return;
    }

    // 从个位开始提取数字字符
    unsigned int temp = num;
    while (temp && i < 7) {  // 保留一个字符用于结束符
        str[i++] = (temp % 10) + '0';
        temp /= 10;
    }

    // 添加字符串结束符
    str[i] = '\0';

    // 反转字符串
    unsigned char len = i;
    for (unsigned char j = 0; j < len / 2; j++) {
        unsigned char temp_char = str[j];
        str[j] = str[len - 1 - j];
        str[len - 1 - j] = temp_char;
    }

    lcd_write_string(x, y, (char *) str);
}

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
                              unsigned char line, unsigned char line_space) {
    lcd_set_cursor(x, y);
    for (unsigned char i = 0; i < num; i++) {//写第i个汉字
        for (unsigned char n = 0; n < ch_width * 2; n++)  //n代表数组中的第n个数值，ch_with是汉字点阵的宽度，
            //程序定义的是12*12的，但是数组中有24个数值，前面12个为上半部，后面的为下半部
        { //这是因为5110的扫描方式是采用列行似的
            if (n == ch_width)  //在调用此函数时可知ch_with=12；在这里n==ch_with说明第i个汉字上半部分是否已经写完
            {
                if (i == 0)    //如果它还是第一个字的话，列地址（x）不变，行地址（Y）+1，
                    lcd_set_cursor(x, y + 1);//调到第二行写下半部分
                else   //如果不为0，说明前面已经写有字符了，那么列地址x就要加上（字的宽度+字符之间的间隔）*i个字
                    lcd_set_cursor((x + (ch_width + line_space) * i), y + 1);//来转到下一个字的起始列地址，，Y+1即跳到下一行写字的下半部分
            }
            lcd_write_byte(FONT_12X12[line + i][n], 1); //这里的1为写数据，写write_chinese[line+i][n]里的数据。
        }  //write_chinese是2维数组，所以line的值表示选择写数组中的哪个字，+i就接着写下一个，那就是一个字的第即个字节
        lcd_set_cursor((x + (ch_width + line_space) * (i + 1)), y);//列地址x跳到下一个字符的起始位置，行地址y回到字符上半部分的起始地址
    }
}

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
void
lcd_draw_bmp_pixel(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char *map) {
    unsigned int i, n;
    unsigned char row;
    //计算位图所占行数
    if (height % 8 == 0)        //如果为位图所占行数为整数
        row = height / 8;
    else
        row = height / 8 + 1;        //如果为位图所占行数不是整数

    for (n = 0; n < row; n++)        //换行
    {
        lcd_set_cursor(x, y + n);
        for (i = 0; i < width; i++) {
            lcd_write_byte(map[i + n * width], 1);
        }
    }
}

#endif
