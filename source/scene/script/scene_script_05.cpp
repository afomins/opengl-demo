/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_05.cpp                            */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 26.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

#include <math.h>

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_05                                                            */

c_scene_script_05::c_scene_script_05( t_char* name )
{
  this->name   = name;

  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_script_05::begin( )
{
  t_long   i;
  t_double step;
  t_double radius;

  /* ............................................................................ */

  t_script_begin = g_timer->current_tick;

  radius_begin = 6.0;
  radius_delta = 0.0;
  t_move       = 500;

  /* ............................................................................ */

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    move_from[i] = g_scene->cube[i].center;
  }

  /* ............................................................................ */

  step = ( 360.0 / 27.0 ) * ( PI / 180.0 );
  
  /* ............................................................................ */

  for( i = 0; i < 27; i++ )
  {
    radius = radius_begin + radius_delta * ( i / ( t_double )27 );

    move_to[i].x = radius * cos( step * i );
    move_to[i].z = radius * sin( step * i );
    move_to[i].y = 0.0;

    g_scene->cube[i].rot_vect.x = 0.0;
    g_scene->cube[i].rot_vect.y = 1.0;
    g_scene->cube[i].rot_vect.z = 0.0;

    g_scene->cube[i].rot_angle = -i * ( 360.0 / 27.0 ) + 90;
  }

  /* ............................................................................ */

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    move_vect[i].x = move_to[i].x - move_from[i].x;
    move_vect[i].y = move_to[i].y - move_from[i].y;
    move_vect[i].z = move_to[i].z - move_from[i].z;
  }

  /* ............................................................................ */

  process_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_05::end( )
{
  g_scene->script_change_cube_col->begin( );

  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_05::process( )
{
  t_double done = ( g_timer->current_tick - t_script_begin ) / ( t_double )t_move;
  t_long   i;

  /* ............................................................................ */

  if( done > 1 )
  {
    done = 1;

    for( i = 0; i < CUBE_COUNT; i++ )
    {
      g_scene->cube[i].center.x = move_from[i].x + move_vect[i].x * done;
      g_scene->cube[i].center.y = move_from[i].y + move_vect[i].y * done;
      g_scene->cube[i].center.z = move_from[i].z + move_vect[i].z * done;
    }

    /* .......................................................................... */

    end( );
  }

  /* ............................................................................ */


  for( i = 0; i < CUBE_COUNT; i++ )
  {
    g_scene->cube[i].center.x = move_from[i].x + move_vect[i].x * done;
    g_scene->cube[i].center.y = move_from[i].y + move_vect[i].y * done;
    g_scene->cube[i].center.z = move_from[i].z + move_vect[i].z * done;
  }
}
