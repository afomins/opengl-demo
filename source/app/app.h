/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app.h                                                   */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"
#include "app\app_wnd.h"
#include "app\app_ogl.h"
#include "app\app_tex.h"
#include "app\app_fnt.h"
#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */

#ifndef __APP_
#define __APP_

  /* ............................................................................ */

  #define WND_COUNT 2

  #define WND_MAIN  0
  #define WND_ABOUT 1

  /* ............................................................................ */
  /*   c_app                                                                      */

  class c_app
  {
    public :

      HINSTANCE hInst;

      t_char* str_class;
      t_char* str_name;
      t_char* str_ver;
      t_char* str_path;

      t_bool quit_flag;

      s_coord2l desktop_size;

      c_app_wnd*   wnd[WND_COUNT];
      c_app_ogl*   ogl;
      c_app_tex*   tex;
      c_app_fnt*   fnt;
      c_app_timer* timer;
      
      /* ........................................................................ */

      void disable_all_wnd_except( c_app_wnd* wnd );

      void enable_all_wnd( );

      void null_wnd( );

      /* ........................................................................ */

      void register_class( );

      void set_path( );

      void quit( );

      void set_desktop_size( );

      /* ........................................................................ */

      c_app( t_char* str_class,
             t_char* str_name,
             t_char* str_ver );

      ~c_app( );

      /* ........................................................................ */
  };

  /* ............................................................................ */

  extern c_app g_app;

  /* ............................................................................ */

#endif