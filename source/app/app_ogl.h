/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app_ogl.h                                               */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 20.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"
#include "app\app_wnd.h"

#include <gl\gl.h>
#include <gl\glu.h>

/* ------------------------------------------------------------------------------ */

#ifndef __APP_OGL_
#define __APP_OGL_
  
  /* ............................................................................ */

  #define ATTRIB_NO_CHANGE -1

  /* ............................................................................ */
  /*   c_app_ogl_ortho                                                            */

  class c_app_ogl_ortho
  {
    public :

      s_rectl view;

      /* ........................................................................ */

      void set_proj( );

      void begin( );

      void end( );

      /* ........................................................................ */

      c_app_ogl_ortho( c_app_wnd* wnd );
  };

  /* ............................................................................ */
  /*   c_app_persp                                                                */

  class c_app_ogl_persp
  {
    public :

      s_rectl view;

      t_double fov;
      t_double aspect;
      t_double z_near;
      t_double z_far;

      s_coord3d eye;
      s_coord3d center;
      s_coord3d up;

      /* ........................................................................ */

      void set_proj( );

      void begin( );

      void end( );

      void set_attrib( t_double fov,
                       t_double aspect );

      void set_correct_aspect( );

      /* ........................................................................ */

      c_app_ogl_persp( c_app_wnd* wnd );
  };
  
  /* ............................................................................ */
  /*   c_app_ogl                                                                  */

  class c_app_ogl
  {
    public :

      HGLRC hRC;

      s_rectl view;

      t_bool    fullscreen_flag;
      s_coord2l screen_size;
      s_coord2l desktop_size;

      t_long col_depth;

      c_app_wnd* wnd;

      c_app_ogl_ortho* ortho;
      c_app_ogl_persp* persp;

      /* ........................................................................ */

      void begin( );

      void end( );

      /* ........................................................................ */

      void change_screen_settings( t_long width, 
                                   t_long height, 
                                   t_long depth,
                                   t_bool fullscreen_flag );

      void update_viewport( );

      /* ........................................................................ */

      c_app_ogl( c_app_wnd* wnd,
                 t_long     width,
                 t_long     height, 
                 t_long     depth,
                 t_bool     fullscreen_flag );

      ~c_app_ogl( );
  };

  /* ............................................................................ */

  void ogl_init( );

  /* ............................................................................ */

#endif
