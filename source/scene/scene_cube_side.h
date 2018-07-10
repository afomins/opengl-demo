/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_cube_side.h                                     */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 30.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"
#include "app\app_tex.h"

/* ------------------------------------------------------------------------------ */

#ifndef __SCENE_CUBE_SIDE_
#define __SCENE_CUBE_SIDE_

  /* ............................................................................ */
  /*   c_scene_cube_side                                                          */

  class c_scene_cube_side
  {
    public :

      s_col4f    col_begin;
      s_col4f    col_end;
      s_coord3d* vert[4];
      s_coord3d  normal;

      t_byte statuss;
      t_long timer_begin;
      t_long timer_delta;

      c_app_tex_inst* tex;

      /* ........................................................................ */

      void draw( );

      void set( s_coord3d*      vert0,
                s_coord3d*      vert1,
                s_coord3d*      vert2,
                s_coord3d*      vert3,
                t_float         begin_r,
                t_float         begin_g,
                t_float         begin_b,
                t_float         begin_a,
                t_float         end_r,
                t_float         end_g,
                t_float         end_b,
                t_float         end_a,
                c_app_tex_inst* tex );

      void appear( t_long delta );

      void fade( t_long delta );

      void build_normal( );
  };

  /* ............................................................................ */

#endif