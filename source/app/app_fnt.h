/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app_fnt.h                                              */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 23.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"
#include "app\app_tex.h"

/* ------------------------------------------------------------------------------ */

#ifndef __APP_FNT_
#define __APP_FNT_

  /* ............................................................................ */

  #define FNT_LET_MAX_COUNT 256

  /* ............................................................................ */

  typedef struct
  {
    t_float sx;
    t_float sy;
    t_float ex;
    t_float ey;

    t_byte width;
    t_byte height;

  } s_app_fnt_let_inst;

  /* ............................................................................ */
  /*   c_app_fnt_inst                                                             */

  class c_app_fnt_inst
  {
    public :

      t_ulong id;

      t_ulong first_list_id;

      t_byte let_count;

      c_app_fnt_inst* next;
      c_app_fnt_inst* prev;

      c_app_tex_inst* tex_inst;

      s_coord2s let_size;

      s_app_fnt_let_inst let[FNT_LET_MAX_COUNT];

      /* ........................................................................ */

      void draw( t_long  index,
                 t_float x,
                 t_float y,
                 t_float scale_x,
                 t_float scale_y );

      void str_out( t_char* str,
                    t_float x,
                    t_float y,
                    t_float scale_x,
                    t_float scale_y );

      /* ........................................................................ */

      c_app_fnt_inst( c_app_tex* tex,
                      t_ulong    fnt_id,
                      t_char*    tex_name,
                      t_char*    alpha_name,
                      t_byte     let_width,
                      t_byte     let_height );

  };

  /* ............................................................................ */
  /*   c_app_fnt                                                                  */

  class c_app_fnt
  {
    public :

      t_ulong count;

      c_app_tex* tex;

      c_app_fnt_inst* first;
      c_app_fnt_inst* last;

      /* ........................................................................ */

      void load( t_char* tex_name,
                 t_char* alpha_alpha,
                 t_byte  let_width,
                 t_byte  let_height );

      /* ........................................................................ */

      c_app_fnt( c_app_tex* tex );

      ~c_app_fnt( );
  };

  /* ............................................................................ */

  extern c_app_fnt_inst* g_f_std;

  /* ............................................................................ */

#endif
