/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_change_sky_rot_vect.cpp           */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 29.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_change_sky_rot_vect                                           */

c_scene_script_change_sky_rot_vect::c_scene_script_change_sky_rot_vect( t_char* name )
{
  process_flag = false;
  this->name   = name;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_script_change_sky_rot_vect::begin( t_double x,
                                                t_double y,
                                                t_double z,
                                                t_long   timer_delta )
{
  timer_begin       = g_timer->current_tick;
  this->timer_delta = timer_delta;

  /* ............................................................................ */

  vect_begin = g_scene->sky.rot_vect;

  /* ............................................................................ */

  vect_delta.x = x - vect_begin.x;
  vect_delta.y = y - vect_begin.y;
  vect_delta.z = z - vect_begin.z;

  /* ............................................................................ */

  process_flag = true;
}
                               
/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_change_sky_rot_vect::end( )
{
  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_change_sky_rot_vect::process( )
{
  t_double done = ( g_timer->current_tick - timer_begin ) / ( t_double )timer_delta;

  /* ............................................................................ */
  /*   end o' script                                                              */

  if( done > 1.0 )
  {
    done = 1.0;

    /* .......................................................................... */

    end( );
  }

  /* ............................................................................ */

  g_scene->sky.rot_vect.x = vect_begin.x + vect_delta.x * done;
  g_scene->sky.rot_vect.y = vect_begin.y + vect_delta.y * done;
  g_scene->sky.rot_vect.z = vect_begin.z + vect_delta.z * done;
}
