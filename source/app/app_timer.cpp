/* ------------------------------------------------------------------------------ */
/*    prg  : ogl                                                                  */
/*    path : .\source\app\app_timer.cpp                                           */
/*    dev  : Alexander 'manny' Fomin                                              */
/*    date : 23.10.2004                                                           */   
/* ------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------ */

#include "app\app_timer.h"

/* ------------------------------------------------------------------------------ */

c_app_timer* g_timer;

/* ------------------------------------------------------------------------------ */
/*   c_app_timer                                                                  */

c_app_timer::c_app_timer( )
{
  fps          = 0;
  frame_count  = 0;

  current_tick = 0;
  prev_tick    = 0;
  first_tick   = GetTickCount( );
  
  current_sec  = 0;
  prev_sec     = 0;
  frame_len    = 0;
}

/* ------------------------------------------------------------------------------ */
/*   process                                                                      */

void c_app_timer::process( )
{
  frame_count++;

  prev_tick    = current_tick;
  current_tick = GetTickCount( ) - first_tick;

  frame_len = current_tick - prev_tick;

  current_sec = current_tick / CLOCKS_PER_SEC;

  if( ( current_sec - 1 ) > prev_sec )
  {
    prev_sec = prev_tick / CLOCKS_PER_SEC;

    fps         = frame_count;
    frame_count = 0;
  }
}