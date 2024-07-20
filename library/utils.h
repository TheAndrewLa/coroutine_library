// by andrew.la

#ifndef LIBRARY_UTILS_H
#define LIBRARY_UTILS_H

#include <stdint.h>
#include <stddef.h>

/// @todo PLATFORM RECOGNITION by #define directive

#define LO_WORD(dword) ((u16) ((dword) & 0xFFFF))
#define HI_WORD(dword) ((u16) ((((u32) (dword)) >> 16) & 0xFFFF))

#define CREATE_DWORD(lo_word, hi_word) ((u32) ((lo_word) | (((u32) (hi_word)) << 16)))

#define LO_DWORD(qword) ((u32) ((qword) & 0xFFFFFFFF))
#define HI_DWORD(qword) ((u32) ((((u64) (qword)) >> 32) & 0xFFFFFFFF))

#define CREATE_QWORD(lo_dword, hi_dword) ((u64) ((lo_dword) | (((u64) (hi_dword)) << 32)))

#define FALSE (0)
#define TRUE (1)

typedef uint8_t u8;
typedef int8_t i8;

typedef uint16_t u16;
typedef int16_t i16;

typedef uint32_t u32;
typedef int32_t i32;

typedef uint64_t u64;
typedef int64_t i64;

typedef size_t usize;
typedef ptrdiff_t isize;

typedef uint8_t bool8;
typedef uint16_t bool16;
typedef uint32_t bool32;

#endif
