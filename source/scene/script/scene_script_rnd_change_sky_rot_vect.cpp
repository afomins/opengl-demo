/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_rnd_change_sky_rot_vect.cpp           */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 29.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_rnd_change_sky_rot_vect                                       */

c_scene_script_rnd_change_sky_rot_vect::c_scene_script_rnd_change_sky_rot_vect( t_char* name )
{
  process_flag = false;
  this->name   = name;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_script_rnd_change_sky_rot_vect::begin( )
{
  t_script_begin = g_timer->current_tick;
  t_script_len   = 100000;
  t_vect_change  = 100000;

  vect.z = crt_rnd( ) * ( crt_rnd( 3 ) - 1 );
  vect.x = crt_rnd( ) * ( crt_rnd( 3 ) - 1 );
  vect.y = crt_rnd( ) * ( crt_rnd( 3 ) - 1 );
  
  /* ............................................................................ */

  g_scene->script_change_sky_rot_vect->begin( vect.x, 
                                              vect.z, 
                                              vect.y, 
                                              t_vect_change );

  /* ............................................................................ */

  process_flag = true;
}
                               
/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_rnd_change_sky_rot_vect::end( )
{
  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_rnd_change_sky_rot_vect::process( )
{
  t_double done = ( g_timer->current_tick - t_script_begin ) / ( t_double )t_script_len;

  /* ............................................................................ */
  /*   end o' script                                                              */

  if( done > 1.0 ) begin( );
}
