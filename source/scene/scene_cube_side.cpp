/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_cube_side.cpp                                   */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 30.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

#include <math.h>

/* ------------------------------------------------------------------------------ */
/*   c_scene_cube_side                                                            */

void c_scene_cube_side::set( s_coord3d*      vert0,
                             s_coord3d*      vert1,
                             s_coord3d*      vert2,
                             s_coord3d*      vert3,
                             t_float         begin_r,
                             t_float         begin_g,
                             t_float         begin_b,
                             t_float         begin_a,
                             t_float         end_r,
                             t_float         end_g,
                             t_float         end_b,
                             t_float         end_a,
                             c_app_tex_inst* tex )
{
  col_begin.r = begin_r;
  col_begin.g = begin_g;
  col_begin.b = begin_b;
  col_begin.a = begin_a;

  col_end.r = end_r;
  col_end.g = end_g;
  col_end.b = end_b;
  col_end.a = end_a;

  vert[0] = vert0;
  vert[1] = vert1;
  vert[2] = vert2;
  vert[3] = vert3;

  timer_begin = 0;
  timer_delta = 0;

  this->tex = tex;

  /* ............................................................................ */

  build_normal( );

  /* ............................................................................ */

  statuss = STATUSS_NO_DRAW;
}

/* .............................................................................. */
/*   draw                                                                         */

void c_scene_cube_side::draw( )
{
  tex->select( );

  glBegin( GL_QUADS );

    /* .......................................................................... */
    /*   DRAW                                                                     */

    if( statuss == STATUSS_DRAW )
    {
//      glColor4f( col_end.r, col_end.g, col_end.b, col_end.a );
      t_float ad[] = { 0.2, 0.2, 0.2, 1.0 };
      glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ad );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 0 );
      glVertex3d( vert[0]->x, vert[0]->y, vert[0]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 1 );
      glVertex3d( vert[1]->x, vert[1]->y, vert[1]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 1 );
      glVertex3d( vert[2]->x, vert[2]->y, vert[2]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 0 );
      glVertex3d( vert[3]->x, vert[3]->y, vert[3]->z );
    }
    else

    /* .......................................................................... */
    /*   BEGIN_APPEAR                                                             */

    if( statuss == STATUSS_BEGIN_APPEAR )
    {
      timer_begin = g_timer->current_tick;
      statuss     = STATUSS_APPEAR;

      /* ........................................................................ */
/*
      glColor4f( col_begin.r, 
                 col_begin.g, 
                 col_begin.b,
                 col_begin.a );
*/
      t_float ad[] = { 0.2, 0.2, 0.2, 0.0 };
      glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ad );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 0 );
      glVertex3d( vert[0]->x, vert[0]->y, vert[0]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 1 );
      glVertex3d( vert[1]->x, vert[1]->y, vert[1]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 1 );
      glVertex3d( vert[2]->x, vert[2]->y, vert[2]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 0 );
      glVertex3d( vert[3]->x, vert[3]->y, vert[3]->z );
    }
    else

    /* .......................................................................... */
    /*   APPEAR                                                                   */

    if( statuss == STATUSS_APPEAR )
    {
      t_double done = ( g_timer->current_tick - timer_begin ) / ( t_double )timer_delta;

      /* ........................................................................ */

      if( done > 1 )
      {
        done    = 1;
        statuss = STATUSS_DRAW;
      }

      /* ........................................................................ */
/*
      glColor4f( col_begin.r + ( col_end.r - col_begin.r ) * ( t_float )done, 
                 col_begin.g + ( col_end.g - col_begin.g ) * ( t_float )done, 
                 col_begin.b + ( col_end.b - col_begin.b ) * ( t_float )done,
                 col_begin.a + ( col_end.a - col_begin.a ) * ( t_float )done );
*/
      t_float ad[] = { 0.2, 0.2, 0.2, col_begin.a + ( col_end.a - col_begin.a ) * ( t_float )done };
      glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ad );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 0 );
      glVertex3d( vert[0]->x, vert[0]->y, vert[0]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 1 );
      glVertex3d( vert[1]->x, vert[1]->y, vert[1]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 1 );
      glVertex3d( vert[2]->x, vert[2]->y, vert[2]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 0 );
      glVertex3d( vert[3]->x, vert[3]->y, vert[3]->z );
    }
    else

    /* .......................................................................... */
    /*   BEGIN_FADE                                                               */

    if( statuss == STATUSS_BEGIN_FADE )
    {
      timer_begin = g_timer->current_tick;
      statuss     = STATUSS_FADE;

      /* ........................................................................ */

      glColor4f( col_end.r, col_end.g, col_end.b, col_end.a );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 0 );
      glVertex3d( vert[0]->x, vert[0]->y, vert[0]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 1 );
      glVertex3d( vert[1]->x, vert[1]->y, vert[1]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 1 );
      glVertex3d( vert[2]->x, vert[2]->y, vert[2]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 0 );
      glVertex3d( vert[3]->x, vert[3]->y, vert[3]->z );
    }
    else

    /* .......................................................................... */
    /*   FADE                                                                     */

    if( statuss == STATUSS_FADE )
    {
      t_double done = ( g_timer->current_tick - timer_begin ) / ( t_double )timer_delta;

      /* ........................................................................ */

      if( done > 1.0 )
      {
        done    = 1.0;
        statuss = STATUSS_NO_DRAW;
      }

      /* ........................................................................ */

      glColor4f( col_end.r - ( col_end.r - col_begin.r ) * ( t_float )done,
                 col_end.g - ( col_end.r - col_begin.g ) * ( t_float )done,
                 col_end.b - ( col_end.r - col_begin.b ) * ( t_float )done,
                 col_end.a - col_end.a * ( t_float )done );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 0 );
      glVertex3d( vert[0]->x, vert[0]->y, vert[0]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 0, 1 );
      glVertex3d( vert[1]->x, vert[1]->y, vert[1]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 1 );
      glVertex3d( vert[2]->x, vert[2]->y, vert[2]->z );

      glNormal3d( normal.x, normal.y, normal.z );
      glTexCoord2i( 1, 0 );
      glVertex3d( vert[3]->x, vert[3]->y, vert[3]->z );
    }

  glEnd( );
}

/* ------------------------------------------------------------------------------ */
/*   appear                                                                       */

void c_scene_cube_side::appear( t_long delta )
{
  statuss        = STATUSS_BEGIN_APPEAR;
  timer_delta    = delta;
}

/* ------------------------------------------------------------------------------ */
/*   fade                                                                         */

void c_scene_cube_side::fade( t_long delta )
{
  statuss     = STATUSS_BEGIN_FADE;
  timer_delta = delta;
}

/* ------------------------------------------------------------------------------ */
/*   build_normal                                                                 */

void c_scene_cube_side::build_normal( )
{
  s_coord3d v0;
  s_coord3d v1;
  t_double  len;

  /* ............................................................................ */

  v0.x = vert[1]->x - vert[0]->x;
  v0.y = vert[1]->y - vert[0]->y;
  v0.z = vert[1]->z - vert[0]->z;

  v1.x = vert[3]->x - vert[0]->x;
  v1.y = vert[3]->y - vert[0]->y;
  v1.z = vert[3]->z - vert[0]->z;

  normal.x = v0.y * v1.z - v0.z * v1.y;
  normal.y = v0.z * v1.x - v0.x * v1.x;
  normal.z = v0.x * v1.y - v0.y * v1.x;

  len = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
  len = sqrt( len );
  len = 1 / len;

  normal.x *= -len;
  normal.y *= -len;
  normal.z *= -len;
}