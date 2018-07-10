/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app.cpp                                                 */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "app\app.h"

/* ------------------------------------------------------------------------------ */

c_app g_app( "Alexander 'manny' Fomin", "ogl", "1.0" );

c_app_wnd** g_w_main  = &g_app.wnd[WND_MAIN];
c_app_wnd** g_w_about = &g_app.wnd[WND_ABOUT];

/* ------------------------------------------------------------------------------ */
/*   c_app                                                                        */

c_app::c_app( t_char* str_class,
              t_char* str_name,
              t_char* str_ver )
{
  this->str_class = str_class;
  this->str_name  = str_name;
  this->str_ver   = str_ver;

  /* ............................................................................ */

  quit_flag = false;

  /* ............................................................................ */

  hInst = GetModuleHandle( NULL );

  /* ............................................................................ */

  set_desktop_size( );
  register_class( );
  set_path( );
  null_wnd( );
}

/* ------------------------------------------------------------------------------ */
/*   ~c_app                                                                       */

c_app::~c_app( )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < WND_COUNT; i++ )
  {
    delete wnd[i];
  }

  /* ............................................................................ */

  delete ogl;
  delete tex;
  delete fnt;

  UnregisterClass( str_class, hInst );
}

/* ------------------------------------------------------------------------------ */
/*   set_path                                                                     */

void c_app::set_path( )
{
  t_char   buf[STR_MAX_LEN];
  t_ushort len;

  /* ............................................................................ */

  GetCurrentDirectory( STR_MAX_LEN, buf );

  /* ............................................................................ */

  len      = strlen( buf ) + 1;
  str_path = ( t_char* )malloc( len );

  /* ............................................................................ */

  strcpy( str_path, buf );
}

/* ------------------------------------------------------------------------------ */
/*   set_desktop_size                                                             */

void c_app::set_desktop_size( )
{
  desktop_size.x = GetSystemMetrics( SM_CXSCREEN );
  desktop_size.y = GetSystemMetrics( SM_CYSCREEN );
}

/* ------------------------------------------------------------------------------ */
/*   register_class                                                               */

void c_app::register_class( )
{
  WNDCLASSEX wcex;

  /* ............................................................................ */

  wcex.cbSize        = sizeof( WNDCLASSEX );
  wcex.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wcex.lpfnWndProc   = ( WNDPROC )wnd_main_proc;
  wcex.cbClsExtra    = 0;
  wcex.cbWndExtra    = 0;
  wcex.hInstance     = hInst;
  wcex.hCursor       = LoadCursor( NULL, IDC_ARROW );
  wcex.hIcon         = NULL;
  wcex.hIconSm       = wcex.hIcon;
  wcex.hbrBackground = ( HBRUSH )COLOR_WINDOW;
  wcex.lpszMenuName  = NULL;
  wcex.lpszClassName = str_class;

  /* ............................................................................ */

  RegisterClassEx( &wcex );
}

/* ------------------------------------------------------------------------------ */
/*   disable_wnd                                                                  */

void c_app::disable_all_wnd_except( c_app_wnd* wnd )
{
  t_byte i;

  /* ............................................................................ */

  for( i = 0; i < WND_COUNT; i++ )
  {
    if( this->wnd[i] != NULL) 
    {
      this->wnd[i]->disable( );
    }
  }

  /* ............................................................................ */

  if( wnd != NULL) 
  {
    wnd->enable( );
  }
}

/* ------------------------------------------------------------------------------ */
/*   enable_wnd                                                                   */

void c_app::enable_all_wnd( )
{
  t_byte i;

  /* ............................................................................ */

  for( i = 0; i < WND_COUNT; i++ )
  {
    if( this->wnd[i] != NULL) 
    {
      this->wnd[i]->enable( );
    }
  }
}

/* ------------------------------------------------------------------------------ */
/*   null_wnd                                                                     */

void c_app::null_wnd( )
{
  t_byte i;

  /* ............................................................................ */

  for( i = 0; i < WND_COUNT; i++ )
  {
    wnd[i] = NULL;
  }
}

/* ------------------------------------------------------------------------------ */
/*   quit                                                                         */

void c_app::quit( )
{
  quit_flag = true;
}