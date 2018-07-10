/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\main.cpp                                                    */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"
#include "app\app.h"
#include "scene\scene.h"

/* ------------------------------------------------------------------------------ */

t_ulong ogl_list_count = 0;

t_double tmp_d[TMP_COUNT];
t_long   tmp_l[TMP_COUNT];
t_ulong  tmp_ul[TMP_COUNT];

/* ------------------------------------------------------------------------------ */
/*   WinMain                                                                      */

t_int WINAPI WinMain( HINSTANCE hInst,
                      HINSTANCE hPrevInst,
                      t_char*   cmd_line,
                      t_int     wnd_state )
{
  MSG    msg;
  t_long i;

  /* ............................................................................ */
  /*   tmp                                                                        */

  for( i = 0; i < TMP_COUNT; i++ )
  {
    tmp_d[i]  = 0;
    tmp_l[i]  = 0;
    tmp_ul[i] = 0;
  }

  /* ............................................................................ */
  /*   wnd                                                                        */

  wnd_main_init( );
  wnd_about_init( );

  /* ............................................................................ */
  /*   ogl                                                                        */

  g_app.ogl = new c_app_ogl( ( *g_w_main ), 320, 240, 32, false );

  /* ............................................................................ */
  /*   tex                                                                        */

  g_app.tex = new c_app_tex( );

  /* ............................................................................ */
  /*   fnt                                                                        */

  g_app.fnt = new c_app_fnt( g_app.tex );

  /* ............................................................................ */
  /*   timer                                                                      */

  g_app.timer = new c_app_timer( );
  g_timer     = g_app.timer;

  /* ............................................................................ */
  /*   scene                                                                      */

  g_scene = new c_scene( g_app.ogl );

  /* ............................................................................ */

  while( !g_app.quit_flag )
  {
    if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
    {
      if( msg.message == WM_QUIT ) break;

      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }

    g_app.timer->process( );

    /* .......................................................................... */
    /*   wnd                                                                      */

    if( !( *g_w_main )->disable_flag ) wnd_main( );
  }

  /* ............................................................................ */

  return msg.wParam;
}