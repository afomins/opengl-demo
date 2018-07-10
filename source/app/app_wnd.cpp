/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app_wnd.cpp                                             */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "app\app_wnd.h"

/* ------------------------------------------------------------------------------ */
/*   c_app_wnd                                                                    */

c_app_wnd::c_app_wnd( HINSTANCE hInst,
                      t_char*   template_name,
                      HWND      parent,
                      DLGPROC   dialog_proc,
                      LPARAM    init_param )
{
  hWnd = CreateDialogParam( hInst,
                            template_name,
                            parent,
                            dialog_proc,
                            init_param );

  hDC = GetDC( hWnd );

  /* ............................................................................ */

  update_pos_and_view( );
  update_view_offset( );

  /* ............................................................................ */

  show_flag    = false;
  disable_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   c_wnd                                                                        */

c_app_wnd::c_app_wnd( t_ulong   style,
                      t_ulong   ex_style,
                      t_char*   class_name,
                      t_char*   window_name,
                      HMENU     hMenu,
                      HINSTANCE hInst,
                      LPVOID    lpParam )
{
  s_rectl pos = { 100, 100, 400, 300 };

  /* ............................................................................ */

  hWnd = CreateWindowEx( ex_style,
                         class_name,
                         window_name,
                         style,
                         pos.x,
                         pos.y,
                         pos.width,
                         pos.height,
                         NULL,
                         hMenu,
                         hInst,
                         NULL );

  hDC = GetDC( hWnd );

  /* ............................................................................ */

  update_pos_and_view( );
  update_view_offset( );

  /* ............................................................................ */

  show_flag    = false;
  disable_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   ~c_app_wnd                                                                   */

c_app_wnd::~c_app_wnd( )
{
  DeleteDC( hDC );
  EndDialog( hWnd, 0 );
}

/* ------------------------------------------------------------------------------ */
/*   show                                                                         */

void c_app_wnd::show( )
{
  ShowWindow( hWnd, SW_SHOW );

  /* ............................................................................ */

  show_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   hide                                                                         */

void c_app_wnd::hide( )
{
  ShowWindow( hWnd, SW_HIDE );

  /* ............................................................................ */

  show_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   toggle_show                                                                  */

void c_app_wnd::toggle_show( )
{
  if( show_flag ) hide( );
  else            show( );
}

/* ------------------------------------------------------------------------------ */
/*   maximize                                                                     */

void c_app_wnd::maximize( )
{
  ShowWindow( hWnd, SW_MAXIMIZE );

  /* ............................................................................ */

  show_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   redraw                                                                       */

void c_app_wnd::redraw( )
{
  hide( );
  show( );
}

/* ------------------------------------------------------------------------------ */
/*   enable                                                                       */

void c_app_wnd::enable( )
{
  t_long old_dw_style = GetWindowLong( hWnd, GWL_STYLE );

  /* ............................................................................ */

  SetWindowLong( hWnd,
                 GWL_STYLE,
                 old_dw_style ^ WS_DISABLED );

  /* ............................................................................ */

  disable_flag = false;
}

/* ------------------------------------------------------------------------------ */
/*   disable                                                                      */

void c_app_wnd::disable( )
{
  t_long old_dw_style = GetWindowLong( hWnd, GWL_STYLE );

  /* ............................................................................ */

  SetWindowLong( hWnd,
                 GWL_STYLE,
                 old_dw_style | WS_DISABLED );
  
  /* ............................................................................ */

  disable_flag = true;
}

/* ------------------------------------------------------------------------------ */
/*   toggle_enable                                                                */

void c_app_wnd::toggle_enable( )
{
  if( disable_flag ) enable( );
  else               disable( );
}

/* ------------------------------------------------------------------------------ */
/*   center                                                                       */

void c_app_wnd::center( s_coord2l* center )
{
  s_rectl pos_rect = { center->x - pos.width / 2,
                       center->y - pos.height / 2,
                       NO_CHANGE,
                       NO_CHANGE };

  /* ............................................................................ */

  set_pos( &pos_rect );
}

/* ------------------------------------------------------------------------------ */
/*   center                                                                       */

void c_app_wnd::center( c_app_wnd* wnd )
{
  s_rectl pos_rect = { wnd->pos.x + wnd->pos.width / 2 - pos.width / 2,
                       wnd->pos.y + wnd->pos.height / 2 - pos.height / 2,
                       NO_CHANGE,
                       NO_CHANGE };

  /* ............................................................................ */

  set_pos( &pos_rect );
}

/* ------------------------------------------------------------------------------ */
/*   update_pos                                                                   */

void c_app_wnd::update_pos( )
{
  RECT pos_rect;

  /* ............................................................................ */

  GetWindowRect( hWnd, &pos_rect );

  /* ............................................................................ */

  pos.x      = pos_rect.left;
  pos.y      = pos_rect.top;
  pos.width  = pos_rect.right - pos_rect.left;
  pos.height = pos_rect.bottom - pos_rect.top;
}

/* ------------------------------------------------------------------------------ */
/*   update_view                                                                  */

void c_app_wnd::update_view( )
{
  RECT view_rect;

  /* ............................................................................ */

  GetClientRect( hWnd, &view_rect );

  /* ............................................................................ */

  view.x      = view_rect.left;
  view.y      = view_rect.top;
  view.width  = view_rect.right - view_rect.left;
  view.height = view_rect.bottom - view_rect.top;
}

/* ------------------------------------------------------------------------------ */
/*   update_pos_and_view                                                          */

void c_app_wnd::update_pos_and_view( )
{
  update_pos( );
  update_view( );
}

/* ------------------------------------------------------------------------------ */
/*   update_view_offset                                                              */

void c_app_wnd::update_view_offset( )
{
  RECT view_rect;
  RECT pos_rect;

  /* ............................................................................ */

  GetClientRect( hWnd, &view_rect );
  GetWindowRect( hWnd, &pos_rect );

  /* ............................................................................ */

  view_offset.x = ( pos_rect.right - pos_rect.left ) - ( view_rect.right - view_rect.left );
  view_offset.y = ( pos_rect.bottom - pos_rect.top ) - ( view_rect.bottom - view_rect.top );
}

/* ------------------------------------------------------------------------------ */
/*   set_view                                                                     */

void c_app_wnd::set_view( s_rectl* view_rect )
{
  if( view_rect->width  != NO_CHANGE ) pos.width  = view_rect->width + view_offset.x;
  if( view_rect->height != NO_CHANGE ) pos.height = view_rect->height + view_offset.y;

  /* ............................................................................ */

  SetWindowPos( hWnd,
                NULL,
                pos.x,
                pos.y,
                pos.width,
                pos.height,
                SWP_SHOWWINDOW );

  /* ............................................................................ */

  update_view( );
}

/* ------------------------------------------------------------------------------ */
/*   set_pos                                                                      */

void c_app_wnd::set_pos( s_rectl* pos_rect )
{
  if( pos_rect->x      != NO_CHANGE ) pos.x      = pos_rect->x;
  if( pos_rect->y      != NO_CHANGE ) pos.y      = pos_rect->y;
  if( pos_rect->width  != NO_CHANGE ) pos.width  = pos_rect->width;
  if( pos_rect->height != NO_CHANGE ) pos.height = pos_rect->height;

  /* ............................................................................ */

  SetWindowPos( hWnd,
                NULL,
                pos.x,
                pos.y,
                pos.width,
                pos.height,
                SWP_SHOWWINDOW );

  /* ............................................................................ */

  update_view( );
}

/* ------------------------------------------------------------------------------ */
/*   set_long                                                                     */

void c_app_wnd::set_long( t_int   index,
                          t_ulong value )
{
  SetWindowLong( hWnd, index, value );
}

/* ------------------------------------------------------------------------------ */
/*   get_long                                                                     */

t_ulong c_app_wnd::get_long( t_int index )
{
  return GetWindowLong( hWnd, index );
}

/* ------------------------------------------------------------------------------ */
/*   ctrl_set_str                                                                 */

void c_app_wnd::ctrl_set_str( t_long  ctrl_id, 
                              t_char* str )
{
  SetDlgItemText( hWnd, ctrl_id, str );
}

/* ------------------------------------------------------------------------------ */
/*   ctrl_set_long                                                                */

void c_app_wnd::ctrl_set_long( t_long ctrl_id,
                               t_long num )
{
  t_char* str = crt_str( num );

  /* ............................................................................ */

  ctrl_set_str( ctrl_id, str );
}

/* ------------------------------------------------------------------------------ */
/*   ctrl_set_double                                                              */

void c_app_wnd::ctrl_set_double( t_long   ctrl_id,
                                 t_double num,
                                 t_short  digits )
{
  t_char* str = crt_str( num, digits );

  /* ............................................................................ */
    
  ctrl_set_str( ctrl_id, str );
}

/* ------------------------------------------------------------------------------ */
/*   ctrl_get_str                                                                 */

t_char* c_app_wnd::ctrl_get_str( t_long ctrl_id )
{
  t_char  buf[STR_MAX_LEN];
  t_char* str;
  t_short len;

  /* ............................................................................ */
  
  GetDlgItemText( hWnd,
                  ctrl_id,
                  buf,
                  STR_MAX_LEN );

  /* ............................................................................ */

  len = strlen( buf ) + 1;
  str = ( t_char* )malloc( len );

  /* ............................................................................ */

  strcpy( str, buf );

  /* ............................................................................ */

  return str;
}

/* ------------------------------------------------------------------------------ */
/*   ctrl_get_long                                                                */

t_long c_app_wnd::ctrl_get_long( t_long ctrl_id )
{
  t_char  buf[STR_MAX_LEN];
  t_char* str;
  t_short len;

  /* ............................................................................ */

  GetDlgItemText( hWnd,
                  ctrl_id,
                  buf,
                  STR_MAX_LEN );

  /* ............................................................................ */

  len = strlen( buf ) + 1;
  str = ( t_char* )malloc( len );

  /* ............................................................................ */

  strcpy( str, buf );

  /* ............................................................................ */

  return atol( str );
}

/* ------------------------------------------------------------------------------ */
/*   ctrl_get_double                                                              */

t_double c_app_wnd::ctrl_get_double( t_long ctrl_id )
{
  t_char  buf[STR_MAX_LEN];
  t_char* str;
  t_short len;

  /* ............................................................................ */

  GetDlgItemText( hWnd,
                  ctrl_id,
                  buf,
                  STR_MAX_LEN );

  /* ............................................................................ */

  len = strlen( buf ) + 1;
  str = ( t_char* )malloc( len );

  /* ............................................................................ */

  strcpy( str, buf );

  /* ............................................................................ */

  return atof( str );
}

/* ------------------------------------------------------------------------------ */
/*   press_button                                                                 */

void c_app_wnd::press_button( t_long button_id )
{
  SendDlgItemMessage( hWnd,
                      button_id,
                      BM_SETCHECK,
                      ( WPARAM )BST_CHECKED,
                      ( LPARAM )0 );
}

/* ------------------------------------------------------------------------------ */
/*   unpress_button                                                               */

void c_app_wnd::unpress_button( t_long button_id )
{
  SendDlgItemMessage( hWnd,
                      button_id,
                      BM_SETCHECK,
                      ( WPARAM )BST_UNCHECKED,
                      ( LPARAM )0 );
}

/* ------------------------------------------------------------------------------ */
/*   check_menu_item                                                              */

void c_app_wnd::check_menu_item( t_long item_id )
{
  CheckMenuItem( GetMenu( hWnd ), item_id, MF_CHECKED );
}

/* ------------------------------------------------------------------------------ */
/*   uncheck_menu_item                                                            */

void c_app_wnd::uncheck_menu_item( t_long item_id )
{
  CheckMenuItem( GetMenu( hWnd ), item_id, MF_UNCHECKED );
}

/* ------------------------------------------------------------------------------ */
/*   set_title                                                                    */

void c_app_wnd::set_title( t_char* string )
{
  SetWindowText( hWnd, string );
}