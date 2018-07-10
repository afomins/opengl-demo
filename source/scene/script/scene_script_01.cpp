/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_01.cpp                            */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 24.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_01                                                            */

c_scene_script_01::c_scene_script_01( t_char* name )
{
  this->name = name;

  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_script_01::begin( )
{
  t_long    i;
  s_coord3d center = { 0.0, 0.0, 0.0 };

  /* ............................................................................ */

  cube_id = 0;

  /* ............................................................................ */

  old_cube_center               = g_scene->cube[cube_id].center;
  new_cube_center               = center;
  g_scene->cube[cube_id].center = new_cube_center;

  /* ............................................................................ */

  t_script_begin = g_timer->current_tick;

  /* ............................................................................ */

  t_point_appear_max_offset = 8000;
  t_point_appear            = 6000;

  /* ............................................................................ */

  for( i = 0; i < CUBE_POINT_COUNT; i++ )
  {
    t_point_appear_offset[i] = ( t_long )( crt_rnd( ) * t_point_appear_max_offset );
  }

  /* ............................................................................ */

  g_scene->cube[cube_id].draw_flag       = true;
  g_scene->cube[cube_id].draw_point_flag = true;
  process_flag                           = true;
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_01::end( )
{
  g_scene->script_02->begin( );

  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_01::process( )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_POINT_COUNT; i++ )
  {
    if( ( g_scene->cube[cube_id].point[i].statuss == STATUSS_NO_DRAW ) &&
       ( g_timer->current_tick > t_script_begin + t_point_appear_offset[i] ) )
    {
      g_scene->cube[cube_id].point[i].appear( t_point_appear );
    }
  }

  /* ............................................................................ */

  if( g_scene->cube[cube_id].check_point_statuss( STATUSS_DRAW ) ) end( );
}

/* ------------------------------------------------------------------------------ */
/*   get_old_cube_center                                                          */

s_coord3d c_scene_script_01::get_old_cube_center( )
{
  return old_cube_center;
}

/* ------------------------------------------------------------------------------ */
/*   get_new_cube_center                                                          */

s_coord3d c_scene_script_01::get_new_cube_center( )
{
  return new_cube_center;
}

/* ------------------------------------------------------------------------------ */
/*   get_cube_id                                                                  */

t_byte c_scene_script_01::get_cube_id( )
{
  return cube_id;
}


