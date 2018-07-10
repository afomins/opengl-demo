/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_cube_point.cpp                                  */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 25.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_cube_point                                                           */

void c_scene_cube_point::set( s_coord3d* vert,
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

  this->vert  = vert;

  timer_delta = 0;
  timer_begin = 0;

  /* ............................................................................ */

  statuss = STATUSS_NO_DRAW;
}

/* .............................................................................. */
/*   draw                                                                         */

void c_scene_cube_point::draw( )
{
  glBegin( GL_POINTS );

    /* .......................................................................... */
    /*   DRAW                                                                     */

    if( statuss == STATUSS_DRAW )
    {
      glColor4f( col_end.r, col_end.g, col_end.b, col_end.a );
      glVertex3d( vert->x, vert->y, vert->z );
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

      if( done > 1.0 )
      {
        done    = 1.0;
        statuss = STATUSS_DRAW;
      }

      glColor4f( col_begin.r + ( col_end.r - col_begin.r ) * ( t_float )done, 
                 col_begin.g + ( col_end.g - col_begin.g ) * ( t_float )done, 
                 col_begin.b + ( col_end.b - col_begin.b ) * ( t_float )done,
                 col_begin.a + ( col_end.a - col_begin.a ) * ( t_float )done );

      glVertex3d( vert->x, vert->y, vert->z );
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
      glVertex3d( vert->x, vert->y, vert->z );
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

      glColor4f( col_end.r - ( col_end.r - col_begin.r ) * ( t_float )done,
                 col_end.g - ( col_end.r - col_begin.g ) * ( t_float )done,
                 col_end.b - ( col_end.r - col_begin.b ) * ( t_float )done,
                 col_end.a - col_end.a * ( t_float )done );

      glVertex3d( vert->x, vert->y, vert->z );
    }

  glEnd( );
}

/* ------------------------------------------------------------------------------ */
/*   appear                                                                       */

void c_scene_cube_point::appear( t_long delta )
{
  statuss         = STATUSS_BEGIN_APPEAR;
  timer_delta     = delta;
}

/* ------------------------------------------------------------------------------ */
/*   fade                                                                         */

void c_scene_cube_point::fade( t_long delta )
{
  statuss     = STATUSS_BEGIN_FADE;
  timer_delta = delta;
}