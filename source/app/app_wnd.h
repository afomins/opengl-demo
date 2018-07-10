/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app_wnd.h                                               */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"

/* ------------------------------------------------------------------------------ */

#ifndef __APP_WND_
#define __APP_WND_

  /* ............................................................................ */

  #define NO_CHANGE -1

  /* ............................................................................ */

  class c_app_wnd
  {
    public :

      HWND  hWnd;
      HDC   hDC;
      
      t_bool show_flag;
      t_bool disable_flag;

      s_rectl view;
      s_rectl pos;

      s_coord2l view_offset;

      /* ........................................................................ */

      void show( );

      void hide( );

      void toggle_show( );

      void maximize( );

      void redraw( );

      /* ........................................................................ */

      void enable( );

      void disable( );

      void toggle_enable( );

      /* ........................................................................ */

      void center( s_coord2l* center );

      void center( c_app_wnd* wnd );

      /* ........................................................................ */
      
      void update_pos( );

      void update_view( );

      void update_pos_and_view( );

      void update_view_offset( );

      /* ........................................................................ */

      void set_view( s_rectl* view_rect );

      void set_pos( s_rectl* pos_rect );

      /* ......................................................................... */

      void set_long( t_int   index,
                     t_ulong value );

      t_ulong get_long( t_int index );

      /* ......................................................................... */

      void ctrl_set_str( t_long  ctrl_id, 
                         t_char* str );

      void ctrl_set_long( t_long ctrl_id,
                          t_long num );

      void ctrl_set_double( t_long   ctrl_id,
                            t_double num,
                            t_short  digits );

      t_char* ctrl_get_str( t_long ctrl_id );

      t_long ctrl_get_long( t_long ctrl_id );

      t_double ctrl_get_double( t_long ctrl_id );

      /* ......................................................................... */

      void press_button( t_long button_id );

      void unpress_button( t_long button_id );

      /* ......................................................................... */

      void check_menu_item( t_long item_id );

      void uncheck_menu_item( t_long item_id );

      /* ........................................................................ */

      void set_title( t_char* str );

      /* ......................................................................... */

      c_app_wnd( HINSTANCE hInst,
                 t_char*   template_name,
                 HWND      parent,
                 DLGPROC   dialog_proc,
                 LPARAM    init_param );

      c_app_wnd( t_ulong   style,
                 t_ulong   ex_style,
                 t_char*   class_name,
                 t_char*   window_name,
                 HMENU     hMenu,
                 HINSTANCE hInst,
                 LPVOID    lpParam );

      ~c_app_wnd( );

      /* ......................................................................... */
  };

  /* .[ main ]................................................................... */

  LRESULT CALLBACK wnd_main_proc( HWND   hWnd,
                                  UINT   msg,
                                  WPARAM wParam,
                                  LPARAM lParam );
  void wnd_main_init( );

  void wnd_main( );

  /* .[ about ].................................................................. */

  LRESULT CALLBACK wnd_about_proc( HWND   hWnd,
                                   UINT   msg,
                                   WPARAM wParam,
                                   LPARAM lParam );
  void wnd_about_init( );

  /* ............................................................................ */

  extern c_app_wnd** g_w_main;
  extern c_app_wnd** g_w_about;

  /* ............................................................................ */

#endif