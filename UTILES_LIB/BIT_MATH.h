/*
 * BIT_MATH.h
 * Created: 6/3/2025
 * Author: Omar El-Azab
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define setBit(REG, BIT_NUM) REG |= (1 << BIT_NUM)
#define clrBit(REG, BIT_NUM) REG &= (~(1 << BIT_NUM))
#define togBit(REG, BIT_NUM) REG ^= (1 << BIT_NUM)
#define getBit(REG, BIT_NUM) ((REG >> BIT_NUM) & 0X01)

#endif