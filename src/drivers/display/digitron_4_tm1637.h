//
// Created by qw on 25-7-24.
//

#ifndef INC_51_LEARNING_DIGITRON_4_TM1637_H
#define INC_51_LEARNING_DIGITRON_4_TM1637_H
void TM1637_init(void);
void TM1637_display_number(unsigned int num, unsigned char leading_zero);
void TM1637_start(void);
void TM1637_stop(void);
#endif //INC_51_LEARNING_DIGITRON_4_TM1637_H
