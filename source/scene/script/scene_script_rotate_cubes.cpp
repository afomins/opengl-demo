/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_rotate_cubes.cpp                  */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 29.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_rotate_cubes                                                  */

c_scene_script_rotate_cubes::c_scene_script_rotate_cubes( t_char* name )
{
  this->name = name;

  /* ............................................................................ */

  process_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_rotate_cubes::end( )
{
  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_rotate_cubes::process( )
{
  g_scene->rot_angle += g_timer->frame_len * g_scene->rot_speed;
}
