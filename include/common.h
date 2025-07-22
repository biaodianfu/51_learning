//
// Created by qw on 25-7-12.
//

#ifndef COMMON_H
#define COMMON_H

/**************** 1. 编译器适配 ****************/
#if defined(__SDCC) || defined(SDCC)  // SDCC编译器
    #define __FAR__ __far
    #define CODE     __code
#elif defined(__C51__)                // Keil C51
    #define __FAR__ far
    #define CODE   code
#else
    #define __FAR__
    #define CODE
#endif

/**************** 2. 数据类型标准化 ****************/
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;
typedef signed char  int8_t;
typedef signed short int16_t;
typedef signed long  int32_t;

#endif //COMMON_H
