/*
  spu.h
        - include with main macros and definitions of libspu and spudrv API project

  Copyright 2019  Dubrovin Egor <dubrovin.en@ya.ru>
                  Alex Popov <alexpopov@bmsru.ru>
                  Bauman Moscow State Technical University
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WOTHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

#ifndef SPU_H
#define SPU_H

/* Use namespace only when compiling C++ */
#ifdef __cplusplus
namespace SPU
{
#endif /* __cplusplus */

/* Used types */
typedef unsigned int  u32;
typedef unsigned char u8;


/* Macro to get right SPU Character Device name */
#define SPU_CDEV_NAME   "spu"

/* Macros of unsigned int's in one SPU data/key unit */
#ifdef SPU32
    #define SPU_WEIGHT 1
#endif
#ifdef SPU64
    #define SPU_WEIGHT 2
#endif
#ifdef SPU128
    #define SPU_WEIGHT 4
#endif
#ifdef SPU256
    #define SPU_WEIGHT 8
#endif

// Global Structure IDentifier weight in 32-bit words
#define GSID_WEIGHT 4

/* Macro to print structure GSID */
/* Only GSID_WEIGHT = 4 supports */
#if GSID_WEIGHT == 4
  #define GSID_FORMAT " %08x-%08x-%08x-%08x "
  #define GSID_VAR(var) \
    var[0], var[1], var[2], var[3]
#endif

// Number of structures in SPU memory
#define SPU_STR_NUM 7

/* SPU commands enumerator */
enum cmd
{
  ADDS = 0x00, // Register new structure special command (not from SPU)
  DEL  = 0x01, // Delete key-value pair
  INS  = 0x02, // Insert key-value pair
  MIN  = 0x03, // Minimum (first) key-value pair by key
  MAX  = 0x04, // Maximum (last) key-value pair by key
  SRCH = 0x05, // Search for key-value pair
  OR   = 0x08, // Binary OR of structures
  AND  = 0x09, // Binary AND of structures
  NOT  = 0x0A, // Binary NOT (minus) of structures
  LSEQ = 0x0B, // Slise less or equal from structure
  LS   = 0x0C, // Slise less from structure
  GREQ = 0x0D, // Slise great or equal from structure
  GR   = 0x0E, // Slise great from structure
  DELS = 0x0F, // Delete structure
  NEXT = 0x10, // Next key-value pair by key
  PREV = 0x11, // Previous key-value pair by key
  NSM  = 0x12, // Next smaller key-value pair by key
  NGR  = 0x13  // Next greater key-value pair by key
}; /* enum cmd */

/* SPU command flags */
enum cmd_flag
{
  Q_FLAG = 0x20, // Add to queue flag
  R_FLAG = 0x40, // Reset queue flag
  P_FLAG = 0x80, // Do polling flag (if 0 - no result will be return)
}; /* cmd_flag */

/* SPU command flags shifts */
enum cmd_flag_shift
{
  Q_FLAG_SHIFT = 5, // Add to queue flag
  R_FLAG_SHIFT = 6, // Reset queue flag
  P_FLAG_SHIFT = 7  // Do polling flag (if 0 - no result will be return)
}; /* cmd_flag_shift */

/* SPU command mask */
enum cmd_mask
{
  CMD_MASK   = 0x1f, // Command mask without any flag
  CMD_TO_SPU = 0x7f  // Command witch can be transfered to SPU (no P flag)
}; /* cmd_mask */

/* SPU result error enumerator */
enum rslt_err
{
  OK  = 0x00,
  ERR = 0x02
}; /* enum rslt_err */

/* Command format 0 - ADDS */
struct cmdfrmt_0
{
  u8 cmd;
};

/* Command format 1 - INS */
struct cmdfrmt_1
{
  u8 cmd;
  u32 gsid[GSID_WEIGHT];
  u32 key[SPU_WEIGHT];
  u32 val[SPU_WEIGHT];
};

/* Command format 2 - SRCH, DEL, NEXT, PREV, NSM, NGR */
struct cmdfrmt_2
{
  u8 cmd;
  u32 gsid[GSID_WEIGHT];
  u32 key[SPU_WEIGHT];
};

/* Command format 3 - DELS, MIN, MAX */
struct cmdfrmt_3
{
  u8 cmd;
  u32 gsid[GSID_WEIGHT];
};

/* Command format 4 - AND, OR, NOT */
struct cmdfrmt_4
{
  u8 cmd;
  u32 gsid_a[GSID_WEIGHT];
  u32 gsid_b[GSID_WEIGHT];
  u32 gsid_r[GSID_WEIGHT];
};

/* Command format 5 - LS, LSEQ, GR, GREQ */
struct cmdfrmt_5
{
  u8 cmd;
  u32 gsid_a[GSID_WEIGHT];
  u32 gsid_r[GSID_WEIGHT];
  u32 key[SPU_WEIGHT];
};

/* Result format 0 - ADDS */
struct rsltfrmt_0
{
  u8 rslt;
  u32 gsid[GSID_WEIGHT];
};

/* Result format 1 - DELS, AND, OR, NOT, LS, LSEQ, GR, GREQ */
struct rsltfrmt_1
{
  u8 rslt;
  u32 power;
};

/* Result format 2 - SRCH, INS, DEL, MIN, MAX, NEXT, PREV, NSM, NGR */
struct rsltfrmt_2
{
  u8 rslt;
  u32 key[SPU_WEIGHT];
  u32 val[SPU_WEIGHT];
  u32 power;
};

/* End of namespace SPU */
#ifdef __cplusplus
} /* namespace SPU */
#endif /* __cplusplus */

#endif /* SPU_H */