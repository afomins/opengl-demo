/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_rotate_sky.cpp                    */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 31.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_rotate_sky                                                    */

c_scene_script_rotate_sky::c_scene_script_rotate_sky( t_char* name )
{
  this->name = name;

  /* ............................................................................ */

  process_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_rotate_sky::end( )
{
  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_rotate_sky::process( )
{
  g_scene->sky.rot_angle += g_timer->frame_len * g_scene->sky.rot_speed;
}
