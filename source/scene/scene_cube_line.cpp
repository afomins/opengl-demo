/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_cube_line.cpp                                   */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 25.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

#include <math.h>

/* ------------------------------------------------------------------------------ */
/*   c_scene_cube_line                                                            */

void c_scene_cube_line::set( s_coord3d* vert0,
                             s_coord3d* vert1,
                             t_float    begin_r,
                             t_float    begin_g,
                             t_float    begin_b,
                             t_float    begin_a,
                             t_float    end_r,
                             t_float    end_g,
                             t_float    end_b,
                             t_float    end_a )
{
  col_begin.r = begin_r;
  col_begin.g = begin_g;
  col_begin.b = begin_b;
  col_begin.a = begin_a;

  col_end.r = end_r;
  col_end.g = end_g;
  col_end.b = end_b;
  col_end.a = end_a;

  /* ............................................................................ */
    
  this->vert[0] = vert0;
  this->vert[1] = vert1;
  timer_begin   = 0;
  timer_delta   = 0;

  /* ............................................................................ */

  vect.x = vert[1]->x - vert[0]->x;
  vect.y = vert[1]->y - vert[0]->y;
  vect.z = vert[1]->z - vert[0]->z;

  t_double diag   = sqrt( vect.x * vect.x + vect.z * vect.z );
           radius = sqrt( diag * diag + vect.y * vect.y );

  /* ............................................................................ */

  statuss = STATUSS_NO_DRAW;
}

/* .............................................................................. */
/*   draw                                                                         */

void c_scene_cube_line::draw( )
{
  glBegin( GL_LINES );

    /* .......................................................................... */
    /*   DRAW                                                                     */

    if( statuss == STATUSS_DRAW )
    {
      glColor4f( col_end.r, col_end.g, col_end.b, col_end.a );
      glVertex3d( vert[0]->x, vert[0]->y, vert[0]->z );
      glVertex3d( vert[1]->x, vert[1]->y, vert[1]->z );
    }
    else

    /* .......................................................................... */
    /*   BEGIN_APPEAR                                                             */

    if( statuss == STATUSS_BEGIN_APPEAR )
    {
      timer_begin = g_timer->current_tick;
      statuss     = STATUSS_APPEAR;
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

      glColor4f( col_begin.r + ( col_end.r - col_begin.r ) * ( t_float )done, 
                 col_begin.g + ( col_end.g - col_begin.g ) * ( t_float )done, 
                 col_begin.b + ( col_end.b - col_begin.b ) * ( t_float )done,
                 col_begin.a + ( col_end.a - col_begin.a ) * ( t_float )done );

      done *= radius;

      /* ........................................................................ */

      t_double x = vect.x * done;
      t_double y = vect.y * done;
      t_double z = vect.z * done;

      glVertex3d( vert[0]->x, vert[0]->y, vert[0]->z );
      glVertex3d( vert[0]->x + x, vert[0]->y + y, vert[0]->z + z );
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
      glVertex3d( vert[0]->x, vert[0]->y, vert[0]->z );
      glVertex3d( vert[1]->x, vert[1]->y, vert[1]->z );
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

      done *= radius;

      /* ........................................................................ */

      t_double x = vect.x * done;
      t_double y = vect.y * done;
      t_double z = vect.z * done;

      glVertex3d( vert[0]->x, vert[0]->y, vert[0]->z );
      glVertex3d( vert[1]->x - x, vert[1]->y - y, vert[1]->z - z );
    }

  glEnd( );
}

/* ------------------------------------------------------------------------------ */
/*   appear                                                                       */

void c_scene_cube_line::appear( t_long delta )
{
  statuss        = STATUSS_BEGIN_APPEAR;
  timer_delta    = delta;
}

/* ------------------------------------------------------------------------------ */
/*   fade                                                                         */

void c_scene_cube_line::fade( t_long delta )
{
  statuss     = STATUSS_BEGIN_FADE;
  timer_delta = delta;
}