/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\scene\scene.cpp                                             */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 24.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "scene\scene.h"
#include "app\app_timer.h"
#include "app\app.h"

/* ------------------------------------------------------------------------------ */

c_scene* g_scene;

/* ------------------------------------------------------------------------------ */
/*   c_scene                                                                      */

c_scene::c_scene( c_app_ogl* ogl )
{
  /* ............................................................................ */
  /*   script                                                                     */

  script_00 = new c_scene_script_00( "startup" );
  script_01 = new c_scene_script_01( "appear cube points" );
  script_02 = new c_scene_script_02( "appear cube lines" );
  script_03 = new c_scene_script_03( "move cube to old pos" );
  script_04 = new c_scene_script_04( "clone cubes" );
  script_05 = new c_scene_script_05( "explode" );

  script_rotate_cubes            = new c_scene_script_rotate_cubes( "rotate cubes" );
  script_rotate_sky              = new c_scene_script_rotate_sky( "rotate sky" );
  script_change_fov              = new c_scene_script_change_fov( "change fov" );
  script_change_rot_vect         = new c_scene_script_change_rot_vect( "change rot_vect" );
  script_change_sky_rot_vect     = new c_scene_script_change_sky_rot_vect( "change sky rot_vect" );
  script_rnd_change_rot_vect     = new c_scene_script_rnd_change_rot_vect( "rnd change rot_vect" );
  script_rnd_change_sky_rot_vect = new c_scene_script_rnd_change_sky_rot_vect( "rnd change sky rot_vect" );
  script_change_cube_col         = new c_scene_script_change_cube_col( "change cube col" );

  /* ............................................................................ */

  this->ogl               = ogl;
  draw_persp_flag         = true;
  draw_ortho_flag         = true;
  process_flag            = false;
      
  /* ............................................................................ */

  build_cube_coord( 1.2 );

  /* ............................................................................ */

  rot_angle  = 0.0;
  rot_speed  = 0.03;
  rot_vect.x = 0.0;
  rot_vect.y = 1.0;
  rot_vect.z = 0.0;

  /* ............................................................................ */

  sky.center.x = ogl->persp->eye.x;
  sky.center.y = ogl->persp->eye.y;
  sky.center.z = ogl->persp->eye.z;

  /* ............................................................................ */

  glMaterialf( GL_FRONT, GL_SHININESS, 128.0 );
}

/* ------------------------------------------------------------------------------ */
/*   ~c_scene                                                                     */

c_scene::~c_scene( )
{
  delete script_00;
  delete script_01;
  delete script_02;
  delete script_03;
  delete script_04;
  delete script_05;

  delete script_rotate_cubes;
  delete script_change_fov;
  delete script_change_rot_vect;
  delete script_change_sky_rot_vect;
  delete script_rnd_change_rot_vect;
  delete script_rnd_change_sky_rot_vect;
  delete script_change_cube_col;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_scene::process( )
{
  /* ............................................................................ */

  if( !process_flag ) return;

  /* ............................................................................ */

  if( script_00->get_process_flag( ) ) script_00->process( );
  if( script_01->get_process_flag( ) ) script_01->process( );
  if( script_02->get_process_flag( ) ) script_02->process( );
  if( script_03->get_process_flag( ) ) script_03->process( );
  if( script_04->get_process_flag( ) ) script_04->process( );
  if( script_05->get_process_flag( ) ) script_05->process( );

  if( script_rotate_cubes->get_process_flag( ) )            script_rotate_cubes->process( );
  if( script_rotate_sky->get_process_flag( ) )              script_rotate_sky->process( );
  if( script_change_fov->get_process_flag( ) )              script_change_fov->process( );
  if( script_change_rot_vect->get_process_flag( ) )         script_change_rot_vect->process( );
  if( script_change_sky_rot_vect->get_process_flag( ) )     script_change_sky_rot_vect->process( );
  if( script_rnd_change_rot_vect->get_process_flag( ) )     script_rnd_change_rot_vect->process( );
  if( script_rnd_change_sky_rot_vect->get_process_flag( ) ) script_rnd_change_sky_rot_vect->process( );
  if( script_change_cube_col->get_process_flag( ) )         script_change_cube_col->process( );
}

/* ------------------------------------------------------------------------------ */
/*   build_cube_coord                                                             */

void c_scene::build_cube_coord( t_double mult )
{
  t_byte x;
  t_byte z;
  t_long id;

  /* ............................................................................ */

  for( z = 0; z < 3; z++ )
  {
    for( x = 0; x < 3; x++ )
    {
      id = z * 3 + x;

      cube[id].center.x = ( x * CUBE_SIZE - CUBE_SIZE ) * mult;
      cube[id].center.z = ( z * CUBE_SIZE - CUBE_SIZE ) * mult;
      cube[id].center.y = ( -CUBE_SIZE ) * mult;

      cube[id + 9].center.x = ( x * CUBE_SIZE - CUBE_SIZE ) * mult;
      cube[id + 9].center.z = ( z * CUBE_SIZE - CUBE_SIZE ) * mult;
      cube[id + 9].center.y = 0;

      cube[id + 18].center.x = ( x * CUBE_SIZE - CUBE_SIZE ) * mult;
      cube[id + 18].center.z = ( z * CUBE_SIZE - CUBE_SIZE ) * mult;
      cube[id + 18].center.y = ( CUBE_SIZE ) * mult;
    }
  }
}

/* ------------------------------------------------------------------------------ */
/*   draw_persp                                                                   */

void c_scene::draw_persp( )
{
  /* ............................................................................ */

  if( !draw_persp_flag ) return;

  /* ............................................................................ */

  t_long i;

  /* ............................................................................ */

  sky.draw( );

  /* ............................................................................ */

  glRotated( rot_angle, rot_vect.x, rot_vect.y, rot_vect.z );

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    if( cube[i].draw_flag ) cube[i].draw( );
  }
}

