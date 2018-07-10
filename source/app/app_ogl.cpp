/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app_ogl.cpp                                             */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 21.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "app\app_ogl.h"

#include <math.h>

/* ------------------------------------------------------------------------------ */
/*   c_app_ogl_ortho                                                              */

c_app_ogl_ortho::c_app_ogl_ortho( c_app_wnd* wnd )
{
  view.x      = 0;
  view.y      = 0;
  view.width  = wnd->view.width;
  view.height = wnd->view.height;
}

/* ------------------------------------------------------------------------------ */
/*   set_proj                                                                     */

void c_app_ogl_ortho::set_proj( )
{
  glMatrixMode( GL_PROJECTION );
  glPushMatrix( );
  glLoadIdentity( );
  glOrtho( 0.0, view.width, 0.0, view.height, -1.0, 1.0 );
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_app_ogl_ortho::begin( )
{
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_app_ogl_ortho::end( )
{
  glMatrixMode( GL_PROJECTION );
  glPopMatrix( );
}

/* ------------------------------------------------------------------------------ */
/*   c_app_ogl_persp                                                              */

c_app_ogl_persp::c_app_ogl_persp( c_app_wnd* wnd )
{
  view.x      = 0;
  view.y      = 0;
  view.width  = wnd->view.width;
  view.height = wnd->view.height;

  /* ............................................................................ */

  fov    = 15.0;
  z_near = 0.1;
  z_far  = 100.0;

  eye.x = 6.0;
  eye.y = 4.0;
  eye.z = 2.0;

  center.x = 0.0;
  center.y = 0.0;
  center.z = 0.0;

  up.x = 0.0;
  up.y = 1.0;
  up.z = 0.0;

  /* ............................................................................ */

  set_correct_aspect( );
}

/* ------------------------------------------------------------------------------ */
/*   set_proj                                                                     */

void c_app_ogl_persp::set_proj( )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );

  /* ............................................................................ */

  gluPerspective( fov, aspect, z_near, z_far );

  gluLookAt( eye.x, eye.y, eye.z,
             center.x, center.y, center.z,
             up.x, up.y, up.z );
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_app_ogl_persp::begin( )
{
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_app_ogl_persp::end( )
{

}

/* ------------------------------------------------------------------------------ */
/*   set_attrib                                                                   */

void c_app_ogl_persp::set_attrib( t_double fov,
                                  t_double aspect )
{
  if( fov != ATTRIB_NO_CHANGE )   this->fov    = fov;
  if( aspect != ATTRIB_NO_CHANGE) this->aspect = aspect;

  /* ............................................................................ */

  set_proj( );
}

/* ------------------------------------------------------------------------------ */
/*   set_correct_aspect                                                           */

void c_app_ogl_persp::set_correct_aspect( )
{
  aspect = view.width / ( t_float ) view.height;
}

/* ------------------------------------------------------------------------------ */
/*   c_app_ogl                                                                    */

c_app_ogl::c_app_ogl( c_app_wnd* wnd,
                      t_long     width,
                      t_long     height,
                      t_long     depth,
                      t_bool     fullscreen_flag )
{
  t_ulong               pix_format;
  PIXELFORMATDESCRIPTOR pfd;

  /* ............................................................................ */

  this->wnd             = wnd;
  this->fullscreen_flag = false;

  /* ............................................................................ */

  desktop_size.x = GetSystemMetrics( SM_CXSCREEN );
  desktop_size.y = GetSystemMetrics( SM_CYSCREEN );

  /* ............................................................................ */

  pfd.nSize           = sizeof( PIXELFORMATDESCRIPTOR );
  pfd.nVersion        = 1;
  pfd.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType      = PFD_TYPE_RGBA;
  pfd.cColorBits      = (t_byte)depth;
  pfd.cRedBits        = 0;
  pfd.cRedShift       = 0;
  pfd.cGreenBits      = 0;
  pfd.cGreenShift     = 0;
  pfd.cBlueBits       = 0;
  pfd.cBlueShift      = 0;
  pfd.cAlphaBits      = 0;
  pfd.cAlphaShift     = 0;
  pfd.cAccumBits      = 0;
  pfd.cAccumRedBits   = 0;
  pfd.cAccumGreenBits = 0;
  pfd.cAccumBlueBits  = 0;
  pfd.cAccumAlphaBits = 0;
  pfd.cDepthBits      = (t_byte)depth;
  pfd.cStencilBits    = 0;
  pfd.cAuxBuffers     = 0;
  pfd.iLayerType      = PFD_MAIN_PLANE;
  pfd.bReserved       = 0;
  pfd.dwLayerMask     = 0;
  pfd.dwVisibleMask   = 0;
  pfd.dwDamageMask    = 0;

  /* ............................................................................ */

  pix_format = ChoosePixelFormat( wnd->hDC, &pfd );
  SetPixelFormat( wnd->hDC, pix_format, &pfd );

  /* ............................................................................ */

  hRC = wglCreateContext( wnd->hDC );
  wglMakeCurrent( wnd->hDC, hRC );

  /* ............................................................................ */
  /*   depth                                                                      */

  glClearDepth( 1.0 );
  glDepthFunc( GL_LEQUAL );

  /* ............................................................................ */
  /*   blend                                                                      */

  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  /* ............................................................................ */
  /*   alpha                                                                      */

  glEnable( GL_ALPHA_TEST );
  glAlphaFunc( GL_GREATER, 0.1);

  /* ............................................................................ */
  /*   proj                                                                       */

  ortho = new c_app_ogl_ortho( wnd );
  persp = new c_app_ogl_persp( wnd );

  /* ............................................................................ */
  /*   misc                                                                       */

  glClearColor( 0.5, 0.5, 0.5, 1.0 );
  glShadeModel( GL_FLAT );
  glPolygonMode( GL_FILL, GL_FRONT_AND_BACK );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
  glEnable( GL_DEPTH_TEST );
  change_screen_settings( width, height, depth, fullscreen_flag );
//  glEnable( GL_CULL_FACE );
//  glFrontFace( GL_CW );
}

/* ------------------------------------------------------------------------------ */
/*   ~c_app_ogl                                                                   */

c_app_ogl::~c_app_ogl( )
{
  delete ortho;
  delete persp;
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_app_ogl::begin( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_app_ogl::end( )
{
  glFlush( );
  SwapBuffers( wnd->hDC );
}

/* ------------------------------------------------------------------------------ */
/*   change_screen_settings                                                       */

void c_app_ogl::change_screen_settings( t_long width,
                                        t_long height,
                                        t_long depth,
                                        t_bool fullscreen_flag )
{
  DEVMODE d_mode;
  s_rectl wnd_rect;
  t_ulong old_dw_style = wnd->get_long( GWL_STYLE );

  /* ............................................................................ */
  /*   fullscreen                                                                 */

  if( fullscreen_flag )
  {
    d_mode.dmSize       = sizeof( DEVMODE );
    d_mode.dmPelsWidth  = width;
    d_mode.dmPelsHeight = height;
    d_mode.dmBitsPerPel = depth;
    d_mode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

    /* .......................................................................... */

    ChangeDisplaySettings( &d_mode, CDS_FULLSCREEN );

    /* .......................................................................... */

    if( !this->fullscreen_flag )
    {
      wnd->set_long( GWL_STYLE, old_dw_style ^ WS_CAPTION );
    }

    /* .......................................................................... */

    wnd_rect.x      = 0;
    wnd_rect.y      = 0;
    wnd_rect.width  = width;
    wnd_rect.height = height;

    /* .......................................................................... */

    wnd->set_pos( &wnd_rect );
  }
  else

  /* ............................................................................ */
  /*   windowed                                                                   */

  {
    if( this->fullscreen_flag )
    {
      ChangeDisplaySettings( NULL, 0 );
      wnd->set_long( GWL_STYLE, old_dw_style ^ WS_CAPTION );
    }

    /* .......................................................................... */

    wnd_rect.x      = NO_CHANGE;
    wnd_rect.y      = NO_CHANGE;
    wnd_rect.width  = width;
    wnd_rect.height = height;

    /* .......................................................................... */

    wnd->set_view( &wnd_rect );

    /* .......................................................................... */

    if( this->fullscreen_flag )
    {
      s_coord2l center;

      /* ........................................................................ */

      center.x = desktop_size.x / 2;
      center.y = desktop_size.y / 2;

      /* ........................................................................ */

      wnd->center( &center );
    }
  }

  /* ............................................................................ */

  this->fullscreen_flag = fullscreen_flag;
  this->screen_size.x   = width;
  this->screen_size.y   = height;
  this->col_depth       = depth;

  /* ............................................................................ */

  update_viewport( );
}

/* ------------------------------------------------------------------------------ */
/*   update_viewport                                                              */

void c_app_ogl::update_viewport( )
{
  view        = wnd->view;
  ortho->view = view;
  persp->view = view;

  persp->set_proj( );

  /* ............................................................................ */
  
  glViewport( view.x,
              view.y,
              view.width,
              view.height );
}
