/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\def\def_type.h                                              */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#ifndef __DEF_TYPE_
#define __DEF_TYPE_

  /* ............................................................................ */

  typedef bool           t_bool;   /* ( 8 )  ( true..false )                      */
  typedef char           t_char;   /* ( 8 )  ( -128..127 )                        */
  typedef unsigned char  t_byte;   /* ( 8 )  ( 0..255 )                           */
  typedef short          t_short;  /* ( 16 ) ( -32,768..32,767 )                  */
  typedef unsigned short t_ushort; /* ( 16 ) ( 0..65,535 )                        */
  typedef long           t_long;   /* ( 32 ) ( -2,147,483,648..2,147,483,647 )    */
  typedef unsigned long  t_ulong;  /* ( 32 ) ( 0..4,294,967,295 )                 */
  typedef __int64        t_dlong;  /* ( 64 ) ( –9,223,372,036,854,775,808..
                                                9,223,372,036,854,775,807 )       */
  typedef float          t_float;  /* ( 32 ) ( 3.4E +/- 38 ) (7 digits)           */
  typedef double         t_double; /* ( 64 ) ( 1.7E +/- 308 ) (15 digits)         */
  typedef int            t_int;    /* ( * )    System dependent                   */
  typedef unsigned int   t_uint;   /* ( * )    System dependent                   */

  /* ............................................................................ */
  /*   coord2                                                                     */

  typedef struct /* s_coord2c                                                     */
  {
    t_char x;
    t_char y; 

  } s_coord2c;

  typedef struct /* s_coord2b                                                     */
  { 
    t_byte x;
    t_byte y;

  } s_coord2b;

  typedef struct /* s_coord2s                                                     */
  { 
    t_short x;
    t_short y;

  } s_coord2s;

  typedef struct /* s_coord2us                                                    */
  {
    t_ushort x;
    t_ushort y; 

  } s_coord2us;

  typedef struct /* s_coord2l                                                     */
  { 
    t_long x;
    t_long y; 

  } s_coord2l;

  typedef struct /* s_coord2ul                                                    */
  {
    t_ulong x;
    t_ulong y; 

  } s_coord2ul;

  typedef struct /* s_coord2f                                                     */
  {
    t_float x;
    t_float y; 

  } s_coord2f;

  typedef struct /* s_coord2d                                                     */
  {
    t_double x;
    t_double y; 

  } s_coord2d;

  /* ............................................................................ */
  /*   coord3                                                                     */

  typedef struct /* s_coord3c                                                     */
  {
    t_char x;
    t_char y;
    t_char z; 

  } s_coord3c;

  typedef struct /* s_coord3b                                                     */
  {
    t_byte x;
    t_byte y;
    t_byte z; 

  } s_coord3b;

  typedef struct /* s_coord3s                                                     */
  {
    t_short x;
    t_short y;
    t_short z; 

  } s_coord3s;

  typedef struct /* s_coord3us                                                    */
  {
    t_ushort x;
    t_ushort y;
    t_ushort z; 

  } s_coord3us;

  typedef struct /* s_coord3l                                                     */
  {
    t_long x;
    t_long y;
    t_long z; 

  } s_coord3l;

  typedef struct /* s_coord3ul                                                    */
  {
    t_ulong x;
    t_ulong y;
    t_ulong z; 

  } s_coord3ul;

  typedef struct /* s_coord3f                                                     */
  {
    t_float x;
    t_float y;
    t_float z; 

  } s_coord3f;

  typedef struct /* s_coord3d                                                     */
  {
    t_double x;
    t_double y;
    t_double z; 

  } s_coord3d;

  /* ............................................................................ */
  /*   col3                                                                       */

  typedef struct /* s_col3b                                                       */
  { 
    t_byte r;
    t_byte g;
    t_byte b; 

  } s_col3b;

  typedef struct /* s_col3f                                                       */
  {
    t_float r;
    t_float g;
    t_float b; 

  } s_col3f;

  /* ............................................................................ */
  /*   col4                                                                       */

  typedef struct /* s_col4b                                                       */
  {
    t_byte r;
    t_byte g;
    t_byte b;
    t_byte a; 

  } s_col4b;

  typedef struct /* s_col4f                                                       */
  {
    t_float r;
    t_float g;
    t_float b;
    t_float a; 

  } s_col4f;

  /* ............................................................................ */
  /*   rect                                                                       */

  typedef struct /* s_rects                                                       */
  {
    t_short x;
    t_short y;
    t_short width;
    t_short height; 

  } s_rects;

  typedef struct /* s_rectl                                                       */
  { 
    t_long x;
    t_long y;
    t_long width;
    t_long height; 

  } s_rectl;

  typedef struct /* s_rectf                                                       */
  {
    t_float x;
    t_float y;
    t_float width;
    t_float height;

  } s_rectf;

  /* ............................................................................ */

#endif