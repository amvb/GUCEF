/*
 *  gucefMT: GUCEF module providing multithreading solutions
 *
 *  Copyright (C) 1998 - 2020.  Dinand Vanvelzen
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef GUCEF_MT_ETYPES_H
#define GUCEF_MT_ETYPES_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_PLATFORM_H
#include "gucef_platform.h"
#define GUCEF_PLATFORM_H
#endif /* GUCEF_PLATFORM_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      CONSTANTS                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      Maximum and minimal values for the simple types which we are about to
 *      define.
 */
#define GUCEF_MT_INT8MAX     127
#define GUCEF_MT_INT8MIN     (-128)
#define GUCEF_MT_UINT8MAX    256
#define GUCEF_MT_UINT8MIN    0
#define GUCEF_MT_INT16MAX    32767
#define GUCEF_MT_INT16MIN    (-32767-1)
#define GUCEF_MT_UINT16MAX   65535
#define GUCEF_MT_UINT16MIN   0
#define GUCEF_MT_INT32MAX    2147483647
#define GUCEF_MT_INT32MIN    (-2147483647-1)
#define GUCEF_MT_UINT32MAX   4294967295
#define GUCEF_MT_UINT32MIN   0
#define GUCEF_MT_INT64MIN    -9223372036854775808
#define GUCEF_MT_INT64MAX    9223372036854775807
#define GUCEF_MT_UINT64MIN   0
#define GUCEF_MT_UINT64MAX   18446744073709551615
#define GUCEF_MT_FLOAT32MAX  (3.40282347E+38F)
#define GUCEF_MT_FLOAT32MIN  (-3.40282347E+38F-1)

/*
 *  Legacy remap - deprecated
 */
