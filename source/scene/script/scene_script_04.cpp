/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\script\scene_script_04.cpp                            */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 26.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_script_04                                                            */

c_scene_script_04::c_scene_script_04( t_char* name )
{
  this->name = name;

  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_script_04::begin( )
{
  s_coord3l pos;
  s_coord3l offset;

  t_long i          = 0;
  t_long j          = 0;
  t_bool found_flag = false;

  /* ............................................................................ */

  t_move         = 1500;
  t_appear_line  = 25000;
  t_appear_side  = 20000;
  t_fade_line    = 25000;

  fov_end   = 120.0;
  fov_speed = 0.005;
  fov_accel = 0.01;

  t_wait_start = -1;
  t_wait       = 27000;

  /* ............................................................................ */

  t_script_begin = g_timer->current_tick;

  /* ............................................................................ */

  build_cube_array( );

  /* ............................................................................ */

  process_flag = true;

  /* ............................................................................ */

  if( empty_count( ) == 0 ) 
  {
    move_flag = false;

    /* .......................................................................... */

    return;
  }
  else
  {
    move_flag = true;
  }

  /* ............................................................................ */

  while( !found_flag )
  {
    pos.x = crt_rnd( 3 );
    pos.y = crt_rnd( 3 );
    pos.z = crt_rnd( 3 );

    /* .......................................................................... */

    offset.x = crt_rnd( 3 ) - 1;
    offset.y = crt_rnd( 3 ) - 1;
    offset.z = crt_rnd( 3 ) - 1;

    if( array[pos.x][pos.y][pos.z].draw_flag )
    {
      move_from = array[pos.x][pos.y][pos.z].id;

      /* ........................................................................ */
      /*   x                                                                      */

      if( ( pos.x + offset.x <= 2 ) && ( pos.x + offset.x >= 0 ) &&
          ( !array[pos.x + offset.x][pos.y][pos.z].draw_flag ) )
      {
        move_to    = array[pos.x + offset.x][pos.y][pos.z].id;
        found_flag = true;
      }
      else

      /* ........................................................................ */
      /*   y                                                                      */

      if( ( pos.y + offset.y <= 2 ) && ( pos.y + offset.y >= 0 ) &&
          ( !array[pos.x][pos.y + offset.y][pos.z].draw_flag ) )
      {
        move_to    = array[pos.x][pos.y + offset.y][pos.z].id;
        found_flag = true;
      }
      else

      /* ........................................................................ */
      /*   z                                                                      */

      if( ( pos.z + offset.z <= 2 ) && ( pos.z + offset.z >= 0 ) &&
          ( !array[pos.x][pos.y][pos.z + offset.z].draw_flag ) )
      {
        move_to    = array[pos.x][pos.y][pos.z + offset.z].id;
        found_flag = true;
      }
    }
  
    i++;
  }

  /* ............................................................................ */

  move_vect.x = g_scene->cube[move_to].center.x - g_scene->cube[move_from].center.x;
  move_vect.y = g_scene->cube[move_to].center.y - g_scene->cube[move_from].center.y;
  move_vect.z = g_scene->cube[move_to].center.z - g_scene->cube[move_from].center.z;

  /* ............................................................................ */

  g_scene->cube[move_to].draw_flag = true;

  /* ............................................................................ */

  g_scene->cube[move_to].appear_lines( t_appear_line );
  g_scene->cube[move_to].rand_line_vert( );
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_script_04::end( )
{
  g_scene->script_05->begin( );

  /* ............................................................................ */

  process_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene_script_04::process( )
{
  /* ............................................................................ */

  t_double done = ( g_timer->current_tick - t_script_begin ) / ( t_double )t_move;

  /* ............................................................................ */

  if( move_flag )
  {
    if( done > 1 )
    {
      done = 1;

      /* ........................................................................ */
  
      g_scene->cube[move_to].center.x = g_scene->cube[move_from].center.x + move_vect.x * done;
      g_scene->cube[move_to].center.y = g_scene->cube[move_from].center.y + move_vect.y * done;
      g_scene->cube[move_to].center.z = g_scene->cube[move_from].center.z + move_vect.z * done;

      /* ........................................................................ */

      begin( );
    }

    /* .......................................................................... */

    g_scene->cube[move_to].center.x = g_scene->cube[move_from].center.x + move_vect.x * done;
    g_scene->cube[move_to].center.y = g_scene->cube[move_from].center.y + move_vect.y * done;
    g_scene->cube[move_to].center.z = g_scene->cube[move_from].center.z + move_vect.z * done;
  }
  else

  /* ............................................................................ */

  if( ( t_wait_start == -1 ) && ( g_scene->check_line_statuss( STATUSS_DRAW ) ) ) 
  {
    t_wait_start = g_timer->current_tick;

    g_scene->fade_cube_lines( t_fade_line );
    g_scene->appear_cube_sides( t_appear_side );
    g_scene->script_rnd_change_rot_vect->begin( );
  }

  if( ( t_wait_start != -1 ) && ( g_timer->current_tick > t_wait_start + t_wait ) )
  {
    g_scene->script_change_fov->begin( fov_end, fov_speed, fov_accel );

    end( );
  }
}

/* ------------------------------------------------------------------------------ */
/*   build_cube_array                                                             */

void c_scene_script_04::build_cube_array( )
{
  t_byte i;
  t_long x;
  t_long y;
  t_long z;

  /* ............................................................................ */

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    y = i / 9;
    z = ( i - y * 9 ) / 3;
    x = ( i - y * 9 ) % 3;

    /* .......................................................................... */

    array[x][y][z].id = i;

    /* .......................................................................... */

    if( g_scene->cube[i].draw_flag ) array[x][y][z].draw_flag = true;
    else                             array[x][y][z].draw_flag = false;
  }
}

/* ------------------------------------------------------------------------------ */
/*   empty_count                                                                  */

t_long c_scene_script_04::empty_count( )
{
  t_long count = 0;
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    if( !g_scene->cube[i].draw_flag ) count++;
  }

  /* ............................................................................ */

  return count;
}