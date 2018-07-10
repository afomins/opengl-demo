/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_cube.h                                          */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 24.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"
#include "scene\scene_cube_point.h"
#include "scene\scene_cube_line.h"
#include "scene\scene_cube_side.h"

/* ------------------------------------------------------------------------------ */

#ifndef __SCENE_CUBE_
#define __SCENE_CUBE_

  /* ............................................................................ */

  #define CUBE_VERT_COUNT  8
  #define CUBE_POINT_COUNT 8
  #define CUBE_LINE_COUNT  12
  #define CUBE_SIDE_COUNT  6
  #define CUBE_SIZE        1

  /* ............................................................................ */
  /*   c_scene_cube                                                               */

  class c_scene_cube
  {
    public :

      /* ........................................................................ */

      t_bool draw_flag;

      /* ........................................................................ */

      /* ........................................................................ */

    public :

      t_bool draw_point_flag;
      t_bool draw_line_flag;
      t_bool draw_side_flag;

      s_coord3d*          vert;
      c_scene_cube_point* point;
      c_scene_cube_line*  line;
      c_scene_cube_side*  side;

      t_double  rot_angle;
      t_double  rot_speed;
      s_coord3d rot_vect;

      s_coord3d center;

      /* ........................................................................ */

      void draw( );

      /* ........................................................................ */

      void set_vert( t_long   vert_id,
                     t_double x,
                     t_double y,
                     t_double z );

      void rand_line_vert( );

      /* ........................................................................ */

      void appear_points( t_long delta );

      void fade_points( t_long delta );

      void appear_lines( t_long delta );

      void fade_lines( t_long delta );

      void appear_sides( t_long delta );

      void fade_sides( t_long delta );

     
      /* ........................................................................ */

      t_bool check_point_statuss( t_byte statuss );

      t_bool check_line_statuss( t_byte statuss );

      t_bool check_side_statuss( t_byte statuss );

      /* ........................................................................ */

      c_scene_cube( );

      ~c_scene_cube( );
  };

  /* ............................................................................ */

#endif