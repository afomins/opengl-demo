/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\def\def_str.h                                               */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

#include "def_type.h"

/* ------------------------------------------------------------------------------ */

#ifndef __DEF_STR_
#define __DEF_STR_

  /* ............................................................................ */

  #define STR_MAX_LEN 4096

  /* ............................................................................ */

  t_char* crt_str( t_long  prefix, 
                   t_char* postfix );

  t_char* crt_str( t_char* prefix, 
                   t_long  postfix );

  t_char* crt_str( t_double prefix, 
                   t_long   digits,
                   t_char*  postfix );

  t_char* crt_str( t_char*  prefix, 
                   t_double postfix,
                   t_long   digits );

  t_char* crt_str( t_char* prefix,
                   t_char* postfix );

  t_char* crt_str( t_long  prefix );

  t_char* crt_str( t_double prefix,
                   t_long   digits );

  /* ............................................................................ */

#endif