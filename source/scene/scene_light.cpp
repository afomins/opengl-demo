/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene_light.cpp                                       */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 32.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"

/* ------------------------------------------------------------------------------ */
/*   c_scene_light                                                                */

c_scene_light_model::c_scene_light_model( )
{
  glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

  /* ............................................................................ */

  set_ambient( 0.9, 0.8, 0.9, 1.0 );
  set_local_viewer( false );
  set_two_side( false );

  /* ............................................................................ */

  light[0] = new c_scene_light( GL_LIGHT0 );
  light[1] = new c_scene_light( GL_LIGHT1 );
  light[2] = new c_scene_light( GL_LIGHT1 );
  light[3] = new c_scene_light( GL_LIGHT2 );
  light[4] = new c_scene_light( GL_LIGHT3 );
  light[5] = new c_scene_light( GL_LIGHT4 );
  light[6] = new c_scene_light( GL_LIGHT5 );
  light[7] = new c_scene_light( GL_LIGHT6 );
  light[8] = new c_scene_light( GL_LIGHT7 );

  /* ............................................................................ */

  light[0]->on_flag = true;
  light[1]->on_flag = true;

  light[1]->set_pos( -15.0, 0.0, -15.0 );
  light[1]->set_dir( 1.0, 1.0, 1.0 );
  
  light[1]->set_ambient( 0.3, 0.6, 0.5, 1.0 );
  light[1]->set_diffuse( 0.7, 0.3, 0.5, 1.0 );
  light[1]->set_specular( 0.5, 0.0, 0.6, 1.0 );

}

/* ------------------------------------------------------------------------------ */
/*   ~c_scene_light_model                                                         */

c_scene_light_model::~c_scene_light_model( )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < MAX_LIGHTS; i++ )
  {
    delete light[i];
  }
}

/* ------------------------------------------------------------------------------ */
/*   set_ambient                                                                  */

void c_scene_light_model::set_ambient( t_float r, 
                                       t_float g,
                                       t_float b,
                                       t_float a )
{
  t_float value[4];

  /* ............................................................................ */

  ambient.r = r;
  ambient.g = g;
  ambient.b = b;
  ambient.a = a;

  /* ............................................................................ */

  value[0] = r;
  value[1] = g;
  value[2] = b;
  value[3] = a;

  /* ............................................................................ */

  glLightModelfv( GL_LIGHT_MODEL_AMBIENT, value );
}

/* ------------------------------------------------------------------------------ */
/*   set_local_viewer                                                             */

void c_scene_light_model::set_local_viewer( t_bool value )
{
  local_viewer = value;

  /* ............................................................................ */

  glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, value );
}

/* ------------------------------------------------------------------------------ */
/*   set_two_side                                                                 */

void c_scene_light_model::set_two_side( t_bool value )
{
  two_side = value;

  /* ............................................................................ */

  glLightModelf( GL_LIGHT_MODEL_TWO_SIDE, value );
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_light_model::begin( )
{
  t_long i;

  /* ............................................................................ */

  glEnable( GL_LIGHTING );

  /* ............................................................................ */

  for( i = 0; i < MAX_LIGHTS; i++ )
  {
    if( light[i]->on_flag ) light[i]->begin( );
  }
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_light_model::end( )
{
  t_long i;

  /* ............................................................................ */

  glDisable( GL_LIGHTING );

  /* ............................................................................ */

  for( i = 0; i < MAX_LIGHTS; i++ )
  {
    if( light[i]->on_flag ) light[i]->end( );
  }
}

/* ------------------------------------------------------------------------------ */
/*   c_scene_light                                                                */

c_scene_light::c_scene_light( GLenum id )
{
  this->id = id;
  on_flag  = false;

  /* ............................................................................ */

  set_ambient( 0.8, 0.4, 0.3, 1.0 );
  set_diffuse( 0.2, 0.6, 0.4, 1.0 );
  set_specular( 0.7, 0.6, 0.8, 1.0 );

  set_pos( 4.0, 7.0, 10.0 );
  set_dir( -1.0, -0.5, -0.0 );
}

/* ------------------------------------------------------------------------------ */
/*   set_ambient                                                                  */

void c_scene_light::set_ambient( t_float r,
                                 t_float g,
                                 t_float b,
                                 t_float a )
{
  t_float value[4];

  /* ............................................................................ */

  ambient.r = r;
  ambient.g = g;
  ambient.b = b;
  ambient.a = a;

  /* ............................................................................ */

  value[0] = r;
  value[1] = g;
  value[2] = b;
  value[3] = a;

  /* ............................................................................ */

  glLightfv( id, GL_AMBIENT, value );
}

/* ------------------------------------------------------------------------------ */
/*   set_diffuse                                                                  */

void c_scene_light::set_diffuse( t_float r,
                                 t_float g,
                                 t_float b,
                                 t_float a )
{
  t_float value[4];

  /* ............................................................................ */

  diffuse.r = r;
  diffuse.g = g;
  diffuse.b = b;
  diffuse.a = a;

  /* ............................................................................ */

  value[0] = r;
  value[1] = g;
  value[2] = b;
  value[3] = r;

  /* ............................................................................ */

  glLightfv( id, GL_DIFFUSE, value );
}

/* ------------------------------------------------------------------------------ */
/*   set_specular                                                                 */

void c_scene_light::set_specular( t_float r,
                                  t_float g,
                                  t_float b,
                                  t_float a )
{
  t_float value[4];

  /* ............................................................................ */

  specular.r = r;
  specular.g = g;
  specular.b = b;
  specular.a = a;

  /* ............................................................................ */

  value[0] = r;
  value[1] = g;
  value[2] = b;
  value[3] = a;

  /* ............................................................................ */

  glLightfv( id, GL_SPECULAR, value );
}

/* ------------------------------------------------------------------------------ */
/*   set_pos                                                                      */

void c_scene_light::set_pos( t_float x,
                             t_float y,
                             t_float z )
{
  t_float value[4];

  /* ............................................................................ */

  pos.x = x;
  pos.y = y;
  pos.z = z;

  /* ............................................................................ */

  value[0] = x;
  value[1] = y;
  value[2] = z;
  value[3] = 1.0;

  /* ............................................................................ */

  glLightfv( id, GL_POSITION, value );
}

/* ------------------------------------------------------------------------------ */
/*   set_dir                                                                      */

void c_scene_light::set_dir( t_float x,
                             t_float y,
                             t_float z )
{
  t_float value[3];

  /* ............................................................................ */

  dir.x = x;
  dir.y = y;
  dir.z = z;

  /* ............................................................................ */

  value[0] = x;
  value[1] = y;
  value[2] = z;

  /* ............................................................................ */

  glLightfv( id, GL_SPOT_DIRECTION, value );
}

/* ------------------------------------------------------------------------------ */
/*   begin                                                                        */

void c_scene_light::begin( )
{
  glEnable( id );
}

/* ------------------------------------------------------------------------------ */
/*   end                                                                          */

void c_scene_light::end( )
{
  glDisable( id );
}