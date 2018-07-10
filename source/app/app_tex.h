/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app_tex.h                                               */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 22.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"

#include <gl\gl.h>
#include <gl\glu.h>

/* ------------------------------------------------------------------------------ */

#ifndef __APP_TEX_
#define __APP_TEX_

  /* ............................................................................ */

  #define TEX_NO_ALPHA        "NO_ALPHA"

  #define TEX_EMPTY_NAME      "EMPTY_TEX"
  #define TEX_EMPTY_WIDTH     4
  #define TEX_EMPTY_HEIGHT    4
  #define TEX_EMPTY_BPP       24
  #define TEX_EMPTY_QUAD_SIZE 1

  /* ............................................................................ */
  /*   c_app_tex_data                                                             */

  class c_app_tex_inst
  {
    public :

      t_uint id;

      t_byte* tex_buf;
      t_byte* alpha_buf;

      t_long bpp;
      t_long width;
      t_long height;

      c_app_tex_inst* next;
      c_app_tex_inst* prev;

      /* ........................................................................ */

      t_byte* load_bmp( t_char* tex_name );

      t_byte* load_empty( );

      void apply_alpha( );

      void register_ogl_tex( t_bool  mipmap_flag );

      void kill_buf( );

      void select( );

      void draw( t_float x,
                 t_float y,
                 t_float scale_x,
                 t_float scale_y );

      /* ........................................................................ */

      c_app_tex_inst( t_ulong tex_id, 
                      t_char* tex_name,
                      t_char* alpha_name,
                      t_bool  mipmap_flag );
  };

  /* ............................................................................ */
  /*   c_app_tex                                                                  */

  class c_app_tex
  {
    public :

      t_ulong count;

      c_app_tex_inst* first;
      c_app_tex_inst* last;

      /* ........................................................................ */

      void load( t_char* tex_name, 
                 t_char* alpha_name,
                 t_bool  mipmap_flag );

      void kill_last_buf( );

      /* ........................................................................ */

      c_app_tex( );

      ~c_app_tex( );
  };

  /* ............................................................................ */

  extern c_app_tex_inst* g_tex_manny;
  extern c_app_tex_inst* g_tex_empty;
  extern c_app_tex_inst* g_tex_00;
  extern c_app_tex_inst* g_tex_sky_front;
  extern c_app_tex_inst* g_tex_sky_back;
  extern c_app_tex_inst* g_tex_sky_left;
  extern c_app_tex_inst* g_tex_sky_right;
  extern c_app_tex_inst* g_tex_sky_up;
  extern c_app_tex_inst* g_tex_sky_down;

  /* ............................................................................ */

#endif