#pragma once

// Unsigned int types.
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

// Signed int types.
typedef signed char      int8;
typedef signed short     int16;
typedef signed int       int32;
typedef signed long long int64;

// Floating point types
typedef float  float32;
typedef double float64;

#define printfl(x) printf("%s\n", x)
#define DebugLog(...) {                           \
        char str[256];                            \
        sprintf_s(str, sizeof(str), __VA_ARGS__); \
        OutputDebugStringA(str);                  \
    }                                             \
