/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_change_fov.cpp                    */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 29.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_change_fov                                                    */

c_scene_script_change_fov::c_scene_script_change_fov( t_char* name )
{
  process_flag = false;
  this->name   = name;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_script_change_fov::begin( t_double fov_end,
                                       t_double fov_speed,
                                       t_double fov_accel )
{
  fov_begin       = g_scene->ogl->persp->fov;
  fov_cur         = fov_begin;
  this->fov_end   = fov_end;
  this->fov_speed = fov_speed;
  this->fov_accel = fov_accel;

  /* ............................................................................ */

  process_flag = true;
}
                               
/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_change_fov::end( )
{
  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_change_fov::process( )
{
  fov_speed += fov_speed * fov_accel * g_timer->frame_len;
  fov_cur   += fov_speed * g_timer->frame_len;

  /* ............................................................................ */
  /*   end o' script                                                              */

  if( fov_cur > fov_end )
  {
    fov_cur = fov_end;

    /* .......................................................................... */

    end( );
  }

  /* ............................................................................ */

  g_scene->ogl->persp->set_attrib( fov_cur, ATTRIB_NO_CHANGE );
}
