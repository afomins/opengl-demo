/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app_tex.cpp                                             */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 22.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "app\app_tex.h"

/* ------------------------------------------------------------------------------ */

c_app_tex_inst* g_tex_manny;
c_app_tex_inst* g_tex_empty;
c_app_tex_inst* g_tex_00;
c_app_tex_inst* g_tex_sky_front;
c_app_tex_inst* g_tex_sky_back;
c_app_tex_inst* g_tex_sky_left;
c_app_tex_inst* g_tex_sky_right;
c_app_tex_inst* g_tex_sky_up;
c_app_tex_inst* g_tex_sky_down;


/* ------------------------------------------------------------------------------ */
/*   c_app_tex                                                                    */

c_app_tex::c_app_tex( )
{
  first = NULL;
  last  = NULL;
  count = 0;

  /* ............................................................................ */

  load( TEX_EMPTY_NAME, TEX_NO_ALPHA, false );
  kill_last_buf( );
  g_tex_empty = last;

  /* ............................................................................ */

  load( "data/pic/fallout.bmp", "data/pic/fallout_alpha.bmp", false );
  kill_last_buf( );
  g_tex_manny = last;

  /* ............................................................................ */

  load( "data/pic/tex_00.bmp", TEX_NO_ALPHA, true );
  kill_last_buf( );
  g_tex_00 = last;

  /* ............................................................................ */

  load( "data/sky/hl_front.bmp", TEX_NO_ALPHA, false );
  kill_last_buf( );
  g_tex_sky_front = last;

  load( "data/sky/hl_back.bmp", TEX_NO_ALPHA, false );
  kill_last_buf( );
  g_tex_sky_back = last;

  load( "data/sky/hl_left.bmp", TEX_NO_ALPHA, false );
  kill_last_buf( );
  g_tex_sky_left = last;

  load( "data/sky/hl_right.bmp", TEX_NO_ALPHA, false );
  kill_last_buf( );
  g_tex_sky_right = last;

  load( "data/sky/hl_up.bmp", TEX_NO_ALPHA, false );
  kill_last_buf( );
  g_tex_sky_up = last;

  load( "data/sky/hl_down.bmp", TEX_NO_ALPHA, false );
  kill_last_buf( );
  g_tex_sky_down = last;
}

/* ------------------------------------------------------------------------------ */
/*   ~c_app_tex                                                                   */

c_app_tex::~c_app_tex( )
{
  if( count == 1 )
  {
    delete first;
  }
  else
  if( count > 1 )
  {
    c_app_tex_inst* cur = first->next;

    /* .......................................................................... */

    while( cur != last )
    {
      glDeleteTextures( 1, &cur->prev->id );
      delete cur->prev;

      cur = cur->next;
    }

    glDeleteTextures( 1, &cur->id );
    delete cur;
  }

  /* ............................................................................ */

  count = 0;
  first = NULL;
  last  = NULL;
}

/* ------------------------------------------------------------------------------ */
/*   load                                                                         */

void c_app_tex::load( t_char* tex_name,
                      t_char* alpha_name,
                      t_bool  mipmap_flag )
{
  c_app_tex_inst* tex = new c_app_tex_inst( count, tex_name, alpha_name, mipmap_flag );

  /* ............................................................................ */

  if( count == 0 )
  {
    first = tex;
    last  = tex;
     
    /* .......................................................................... */

    tex->next = NULL;
    tex->prev = NULL;
  }
  else
  {
    tex->next = NULL;
    tex->prev = last;

    /* .......................................................................... */

    last->next = tex;
    last       = tex;
  }

  /* ............................................................................ */

  count++;
}

/* ------------------------------------------------------------------------------ */
/*   kill_last_buf                                                                */

void c_app_tex::kill_last_buf( )
{
  last->kill_buf( );
}

/* ------------------------------------------------------------------------------ */
/*   c_app_tex_inst                                                               */

