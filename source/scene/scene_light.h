/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_light.h                                         */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 31.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "def_main.h"

/* ------------------------------------------------------------------------------ */

#ifndef __SCENE_LIGHT_
#define __SCENE_LIGHT_

  /* ............................................................................ */

  #define MAX_LIGHTS 8

  /* ............................................................................ */
  /*   c_scene_light                                                              */
  
  class c_scene_light
  {
    public :

      GLenum id;

      t_bool on_flag;

      s_col4f ambient;
      s_col4f diffuse;
      s_col4f specular;

      s_coord3f pos;
      s_coord3f dir;

      /* ........................................................................ */

      void set_ambient( t_float r,
                        t_float g,
                        t_float b,
                        t_float a );

      void set_diffuse( t_float r,
                        t_float g,
                        t_float b,
                        t_float a );

      void set_specular( t_float r,
                         t_float g,
                         t_float b,
                         t_float a );

      void set_pos( t_float x,
                    t_float y,
                    t_float z );

      void set_dir( t_float x,
                    t_float y,
                    t_float z );

      /* ........................................................................ */

      void begin( );

      void end( );

      /* ........................................................................ */

      c_scene_light( GLenum id );
   };

  /* ............................................................................ */
  /*   c_scene_light_model                                                        */
  
  class c_scene_light_model
  {
    public :

      t_bool  local_viewer;
      t_bool  two_side;
      s_col4f ambient;

      /* ........................................................................ */

      c_scene_light* light[MAX_LIGHTS];

      /* ........................................................................ */

      void set_ambient( t_float r,
                        t_float g,
                        t_float b,
                        t_float a );

      void set_local_viewer( t_bool value );

      void set_two_side( t_bool value );

      /* ........................................................................ */

      void begin( );

      void end( );

      /* ........................................................................ */

      c_scene_light_model( );

      ~c_scene_light_model( );
   };

  /* ............................................................................ */

#endif