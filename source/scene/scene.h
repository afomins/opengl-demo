/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene.h                                               */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 24.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"
#include "app\app_ogl.h"
#include "scene\scene_cube.h"
#include "scene\script\scene_script.h"
#include "scene\scene_light.h"
#include "scene\scene_sky.h"

/* ------------------------------------------------------------------------------ */

#ifndef __SCENE_
#define __SCENE_

  /* ............................................................................ */

  #define STATUSS_BEGIN_FADE   0
  #define STATUSS_FADE         1
  #define STATUSS_NO_DRAW      2
  #define STATUSS_BEGIN_APPEAR 3
  #define STATUSS_APPEAR       4
  #define STATUSS_DRAW         5

  /* ............................................................................ */

  #define CUBE_COUNT 27

  #define LINE_FADE  100//2000
  #define POINT_FADE 100//5000
  #define SIDE_FADE  100//2000

  #define POINT_SIZE 7
  #define LINE_SIZE  3

  /* ............................................................................ */
  /*   c_scene                                                                    */

  class c_scene
  {
    public :

      c_app_ogl* ogl;

      /* ........................................................................ */

      t_bool draw_persp_flag;
      t_bool draw_ortho_flag;
      t_bool process_flag;

      c_scene_cube cube[CUBE_COUNT];

      c_scene_sky sky;

      c_scene_light_model light_model;

      t_double  rot_angle;
      t_double  rot_speed;
      s_coord3d rot_vect;

      /* ........................................................................ */

      c_scene_script_00* script_00;
      c_scene_script_01* script_01;
      c_scene_script_02* script_02;
      c_scene_script_03* script_03;
      c_scene_script_04* script_04;
      c_scene_script_05* script_05;

      c_scene_script_rotate_cubes*            script_rotate_cubes;
      c_scene_script_rotate_sky*              script_rotate_sky;
      c_scene_script_change_fov*              script_change_fov;
      c_scene_script_change_rot_vect*         script_change_rot_vect;
      c_scene_script_change_sky_rot_vect*     script_change_sky_rot_vect;
      c_scene_script_rnd_change_rot_vect*     script_rnd_change_rot_vect;
      c_scene_script_rnd_change_sky_rot_vect* script_rnd_change_sky_rot_vect;
      c_scene_script_change_cube_col*         script_change_cube_col;

      /* ........................................................................ */

      void process( );

      void build_cube_coord( t_double mult );

      void draw_persp( );

      void draw_ortho( );

      /* ........................................................................ */

      void appear_cube_points( t_long delta );

      void fade_cube_points( t_long delta );

      void appear_cube_lines( t_long delta );

      void fade_cube_lines( t_long delta );

      void appear_cube_sides( t_long delta );

      void fade_cube_sides( t_long delta );

      /* ........................................................................ */

      t_bool check_point_statuss( t_byte statuss );

      t_bool check_line_statuss( t_byte statuss );

      t_bool check_side_statuss( t_byte statuss );

      /* ........................................................................ */

      c_scene( c_app_ogl* ogl );

      ~c_scene( );
  };

  /* ............................................................................ */

  extern c_scene* g_scene;

  /* ............................................................................ */

#endif