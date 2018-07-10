/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_change_cube_col.cpp               */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 01.11.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_change_cube_col                                               */

c_scene_script_change_cube_col::c_scene_script_change_cube_col( t_char* name )
{
  process_flag = false;
  this->name   = name;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_script_change_cube_col::begin( )
{
  t_long i;

  /* ............................................................................ */

  t_script_len   = 2000;
  t_script_begin = g_timer->current_tick;

  /* ............................................................................ */

  for( i = 0; i < 2; i++ )
  {
    col_a_begin[i].r = g_scene->light_model.light[i]->ambient.r;
    col_a_begin[i].g = g_scene->light_model.light[i]->ambient.g;
    col_a_begin[i].b = g_scene->light_model.light[i]->ambient.b;

    col_a_end[i].r = ( t_float )crt_rnd( );
    col_a_end[i].g = ( t_float )crt_rnd( );
    col_a_end[i].b = ( t_float )crt_rnd( );

    /* .......................................................................... */

    col_d_begin[i].r = g_scene->light_model.light[i]->diffuse.r;
    col_d_begin[i].g = g_scene->light_model.light[i]->diffuse.g;
    col_d_begin[i].b = g_scene->light_model.light[i]->diffuse.b;

    col_d_end[i].r = ( t_float )crt_rnd( );
    col_d_end[i].g = ( t_float )crt_rnd( );
    col_d_end[i].b = ( t_float )crt_rnd( );

    /* .......................................................................... */

    col_s_begin[i].r = g_scene->light_model.light[i]->specular.r;
    col_s_begin[i].g = g_scene->light_model.light[i]->specular.g;
    col_s_begin[i].b = g_scene->light_model.light[i]->specular.b;

    col_s_end[i].r = ( t_float )crt_rnd( );
    col_s_end[i].g = ( t_float )crt_rnd( );
    col_s_end[i].b = ( t_float )crt_rnd( );
  }

  /* ............................................................................ */

  process_flag = true;
}
                               
/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_change_cube_col::end( )
{
  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_change_cube_col::process( )
{
  t_double done = ( g_timer->current_tick - t_script_begin ) / ( t_double )t_script_len;
  t_long   i;

  /* ............................................................................ */

  for( i = 0; i < 2; i++ )
  {
    g_scene->light_model.light[i]->set_ambient( col_a_begin[i].r + ( t_float )done * ( col_a_end[i].r - col_a_begin[i].r ),
                                                col_a_begin[i].g + ( t_float )done * ( col_a_end[i].g - col_a_begin[i].g ),
                                                col_a_begin[i].b + ( t_float )done * ( col_a_end[i].b - col_a_begin[i].b ),
                                                1.0 );

    g_scene->light_model.light[i]->set_diffuse( col_d_begin[i].r + ( t_float )done * ( col_d_end[i].r - col_d_begin[i].r ),
                                                col_d_begin[i].g + ( t_float )done * ( col_d_end[i].g - col_d_begin[i].g ),
                                                col_d_begin[i].b + ( t_float )done * ( col_d_end[i].b - col_d_begin[i].b ),
                                                1.0 );

    g_scene->light_model.light[i]->set_specular( col_s_begin[i].r + ( t_float )done * ( col_s_end[i].r - col_s_begin[i].r ),
                                                 col_s_begin[i].g + ( t_float )done * ( col_s_end[i].g - col_s_begin[i].g ),
                                                 col_s_begin[i].b + ( t_float )done * ( col_s_end[i].b - col_s_begin[i].b ),
                                                 1.0 );
  }

  /* ............................................................................ */

  if( done > 1 )
  {
    done = 1;

    begin( );
  }
}
