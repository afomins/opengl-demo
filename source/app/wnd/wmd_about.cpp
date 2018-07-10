/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\wnd\wnd_about.cpp                                       */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_res.h"
#include "app\app.h"

/* ------------------------------------------------------------------------------ */
/*   wnd_about_proc                                                               */

LRESULT CALLBACK wnd_about_proc( HWND   hWnd,
                                 UINT   msg,
                                 WPARAM wParam,
                                 LPARAM lParam )
{

  /* .[ WM_COMMAND ]............................................................. */

  if( msg == WM_COMMAND )
  {
    t_long code_id   = HIWORD( wParam );
    t_long ctrl_id   = LOWORD( wParam );
    HWND   ctrl_hWnd = ( HWND)lParam;

    /* .[ ok ]................................................................... */

    if( ctrl_id == r_about_button_ok )
    {
      if( code_id == BN_CLICKED )
      {
        g_app.enable_all_wnd( );
        ( *g_w_about )->hide( );
      }
    }
  }

  return false;
}

/* -[ wnd_about_init ]----------------------------------------------------------- */

void wnd_about_init( )
{
  ( *g_w_about ) = new c_app_wnd( g_app.hInst,
                                ( t_char* )r_wnd_about,
                                ( *g_w_main )->hWnd,
                                ( DLGPROC )wnd_about_proc,
                                NULL );
  /* ............................................................................ */

  ( *g_w_about )->ctrl_set_str( r_about_text_prg, g_app.str_name );
  ( *g_w_about )->ctrl_set_str( r_about_text_ver, g_app.str_ver );
  ( *g_w_about )->ctrl_set_str( r_about_text_dev, g_app.str_class );
}