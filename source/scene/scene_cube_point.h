/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_cube_point.h                                    */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 25.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"

/* ------------------------------------------------------------------------------ */

#ifndef __SCENE_CUBE_POINT_
#define __SCENE_CUBE_POINT_

  /* ............................................................................ */
  /*   c_scene_cube_point                                                         */

  class c_scene_cube_point
  {
    public :

      s_col4f col_begin;
      s_col4f col_end;

      s_coord3d* vert;

      t_byte statuss;
      t_long timer_begin;
      t_long timer_delta;

      /* ........................................................................ */

      void draw( );

      void set( s_coord3d* vert,
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