c_app_tex_inst::c_app_tex_inst( t_ulong tex_id, 
                                t_char* tex_name,
                                t_char* alpha_name,
                                t_bool  mipmap_flag )
{
  tex_buf   = NULL;
  alpha_buf = NULL;

  /* ............................................................................ */

  id  = tex_id;
  bpp = 24;

  /* ............................................................................ */

  if( tex_name == TEX_EMPTY_NAME ) tex_buf = load_empty( );
  else                             tex_buf = load_bmp( tex_name );

  if( alpha_name != TEX_NO_ALPHA ) 
  {
    bpp       = 32;
    alpha_buf = load_bmp( alpha_name );

    apply_alpha( );
  }

  /* ............................................................................ */

  register_ogl_tex( mipmap_flag );
}

/* ------------------------------------------------------------------------------ */
/*   load_bmp                                                                     */

t_byte* c_app_tex_inst::load_bmp( t_char* tex_name )
{
  t_byte* data;
  t_byte* file_data;
  t_ulong file_size;
  t_ulong bytes_read;
  HANDLE  hFile;

  BITMAPFILEHEADER fBmp;
  BITMAPINFOHEADER iBmp;

  /* ............................................................................ */

  hFile = CreateFile( tex_name,
                      GENERIC_READ,
                      FILE_SHARE_READ,
                      NULL,
                      OPEN_EXISTING,
                      0,
                      NULL );

  /* ............................................................................ */

  ReadFile( hFile,
            &fBmp,
            sizeof( BITMAPFILEHEADER ),
            &bytes_read,
            NULL );

  ReadFile( hFile,
            &iBmp,
            sizeof( BITMAPINFOHEADER ),
            &bytes_read,
            NULL );

  /* ............................................................................ */

  file_size = GetFileSize( hFile, NULL ) - fBmp.bfOffBits;
  file_data = ( byte* )malloc( file_size );

  /* ............................................................................ */

  ReadFile( hFile,
            file_data,
            file_size,
            &bytes_read,
            NULL );

  CloseHandle( hFile );

  /* ............................................................................ */

  width  = iBmp.biWidth;
  height = iBmp.biHeight;

  /* ............................................................................ */

  s_coord2l i;
  t_long    img_byte_num  = 0;
  t_long    file_byte_num = 0;
  t_byte    allign_byte   = width % sizeof( t_long );

  /* ............................................................................ */

  data = ( t_byte* )malloc( width * height * 3 );

  /* ............................................................................ */

  for( i.y = 0; i.y < height; i.y++ )
  {
    for( i.x = 0; i.x < width; i.x++ )
    {
      data[img_byte_num + 2] = file_data[file_byte_num + 0];
      data[img_byte_num + 1] = file_data[file_byte_num + 1];
      data[img_byte_num + 0] = file_data[file_byte_num + 2];

      img_byte_num  += 3;
      file_byte_num += 3;
    }

    file_byte_num += allign_byte;
  }

  /* ............................................................................ */

  free( file_data );

  /* ............................................................................ */

  return data;
}

/* ------------------------------------------------------------------------------ */
/*   load_empty                                                                   */

t_byte* c_app_tex_inst::load_empty( )
{
  t_byte*   data;
  t_byte    bytes_per_pix;
  t_byte    pix_col       = 0;
  t_bool    pix_white     = true;
  t_bool    pix_inv       = false;
  s_coord2s pix           = { 0, 0 };
  t_ulong   data_size;
  t_ulong   i;

  /* ............................................................................ */

  bpp           = TEX_EMPTY_BPP;
  width         = TEX_EMPTY_WIDTH;
  height        = TEX_EMPTY_HEIGHT;
  bytes_per_pix = bpp / 8;

  /* ............................................................................ */

  data_size = width * height * bytes_per_pix;
  data      = ( t_byte* )malloc( data_size );

  /* ............................................................................ */

  for( i = 0; i < data_size; i += bytes_per_pix )
  {
    if( pix.x == width )
    {
      pix.x = 0;
      pix.y++;
    }

    /* ............................................................................ */

    if( pix.x % TEX_EMPTY_QUAD_SIZE == 0 ) 
    {
      pix_white = !pix_white;
    }

    if( ( pix.y % TEX_EMPTY_QUAD_SIZE == 0 ) && ( pix.x == 0) ) 
    {
      pix_inv = !pix_inv;
    }

    /* ............................................................................ */

    if( pix_white ) pix_col = 255;
    else            pix_col = 0;

    if( pix_inv )
    {
      if( pix_col == 255 ) pix_col = 0;
      else                 pix_col = 255;
    }

    /* ............................................................................ */

    data[i + 0] = pix_col;
    data[i + 1] = pix_col;
    data[i + 2] = pix_col;

    pix.x++;
  }

  /* ............................................................................ */

  return data;
}

