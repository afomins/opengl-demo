/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\wnd\wnd_main.cpp                                        */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_res.h"
#include "app\app.h"
#include "app\app_ogl.h"
#include "scene\scene.h"

/* ------------------------------------------------------------------------------ */
/*   wnd_main_proc                                                                */

LRESULT CALLBACK wnd_main_proc( HWND   hWnd,
                                UINT   msg,
                                WPARAM wParam,
                                LPARAM lParam )
{
  /* ............................................................................ */
  /*   WM_DESTROY                                                                 */

  if( msg == WM_DESTROY )
  {
    g_app.quit( );
  }
  else

  /* ............................................................................ */
  /*   WM_MOVE                                                                    */

  if( msg == WM_MOVE )
  {
    ( *g_w_main )->update_pos( );
  }
  else

  /* ............................................................................ */
  /*   WM_COMMAND                                                                 */

  if( msg == WM_COMMAND )
  {
    t_long code_id   = HIWORD( wParam );
    t_long ctrl_id   = LOWORD( wParam );
    HWND   ctrl_hWnd = ( HWND)lParam;

    /* .......................................................................... */
    /*   menu_main_fullscreen                                                     */

    if( ctrl_id == r_menu_main_screen_fullscreen )
                   
    {
      t_bool flag = true;

      /* ........................................................................ */

      if( g_app.ogl->fullscreen_flag ) flag = false;

      /* ........................................................................ */

      g_app.ogl->change_screen_settings( g_app.ogl->screen_size.x, 
                                         g_app.ogl->screen_size.y, 
                                         g_app.ogl->col_depth,
                                         flag );

      if( flag ) ( *g_w_main )->check_menu_item( r_menu_main_screen_fullscreen );
      else       ( *g_w_main )->uncheck_menu_item( r_menu_main_screen_fullscreen );
    }
    else

    /* .......................................................................... */
    /*   menu_main_begin                                                          */

    if( ctrl_id == r_menu_main_begin )
    {
      g_scene->process_flag = true;
    }
    else

    /* .......................................................................... */
    /*   menu_main_screen_16bpp                                                   */

    if( ctrl_id == r_menu_main_screen_16bpp )
    {
      ( *g_w_main )->check_menu_item( r_menu_main_screen_16bpp );
      ( *g_w_main )->uncheck_menu_item( r_menu_main_screen_32bpp );

      g_app.ogl->change_screen_settings( g_app.ogl->screen_size.x, 
                                         g_app.ogl->screen_size.y, 
                                         16, 
                                         g_app.ogl->fullscreen_flag );
    }
    else

    /* .......................................................................... */
    /*   menu_main_screen_32bpp                                                   */

    if( ctrl_id == r_menu_main_screen_32bpp )
    {
      ( *g_w_main )->check_menu_item( r_menu_main_screen_32bpp );
      ( *g_w_main )->uncheck_menu_item( r_menu_main_screen_16bpp );

      g_app.ogl->change_screen_settings( g_app.ogl->screen_size.x, 
                                         g_app.ogl->screen_size.y, 
                                         32, 
                                         g_app.ogl->fullscreen_flag );
    }
    else

    /* .......................................................................... */
    /*   menu_main_screen_640                                                     */

    if( ctrl_id == r_menu_main_screen_640 )
    {
      ( *g_w_main )->check_menu_item( r_menu_main_screen_640 );
      ( *g_w_main )->uncheck_menu_item( r_menu_main_screen_800 );
      ( *g_w_main )->uncheck_menu_item( r_menu_main_screen_1024 );
      g_app.ogl->change_screen_settings( 640, 480, g_app.ogl->col_depth, g_app.ogl->fullscreen_flag );
    }
    else

    /* .......................................................................... */
    /*   menu_main_screen_800                                                     */

    if( ctrl_id == r_menu_main_screen_800 )
    {
      ( *g_w_main )->uncheck_menu_item( r_menu_main_screen_640 );
      ( *g_w_main )->check_menu_item( r_menu_main_screen_800 );
      ( *g_w_main )->uncheck_menu_item( r_menu_main_screen_1024 );
      g_app.ogl->change_screen_settings( 800, 600, g_app.ogl->col_depth, g_app.ogl->fullscreen_flag );
    }
    else

    /* .......................................................................... */
    /*   menu_main_screen_1024                                                    */

    if( ctrl_id == r_menu_main_screen_1024 )
    {
      ( *g_w_main )->uncheck_menu_item( r_menu_main_screen_640 );
      ( *g_w_main )->uncheck_menu_item( r_menu_main_screen_800 );
      ( *g_w_main )->check_menu_item( r_menu_main_screen_1024 );
      g_app.ogl->change_screen_settings( 1024, 768, g_app.ogl->col_depth, g_app.ogl->fullscreen_flag );
    }
    else

    /* .......................................................................... */
    /*   menu_main_about                                                          */

    if( ctrl_id == r_menu_main_about )
    {
      ( *g_w_about )->center( ( *g_w_main ) );
      ( *g_w_about )->show( );
      g_app.disable_all_wnd_except( ( *g_w_about ) );
    }
    else

    /* .......................................................................... */
    /*   menu_main_quit                                                           */

    if( ctrl_id == r_menu_main_quit )
    {
      g_app.quit( );
    }
  }

  return DefWindowProc( hWnd, msg, wParam, lParam);
}

/* ------------------------------------------------------------------------------ */
/*   wnd_main_init                                                                */

void wnd_main_init( )
{
  ( *g_w_main ) = new c_app_wnd( WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | 
                               WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                               NULL,
                               g_app.str_class,
                               g_app.str_name,
                               LoadMenu( g_app.hInst, ( t_char* )r_menu_main ),
                               g_app.hInst,
                               NULL );

  /* ............................................................................ */

  s_rectl view_rect = { NO_CHANGE, 
                        NO_CHANGE, 
                        640,
                        480 };

  /* ............................................................................ */

  s_coord2l center = { g_app.desktop_size.x / 2, 
                       g_app.desktop_size.y / 2 };

  /* ............................................................................ */

  ( *g_w_main )->set_view( &view_rect );
  ( *g_w_main )->center( &center );
}

/* ------------------------------------------------------------------------------ */
/*   wnd_main                                                                     */

void wnd_main( )
{
  c_app_ogl* ogl = g_app.ogl;

  /* ............................................................................ */

  g_scene->process( );

  /* ............................................................................ */

  ogl->begin( );
  ogl->persp->begin( );

    g_scene->draw_persp( );

  ogl->persp->end( );

  /* ............................................................................ */

  ogl->ortho->set_proj( );
  ogl->ortho->begin( );

    g_scene->draw_ortho( );

  ogl->ortho->end( );
  ogl->end( );
}
