//-----------------------------------------------------------------------------
// types.h -- Basic typedefs for the vm.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- MIT License
//
//-----------------------------------------------------------------------------

#ifndef types_h
#define types_h

/* ----- MSVC Loadout ----- */
#if defined(_MSC_VER)
//unsigned types
typedef unsigned char    uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

//signed types
typedef signed char      int8 ;
typedef __int16          int16;
typedef __int32          int32;
typedef __int64          int64;

//floating point types
typedef float            float32;
typedef double           float64;

//byte-string types
typedef struct bstr32 {
    uint32 length;
    char* data;
} bstr32;
typedef struct bstr64 {
    uint64 length;
    char* data;
} bstr64;


/* ----- GCC Loadout ----- */
#elif defined(__GUNC__)
//unsigned types
typedef unsigned char     uint8;
typedef unsigned short    uint16;
typedef unsigned int      uint32;
typedef unsigned long int uint64;

//signed types
typedef signed char       int8;
typedef signed short      int16;
typedef signed int        int32;
typedef signed long int   int64;

//floating point types
typedef float             float32;
typedef double            float64;


/* ----- Default Loadout (for everybody else) ----- */
#else
//unsigned types
typedef unsigned char     uint8;
typedef unsigned short    uint16;
typedef unsigned int      uint32;
typedef unsigned long int uint64;

//signed types
typedef signed char       int8;
typedef signed short      int16;
typedef signed int        int32;
typedef signed long int   int64;

//floating point types
typedef float             float32;
typedef double            float64;


#endif


#endif //types_h





