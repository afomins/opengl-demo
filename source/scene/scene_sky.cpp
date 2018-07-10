/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_sky.cpp                                         */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 31.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"
#include "app\app_tex.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_sky                                                                  */

c_scene_sky::c_scene_sky( )
{
  vert  = ( s_coord3d* )malloc( CUBE_VERT_COUNT * sizeof( s_coord3d ) );
  point = ( c_scene_cube_point* )malloc( CUBE_POINT_COUNT * sizeof( c_scene_cube_point ) );
  line  = ( c_scene_cube_line* )malloc( CUBE_LINE_COUNT * sizeof( c_scene_cube_line ) );
  side  = ( c_scene_cube_side* )malloc( CUBE_SIDE_COUNT * sizeof( c_scene_cube_side ) );

  /* ............................................................................ */

  t_double size = SKY_SIZE / 2.0;
  t_long   i;

  /* ............................................................................ */
  /*   vert                                                                       */

  set_vert( 0, -size, -size,  size );
  set_vert( 1, -size, -size, -size );
  set_vert( 2,  size, -size, -size );
  set_vert( 3,  size, -size,  size );
  set_vert( 4, -size,  size,  size );
  set_vert( 5, -size,  size, -size );
  set_vert( 6,  size,  size, -size );
  set_vert( 7,  size,  size,  size );

  /* ............................................................................ */
  /*   point                                                                      */

  for( i = 0; i < CUBE_VERT_COUNT; i++ )
  {
    point[i].set( &vert[i], 0.0, 1.0, 0.0, 0.2, 1.0, 1.0, 1.0, 1.0 );
  }

  /* ............................................................................ */
  /*   line                                                                       */

  line[0].set(  &vert[0], &vert[1], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[1].set(  &vert[1], &vert[2], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[2].set(  &vert[3], &vert[2], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[3].set(  &vert[3], &vert[0], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[4].set(  &vert[5], &vert[4], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[5].set(  &vert[5], &vert[6], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[6].set(  &vert[6], &vert[7], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[7].set(  &vert[7], &vert[4], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[8].set(  &vert[4], &vert[0], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[9].set(  &vert[1], &vert[5], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[10].set( &vert[2], &vert[6], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );
  line[11].set( &vert[7], &vert[3], 0.9, 0.0, 0.0, 0.2, 0.9, 0.9, 0.6, 0.8 );

  /* ............................................................................ */
  /*   side                                                                       */

  side[0].set( &vert[1], &vert[5], &vert[6], &vert[2], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_sky_front );
  side[1].set( &vert[3], &vert[7], &vert[4], &vert[0], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_sky_back );
  side[2].set( &vert[0], &vert[4], &vert[5], &vert[1], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_sky_left );
  side[3].set( &vert[2], &vert[6], &vert[7], &vert[3], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_sky_right );
  side[4].set( &vert[5], &vert[4], &vert[7], &vert[6], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_sky_up );
  side[5].set( &vert[0], &vert[1], &vert[2], &vert[3], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_sky_down );

  for( i = 0; i < CUBE_SIDE_COUNT; i++ )
  {
    side[i].appear( 0 );
  }

  /* ............................................................................ */

  draw_flag       = true;
  draw_point_flag = false;
  draw_line_flag  = false;
  draw_side_flag  = true;

  /* ............................................................................ */

  rot_vect.x = 0.2;//crt_rnd( );
  rot_vect.y = 1.0;//crt_rnd( );
  rot_vect.z = 0.5;//crt_rnd( );
  rot_angle  = 0.0;
  rot_speed  = -0.01;
}

/* ------------------------------------------------------------------------------ */
/*   ~c_scene_sky                                                                 */

c_scene_sky::~c_scene_sky( )
{
  free( vert );
  free( point );
  free( line );
  free( side );
}

/* ------------------------------------------------------------------------------ */
/*   draw                                                                         */

void c_scene_sky::draw( )
{
  t_long i;

  /* ............................................................................ */

  glPushMatrix( );

    /* .......................................................................... */

    glTranslated( center.x, center.y, center.z );
    glRotated( rot_angle, rot_vect.x, rot_vect.y, rot_vect.z );

    /* .......................................................................... */

    glEnable( GL_TEXTURE_2D );

      /* ........................................................................ */

      for( i = 0; i < CUBE_SIDE_COUNT; i++ )
      {
        side[i].draw( );
      }

      /* ........................................................................ */

    glDisable( GL_TEXTURE_2D );

    /* .......................................................................... */

  glPopMatrix( );
}

