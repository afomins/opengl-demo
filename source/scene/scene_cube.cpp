/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_cube.cpp                                        */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 24.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"
#include "app\app_tex.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_cube                                                                 */

c_scene_cube::c_scene_cube( )
{
  vert  = ( s_coord3d* )malloc( CUBE_VERT_COUNT * sizeof( s_coord3d ) );
  point = ( c_scene_cube_point* )malloc( CUBE_POINT_COUNT * sizeof( c_scene_cube_point ) );
  line  = ( c_scene_cube_line* )malloc( CUBE_LINE_COUNT * sizeof( c_scene_cube_line ) );
  side  = ( c_scene_cube_side* )malloc( CUBE_SIDE_COUNT * sizeof( c_scene_cube_side ) );

  /* ............................................................................ */

  t_double size = CUBE_SIZE / 2.0;
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

  side[0].set( &vert[2], &vert[6], &vert[5], &vert[1], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_00 );
  side[1].set( &vert[0], &vert[4], &vert[7], &vert[3], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_00 );
  side[2].set( &vert[1], &vert[5], &vert[4], &vert[0], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_00 );
  side[3].set( &vert[3], &vert[7], &vert[6], &vert[2], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_00 );
  side[4].set( &vert[4], &vert[5], &vert[6], &vert[7], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_00 );
  side[5].set( &vert[1], &vert[0], &vert[3], &vert[2], 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, g_tex_00 );

  /* ............................................................................ */

  draw_flag       = false;
  draw_point_flag = false;
  draw_line_flag  = false;
  draw_side_flag  = false;

  /* ............................................................................ */

  rot_vect.x = 0.7;
  rot_vect.y = 1.0;
  rot_vect.z = 0.3;
  rot_angle  = 0.0;
  rot_speed  = -0.03;
}

/* ------------------------------------------------------------------------------ */
/*   ~c_scene_cube                                                                */

c_scene_cube::~c_scene_cube( )
{
  free( vert );
  free( point );
  free( line );
  free( side );
}

/* ------------------------------------------------------------------------------ */
/*   draw                                                                         */

void c_scene_cube::draw( )
{
  t_long i;

  /* ............................................................................ */

  glPointSize( POINT_SIZE );
  glLineWidth( LINE_SIZE );
  glEnable( GL_POINT_SMOOTH );
  glEnable( GL_LINE_SMOOTH );

  /* ............................................................................ */

  glPushMatrix( );

    glTranslated( center.x, center.y, center.z );
    glRotated( rot_angle, rot_vect.x, rot_vect.y, rot_vect.z );

    /* .......................................................................... */
    /*   draw_point                                                               */

    if( draw_point_flag ) 
    {
      for( i = 0; i < CUBE_POINT_COUNT; i++ )
      {
        point[i].draw( );
      }
    }

    /* .......................................................................... */
    /*   draw_line                                                                */

    if( draw_line_flag )
    {
      for( i = 0; i < CUBE_LINE_COUNT; i++ )
      {
        line[i].draw( );
      }
    }

    /* .......................................................................... */
    /*   draw_side                                                                */

    if( draw_side_flag )
    {
      g_scene->light_model.begin( );

      glEnable( GL_TEXTURE_2D );

      /* ........................................................................ */

      for( i = 0; i < CUBE_SIDE_COUNT; i++ )
      {
        side[i].draw( );
      }

      /* ........................................................................ */

      glDisable( GL_TEXTURE_2D );

      g_scene->light_model.end( );
    }

    /* .......................................................................... */

  glPopMatrix( );

  /* ............................................................................ */

  glDisable( GL_POINT_SMOOTH );
  glDisable( GL_LINE_SMOOTH );
  glPointSize( 1.0 );
  glLineWidth( 1.0 );
}

/* ------------------------------------------------------------------------------ */
/*   set_vert                                                                     */

void c_scene_cube::set_vert( t_long   vert_id,
                             t_double x,
                             t_double y,
                             t_double z )
{
  vert[vert_id].x = x;
  vert[vert_id].y = y;
  vert[vert_id].z = z;
}

/* ------------------------------------------------------------------------------ */
/*   rand_line_vert                                                               */

void c_scene_cube::rand_line_vert( )
{
  t_long     i;
  t_long     rnd;
  s_coord3d* tmp;

  /* ............................................................................ */

  for( i = 0; i < CUBE_LINE_COUNT; i++ )
  {
    rnd = crt_rnd( 2 );

    /* .......................................................................... */

    if( rnd == 0 )
    {
      tmp = line[i].vert[0];

      line[i].vert[0] = line[i].vert[1];
      line[i].vert[1] = tmp;

      line[i].vect.x = line[i].vert[1]->x - line[i].vert[0]->x;
      line[i].vect.y = line[i].vert[1]->y - line[i].vert[0]->y;
      line[i].vect.z = line[i].vert[1]->z - line[i].vert[0]->z;
    }
  }
}

/* ------------------------------------------------------------------------------ */
/*   appear_points                                                                */

void c_scene_cube::appear_points( t_long delta )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_POINT_COUNT; i++ )
  {
    point[i].appear( delta );
  }

  /* ............................................................................ */

  draw_point_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   fade_points                                                                  */

void c_scene_cube::fade_points( t_long delta )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_POINT_COUNT; i++ )
  {
    point[i].fade( delta );
  }
}

/* ------------------------------------------------------------------------------ */
/*   appear_lines                                                                 */

void c_scene_cube::appear_lines( t_long delta )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_LINE_COUNT; i++ )
  {
    line[i].appear( delta );
  }

  /* ............................................................................ */

  draw_line_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   fade_lines                                                                   */

void c_scene_cube::fade_lines( t_long delta )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_LINE_COUNT; i++ )
  {
    line[i].fade( delta );
  }
}

/* ------------------------------------------------------------------------------ */
/*   appear_sides                                                                 */

void c_scene_cube::appear_sides( t_long delta )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_SIDE_COUNT; i++ )
  {
    side[i].appear( delta );
  }

  /* ............................................................................ */

  draw_side_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   fade_sides                                                                   */

void c_scene_cube::fade_sides( t_long delta )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_SIDE_COUNT; i++ )
  {
    side[i].fade( delta );
  }
}

/* ------------------------------------------------------------------------------ */
/*   check_point_statuss                                                          */

t_bool c_scene_cube::check_point_statuss( t_byte statuss )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_POINT_COUNT; i++ )
  {
    if( point[i].statuss != statuss ) return false;
  }

  /* ............................................................................ */

  return true;
}

/* ------------------------------------------------------------------------------ */
/*   check_line_statuss                                                           */

t_bool c_scene_cube::check_line_statuss( t_byte statuss )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_LINE_COUNT; i++ )
  {
    if( line[i].statuss != statuss ) return false;
  }

  /* ............................................................................ */

  return true;
}

/* ------------------------------------------------------------------------------ */
/*   check_side_statuss                                                           */

t_bool c_scene_cube::check_side_statuss( t_byte statuss )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_SIDE_COUNT; i++ )
  {
    if( side[i].statuss != statuss ) return false;
  }

  /* ............................................................................ */

  return true;
}