/* ------------------------------------------------------------------------------ */
/*   draw_ortho                                                                   */

void c_scene::draw_ortho( )
{
  /* ............................................................................ */

  if( !draw_ortho_flag ) return;

  /* ............................................................................ */

  t_char* str_fps = crt_str( "FPS : ", g_timer->fps );
  t_char* str_sec = crt_str( "SEC : ", g_timer->current_sec );

  /* ............................................................................ */

  glColor4f( 1.0, 1.0, 1.0, 0.3 );

  glBegin( GL_LINE_LOOP );

    glVertex2i( ogl->view.x, ogl->view.y );
    glVertex2i( ogl->view.x + ogl->view.width - 1 , ogl->view.y );
    glVertex2i( ogl->view.x + ogl->view.width - 1 , ogl->view.y + ogl->view.height - 1 );
    glVertex2i( ogl->view.x, ogl->view.y + ogl->view.height - 1 );

  glEnd( );

  glEnable( GL_TEXTURE_2D );

    /* .......................................................................... */

    glColor4f( 1.0, 1.0, 1.0, 1.0 );

    g_f_std->str_out( "from_manny", ( t_float )ogl->view.width - 62, 2, 1, 1 );
    g_f_std->str_out( str_fps, 2, 12, 1, 1 );
    g_f_std->str_out( str_sec, 2, 2, 1, 1 );

    g_tex_manny->draw( ( t_float )ogl->view.width - 110, ( t_float )ogl->view.height - 128, 1.0, 1.0 );

    /* .......................................................................... */

  glDisable( GL_TEXTURE_2D );

  /* ............................................................................ */

  free( str_fps );
  free( str_sec );
}

/* ------------------------------------------------------------------------------ */
/*   appear_cube_points                                                           */

void c_scene::appear_cube_points( t_long delta )
{
  t_long i;

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    cube[i].appear_points( delta );
  }
}

/* ------------------------------------------------------------------------------ */
/*   fade_cube_points                                                             */

void c_scene::fade_cube_points( t_long delta )
{
  t_long i;

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    cube[i].fade_points( delta );
  }
}

/* ------------------------------------------------------------------------------ */
/*   appear_cube_lines                                                            */

void c_scene::appear_cube_lines( t_long delta )
{
  t_long i;

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    cube[i].appear_lines( delta );
  }
}

/* ------------------------------------------------------------------------------ */
/*   fade_cube_lines                                                              */

void c_scene::fade_cube_lines( t_long delta )
{
  t_long i;

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    cube[i].fade_lines( delta );
  }
}

/* ------------------------------------------------------------------------------ */
/*   appear_cube_sides                                                            */

void c_scene::appear_cube_sides( t_long delta )
{
  t_long i;

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    cube[i].appear_sides( delta );
  }
}

/* ------------------------------------------------------------------------------ */
/*   fade_cube_sides                                                              */

void c_scene::fade_cube_sides( t_long delta )
{
  t_long i;

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    cube[i].fade_sides( delta );
  }
}

/* ------------------------------------------------------------------------------ */
/*   check_point_statuss                                                          */

t_bool c_scene::check_point_statuss( t_byte statuss )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    if( cube[i].check_point_statuss( statuss ) ) return false;
  }

  /* ............................................................................ */

  return true;
}

/* ------------------------------------------------------------------------------ */
/*   chack_line_statuss                                                           */

t_bool c_scene::check_line_statuss( t_byte statuss )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    if( !cube[i].check_line_statuss( statuss ) ) return false;
  }

  /* ............................................................................ */

  return true;
}

/* ------------------------------------------------------------------------------ */
/*   chack_side_statuss                                                           */

t_bool c_scene::check_side_statuss( t_byte statuss )
{
  t_long i;

  /* ............................................................................ */

  for( i = 0; i < CUBE_COUNT; i++ )
  {
    if( !cube[i].check_side_statuss( statuss ) ) return false;
  }

  /* ............................................................................ */

  return true;
}
