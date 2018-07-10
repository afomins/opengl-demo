/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_02.cpp                            */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 24.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_02                                                            */

c_scene_script_02::c_scene_script_02( t_char* name )
{
  this->name = name;

  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_script_02::begin( )
{
  cube_id = g_scene->script_01->get_cube_id( );

  /* ............................................................................ */

  t_script_begin = g_timer->current_tick;

  /* ............................................................................ */

  fov_end   = 45.0;
  fov_speed = 0.00001;
  fov_accel = 0.0002;

  t_vect_change = 5000;
  t_line_appear = 5000;

  /* ............................................................................ */

  t_line_appear_offset[7]  = t_line_appear * 0;
  t_line_appear_offset[1]  = t_line_appear * 0;
  t_line_appear_offset[8]  = t_line_appear * 1;
  t_line_appear_offset[10] = t_line_appear * 1;
  t_line_appear_offset[0]  = t_line_appear * 2;
  t_line_appear_offset[6]  = t_line_appear * 2;
  t_line_appear_offset[11] = t_line_appear * 3;
  t_line_appear_offset[9]  = t_line_appear * 3;
  t_line_appear_offset[3]  = t_line_appear * 4;
  t_line_appear_offset[5]  = t_line_appear * 4;
  t_line_appear_offset[4]  = t_line_appear * 4;
  t_line_appear_offset[2]  = t_line_appear * 4;

  /* ............................................................................ */

  process_flag                          = true;
  g_scene->cube[cube_id].draw_line_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_02::end( )
{
  g_scene->script_03->begin( );

  /* ............................................................................ */

  g_scene->script_change_fov->begin( fov_end, fov_speed, fov_accel );

  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_02::process( )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_LINE_COUNT; i++ )
  {
    if( ( g_scene->cube[cube_id].line[i].statuss == STATUSS_NO_DRAW ) &&
        ( g_timer->current_tick > t_script_begin + t_line_appear_offset[i] ) )
    {
      g_scene->cube[cube_id].line[i].appear( t_line_appear );
    }
  }

  /* ............................................................................ */

  if( g_scene->cube[cube_id].check_line_statuss( STATUSS_DRAW ) ) end( );
}
