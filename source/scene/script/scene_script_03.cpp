/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_03.cpp                            */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 26.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_03                                                            */

c_scene_script_03::c_scene_script_03( t_char* name )
{
  this->name   = name;

  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_script_03::begin( )
{
  cube_id = g_scene->script_01->get_cube_id( );
  
  t_script_begin = g_timer->current_tick;

  t_move       = 5000;
  t_point_fade = 5000;

  move_to   = g_scene->script_01->get_old_cube_center( );
  move_from = g_scene->script_01->get_new_cube_center( );
  
  move_vect.x = move_to.x - move_from.x;
  move_vect.y = move_to.y - move_from.y;
  move_vect.z = move_to.z - move_from.z;
  
  /* ............................................................................ */

  g_scene->cube[cube_id].fade_points( t_point_fade );

  /* ............................................................................ */

  process_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_03::end( )
{
  g_scene->script_04->begin( );
  
  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_03::process( )
{
  t_double done = ( g_timer->current_tick - t_script_begin ) / ( t_double )t_move;

  /* ............................................................................ */

  if( done > 1 )
  {
    done = 1;

    g_scene->cube[cube_id].center.x = move_from.x + move_vect.x * done;
    g_scene->cube[cube_id].center.y = move_from.y + move_vect.y * done;
    g_scene->cube[cube_id].center.z = move_from.z + move_vect.z * done;

    /* .......................................................................... */

    end( );
  }

  /* ............................................................................ */

  g_scene->cube[cube_id].center.x = move_from.x + move_vect.x * done;
  g_scene->cube[cube_id].center.y = move_from.y + move_vect.y * done;
  g_scene->cube[cube_id].center.z = move_from.z + move_vect.z * done;
}