#define GUCEFMT_INT8MAX     GUCEF_MT_INT8MAX
#define GUCEFMT_INT8MIN     GUCEF_MT_INT8MIN
#define GUCEFMT_UINT8MAX    GUCEF_MT_UINT8MAX
#define GUCEFMT_UINT8MIN    GUCEF_MT_UINT8MIN
#define GUCEFMT_INT16MAX    GUCEF_MT_INT16MAX
#define GUCEFMT_INT16MIN    GUCEF_MT_INT16MIN
#define GUCEFMT_UINT16MAX   GUCEF_MT_UINT16MAX
#define GUCEFMT_UINT16MIN   GUCEF_MT_UINT16MIN
#define GUCEFMT_INT32MAX    GUCEF_MT_INT32MAX
#define GUCEFMT_INT32MIN    GUCEF_MT_INT32MIN
#define GUCEFMT_UINT32MAX   GUCEF_MT_UINT32MAX
#define GUCEFMT_UINT32MIN   GUCEF_MT_UINT32MIN
#define GUCEFMT_FLOAT32MAX  GUCEF_MT_FLOAT32MAX
#define GUCEFMT_FLOAT32MIN  GUCEF_MT_FLOAT32MIN

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifdef __cplusplus
namespace GUCEF {
namespace MT {
#endif /* __cplusplus ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      TYPES                                                              //
//                                                                         //
//-------------------------------------------------------------------------*/

#if GUCEF_COMPILER == GUCEF_COMPILER_MSVC

#ifndef Byte
typedef signed __int8       Byte;     /* 1 byte, signed */
#endif

typedef unsigned __int8     Ubyte;    /* 1 byte, unsigned */

#undef UByte
#define UByte               Ubyte

typedef unsigned __int8     UInt8;    /* 1 byte, unsigned */
typedef signed __int8       Int8;     /* 1 byte, signed */

typedef unsigned __int16    UInt16;   /* 2 bytes, unsigned */
typedef signed __int16      Int16;    /* 2 bytes, signed */

typedef unsigned __int32    UInt32;   /* 4 bytes, unsigned */
typedef signed __int32      Int32;    /* 4 bytes, signed */

typedef signed __int64      Int64;   /* 8 bytes, signed */
typedef unsigned __int64    UInt64;  /* 8 bytes, unsigned */

typedef float               Float32;  /* 4 bytes, signed, decimal */
typedef double              Float64;  /* 8 bytes, signed, decimal */

#else

typedef unsigned char   UInt8;    /* 1 byte, unsigned */
typedef signed char     Int8;     /* 1 byte, signed */

typedef unsigned short  UInt16;   /* 2 bytes, unsigned */
typedef signed short    Int16;    /* 2 bytes, signed */

#if defined(__alpha) || (defined(_MIPS_SZLONG) && _MIPS_SZLONG == 64) || defined(__LP64__)
typedef unsigned int    UInt32;   /* 4 bytes, unsigned */
typedef signed int      Int32;    /* 4 bytes, signed */
#else
typedef unsigned long   UInt32;   /* 4 bytes, unsigned */
typedef signed long     Int32;    /* 4 bytes, signed */
#endif

#ifdef __GNUC__
typedef signed long long   Int64;   /* 8 bytes, signed */
typedef unsigned long long UInt64;  /* 8 bytes, unsigned */
#else
typedef signed __int64   Int64;   /* 8 bytes, signed */
typedef unsigned __int64 UInt64;  /* 8 bytes, unsigned */
#endif

typedef float           Float32;  /* 4 bytes, signed, decimal */
typedef double          Float64;  /* 8 bytes, signed, decimal */

#endif

/*--------------------------------------------------------------------------*/

#define GUCEF_DATATYPE_UNKNOWN      0

#define GUCEF_DATATYPE_FLOAT32      1
#define GUCEF_DATATYPE_FLOAT64      2
#define GUCEF_DATATYPE_UINT8        3
#define GUCEF_DATATYPE_INT8         4
#define GUCEF_DATATYPE_UINT16       5
#define GUCEF_DATATYPE_INT16        6
#define GUCEF_DATATYPE_UINT32       7
#define GUCEF_DATATYPE_INT32        8
#define GUCEF_DATATYPE_UINT64       9
#define GUCEF_DATATYPE_INT64       10

#define GUCEF_DATATYPE_BINARY               20
#define GUCEF_DATATYPE_NUMERIC              21
#define GUCEF_DATATYPE_ASCII_STRING         22
#define GUCEF_DATATYPE_UTF8_STRING          23
#define GUCEF_DATATYPE_UTF16_STRING         24
#define GUCEF_DATATYPE_UTF32_STRING         25
#define GUCEF_DATATYPE_ARRAY                26
#define GUCEF_DATATYPE_OBJECT               27
#define GUCEF_DATATYPE_BOOLEAN_INT32        28
#define GUCEF_DATATYPE_BOOLEAN_ASCII_STRING 29
#define GUCEF_DATATYPE_BOOLEAN_UTF8_STRING  30

#ifdef __cplusplus

/**
 *      Build-in data types as part of an enumeration set
 */
enum EBuildinDataType
{
    DATATYPE_FLOAT32 = GUCEF_DATATYPE_FLOAT32 ,
    DATATYPE_FLOAT64 = GUCEF_DATATYPE_FLOAT64 ,
    DATATYPE_UINT8   = GUCEF_DATATYPE_UINT8   ,
    DATATYPE_INT8    = GUCEF_DATATYPE_INT8    ,
    DATATYPE_UINT16  = GUCEF_DATATYPE_UINT16  ,
    DATATYPE_INT16   = GUCEF_DATATYPE_INT16   ,
    DATATYPE_UINT32  = GUCEF_DATATYPE_UINT32  ,
    DATATYPE_INT32   = GUCEF_DATATYPE_INT32   ,
    DATATYPE_UINT64  = GUCEF_DATATYPE_UINT64  ,
    DATATYPE_INT64   = GUCEF_DATATYPE_INT64   ,

    DATATYPE_UNKNOWN = GUCEF_DATATYPE_UNKNOWN
};
typedef enum EBuildinDataType TBuildinDataType;

enum EBasicDataType
{
    DATATYPE_BINARY         = GUCEF_DATATYPE_BINARY        ,
    DATATYPE_NUMERIC        = GUCEF_DATATYPE_NUMERIC       ,
    DATATYPE_ASCII_STRING   = GUCEF_DATATYPE_ASCII_STRING  ,
    DATATYPE_UTF8_STRING    = GUCEF_DATATYPE_UTF8_STRING   ,
    DATATYPE_ARRAY          = GUCEF_DATATYPE_ARRAY         ,
    DATATYPE_OBJECT         = GUCEF_DATATYPE_OBJECT        ,
    DATATYPE_BOOLEAN        = GUCEF_DATATYPE_BOOLEAN_INT32
};
typedef enum EBasicDataType TBasicDataType;

#endif /* __cplusplus ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifdef __cplusplus
}; /* namespace MT */
}; /* namespace GUCEF */
#endif /* __cplusplus ? */

/*--------------------------------------------------------------------------*/

#endif /* GUCEF_MT_ETYPES_H ? */





