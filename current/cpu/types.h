#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef unsigned int u32;
typedef          int i32;
typedef unsigned short u16;
typedef          short i16;
typedef unsigned char u8;
typedef          char i8;
typedef  long long int i64;
typedef unsigned long long int u64;

#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)

#endif
