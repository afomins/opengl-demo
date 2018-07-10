/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app_fnt.cpp                                             */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 23.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "app\app_fnt.h"

/* ------------------------------------------------------------------------------ */

c_app_fnt_inst* g_f_std;

/* ------------------------------------------------------------------------------ */
/*   c_app_fnt                                                                    */

c_app_fnt::c_app_fnt( c_app_tex* tex )
{
  count = 0;
  first = NULL;
  last  = NULL;

  this->tex = tex;

  /* ............................................................................ */
  /*   f_std                                                                      */

  load( "data/font/std_8x8.bmp", "data/font/std_8x8.bmp", 8, 8 );

  g_f_std                = last;
  g_f_std->let[0].width  = 4;
  g_f_std->let[0].height = 1;

  /* ............................................................................ */
}

/* ------------------------------------------------------------------------------ */
/*   ~c_app_fnt                                                                   */

c_app_fnt::~c_app_fnt( )
{
  if( count == 1 )
  {
    delete first;
  }
  else
  if( count > 1 )
  {
    c_app_fnt_inst* cur = first->next;

    /* .......................................................................... */

    while( cur != last )
    {
      delete cur->prev;

      cur = cur->next;
    }

    delete cur;
  }

  /* ............................................................................ */

  count = 0;
  first = NULL;
  last  = NULL;
}

/* ------------------------------------------------------------------------------ */
/*   load                                                                         */

void c_app_fnt::load( t_char* tex_name,
                      t_char* alpha_name,
                      t_byte  let_width,
                      t_byte  let_height )
{
  c_app_fnt_inst* fnt = new c_app_fnt_inst( tex,
                                            count, 
                                            tex_name, 
                                            alpha_name, 
                                            let_width, 
                                            let_height );

  /* ............................................................................ */

  if( count == 0 )
  {
    first = fnt;
    last  = fnt;
     
    /* .......................................................................... */

    fnt->next = NULL;
    fnt->prev = NULL;
  }
  else
  {
    fnt->next = NULL;
    fnt->prev = last;

    /* .......................................................................... */

    last->next = fnt;
    last       = fnt;
  }

  /* ............................................................................ */

  count++;
}

/* ------------------------------------------------------------------------------ */
/*   c_app_fnt_inst                                                               */

c_app_fnt_inst::c_app_fnt_inst( c_app_tex* tex,
                                t_ulong    fnt_id,
                                t_char*    tex_name,
                                t_char*    alpha_name,
                                t_byte     let_width,
                                t_byte     let_height )
{
  tex->load( tex_name, alpha_name, false );

  /* ............................................................................ */

  id         = fnt_id;
  tex_inst   = tex->last;
  let_size.x = let_width;
  let_size.y = let_height;

  /* ............................................................................ */

  t_ulong   i;
  t_ulong   let_index;
  t_ulong   pix_index;
  t_ulong   data_size     = tex_inst->width * tex_inst->height * 3;
  t_short   let_in_row    = tex_inst->width / let_width;
  t_short   let_in_column = tex_inst->height / let_height;
  s_coord2s pix_c;
  s_coord2s let_c;
  s_coord2s pix_in_let_c;

  /* ............................................................................ */

  pix_c.x = 0;
  pix_c.y = 0;
  let_c.x = 0;
  let_c.y = 0;

  /* ............................................................................ */

  for( i = 0; i < data_size; i += 3 )
  {
    if( pix_c.x == tex_inst->width )
    {
      pix_c.x = 0;
      pix_c.y++;
    }

    /* .......................................................................... */

    let_c.x        = pix_c.x / let_width;
    let_c.y        = pix_c.y / let_height;
    pix_in_let_c.x = pix_c.x - let_c.x * let_width;
    pix_in_let_c.y = pix_c.y - let_c.y * let_height;
    pix_index      = pix_c.y * tex_inst->width + pix_c.x;
    let_index      = ( let_in_column - let_c.y - 1 ) * let_in_row + let_c.x;

    /* .......................................................................... */

    if( ( pix_in_let_c.x == 0 ) && ( pix_in_let_c.y == 0 ) )
    {
      let[let_index].sx     = pix_c.x;
      let[let_index].sy     = pix_c.y;
      let[let_index].width  = 0;
      let[let_index].height = 0;
    }

    /* .......................................................................... */

    if( tex_inst->alpha_buf[pix_index * 3] != 0 )
    {
      if( let[let_index].width < ( pix_in_let_c.x + 1 ) )  let[let_index].width = pix_in_let_c.x + 1;
      if( let[let_index].height < ( pix_in_let_c.y + 1 ) ) let[let_index].height = pix_in_let_c.y + 1;
    }

    /* .......................................................................... */

    pix_c.x++;
  }

  /* ............................................................................ */

  for( i = 0; i < FNT_LET_MAX_COUNT; i++ )
  {
    let[i].sx /= tex_inst->width;
    let[i].sy /= tex_inst->height;
    let[i].ex = let[i].sx + let[i].width / ( t_float )tex_inst->width;
    let[i].ey = let[i].sy + let[i].height / ( t_float )tex_inst->height;
  }

  /* ............................................................................ */

  first_list_id  = ogl_list_count;
  ogl_list_count += FNT_LET_MAX_COUNT;

  for( i = 0; i < FNT_LET_MAX_COUNT; i++ )
  {
    glNewList( first_list_id + i, GL_COMPILE );

      /* ........................................................................ */

      glBegin( GL_QUADS );

        /* ...................................................................... */

        glTexCoord2f( let[i].sx, let[i].sy );
        glVertex2i( 0, 0 );

        glTexCoord2f( let[i].sx, let[i].ey );
        glVertex2i( 0, let[i].height );

        glTexCoord2f( let[i].ex, let[i].ey );
        glVertex2i( let[i].width, let[i].height );

        glTexCoord2f( let[i].ex, let[i].sy );
        glVertex2i( let[i].width, 0 );

        /* ...................................................................... */

      glEnd( );

      /* ........................................................................ */

    glEndList( );
  }

  /* ............................................................................ */

  tex->kill_last_buf( );
}

/* ------------------------------------------------------------------------------ */
/*   draw                                                                         */

void c_app_fnt_inst::draw( t_long  index,
                           t_float x,
                           t_float y,
                           t_float scale_x,
                           t_float scale_y )
{
  glPushMatrix( );

    glTranslatef( x, y, 0.0 );
    glScalef( scale_x, scale_y, 0.0 );
    tex_inst->select( );
    glCallList( index + first_list_id );

  glPopMatrix( );
}

/* ------------------------------------------------------------------------------ */
/*   str_out                                                                      */

void c_app_fnt_inst::str_out( t_char* str,
                              t_float x,
                              t_float y,
                              t_float scale_x,
                              t_float scale_y )
{
  t_short str_len = strlen( str );
  t_short offset  = 0;
  t_short i;
  t_short let_id;

  for( i = 0; i < str_len; i++ )
  {
    let_id = str[i];

    if( let_id == -88 ) let_id = 160;
    else
    if( let_id == -72 ) let_id = 161;
    else
    if( let_id > 0 ) let_id -= 32;
    else             let_id += 160;

    draw( let_id, x + offset, y, scale_x, scale_y );

    offset += ( t_short )( let[let_id].width * scale_x ) + ( t_short )scale_x;
  }
}