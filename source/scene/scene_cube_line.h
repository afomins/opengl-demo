/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_cube_line.h                                     */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 25.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"

/* ------------------------------------------------------------------------------ */

#ifndef __SCENE_CUBE_LINE_
#define __SCENE_CUBE_LINE_

  /* ............................................................................ */
  /*   c_scene_cube_line                                                          */

  class c_scene_cube_line
  {
    public :

      s_col4f    col_begin;
      s_col4f    col_end;
      s_coord3d* vert[2];

      t_byte statuss;
      t_long timer_begin;
      t_long timer_delta;

      t_double  radius;
      s_coord3d vect;

      /* ........................................................................ */

      void draw( );

      void set( s_coord3d* vert0,
                s_coord3d* vert1,
                t_float    begin_r,
                t_float    begin_g,
                t_float    begin_b,
                t_float    begin_a,
                t_float    end_r,
                t_float    end_g,
                t_float    end_b,
                t_float    end_a );

      void appear( t_long delta );

      void fade( t_long delta );
  };

  /* ............................................................................ */

#endif