#ifndef DIGITRON_H
#define DIGITRON_H

/**
 * 在数码管上显示指定的数字
 * @param num 要显示的数字，取值范围为0-9
 * @param dp 小数点控制，0表示不显示小数点，非0表示显示小数点
 */
void show_number(unsigned char num, unsigned char dp);

#endif //DIGITRON_H