/* ------------------------------------------------------------------------------ */
/*   apply_alpha                                                                  */

void c_app_tex_inst::apply_alpha( )
{
  t_byte* data;
  t_ulong data_size;
  t_ulong pix_count = width * height;
  t_ulong i;

  /* ............................................................................ */

  data_size = pix_count * 4;
  data      = ( byte* )malloc( data_size );

  /* ............................................................................ */

  for( i = 0; i < pix_count; i++ )
  {
    data[i * 4 + 0] = tex_buf[i * 3 + 0];
    data[i * 4 + 1] = tex_buf[i * 3 + 1];
    data[i * 4 + 2] = tex_buf[i * 3 + 2];
    data[i * 4 + 3] = alpha_buf[i * 3];
  }

  /* ............................................................................ */

  free( tex_buf );

  /* ............................................................................ */

  tex_buf = data;
}

/* ------------------------------------------------------------------------------ */
/*   register_ogl_tex                                                             */

void c_app_tex_inst::register_ogl_tex( t_bool mipmap_flag )
{
  GLenum tex_format;
  GLint  tex_components;

  /* ............................................................................ */

  if( bpp == 24 )
  {
    tex_components = 3;
    tex_format     = GL_RGB;
  }
  else
  {
    tex_components = 4;
    tex_format     = GL_RGBA;
  }

  /* ............................................................................ */

  glGenTextures( 1, &id );
  glBindTexture( GL_TEXTURE_2D, id );

  /* ............................................................................ */


  /* ............................................................................ */

  if( !mipmap_flag )
  {
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    glTexImage2D( GL_TEXTURE_2D,
                  0,
                  tex_components,
                  width,
                  height,
                  0,
                  tex_format,
                  GL_UNSIGNED_BYTE,
                  tex_buf );
  }
  else
  {
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    gluBuild2DMipmaps( GL_TEXTURE_2D,
                       4,
                       width,
                       height,
                       tex_format,
                       GL_UNSIGNED_BYTE,
                       tex_buf );
  }
}

/* ------------------------------------------------------------------------------ */
/*   kill_buff                                                                    */

void c_app_tex_inst::kill_buf( )
{
  free( tex_buf );
  free( alpha_buf );
}

/* ------------------------------------------------------------------------------ */
/*   select                                                                       */

void c_app_tex_inst::select( )
{
  glBindTexture( GL_TEXTURE_2D, id );
}

/* ------------------------------------------------------------------------------ */
/*   draw                                                                         */

void c_app_tex_inst::draw( t_float x,
                           t_float y,
                           t_float scale_x,
                           t_float scale_y )
{
  select( );

  /* ............................................................................ */

  glPushMatrix( );

    glTranslatef( x, y, 0.0 );
    glScalef( scale_x, scale_y, 0.0 );

    glBegin( GL_QUADS );

      glTexCoord2d( 0.0, 0.0 );
      glVertex2d( 0.0, 0.0 );

      glTexCoord2d( 0.0, 1.0 );
      glVertex2d( 0.0, height );

      glTexCoord2d( 1.0, 1.0 );
      glVertex2d( width, height );

      glTexCoord2d( 1.0, 0.0 );
      glVertex2d( width, 0.0 );

    glEnd( );

  glPopMatrix( );
}