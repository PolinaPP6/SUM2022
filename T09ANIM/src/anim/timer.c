/* FILE NAME  : timer.c
 * PROGRAMMER : PP6
 * LAST UPDATE: 10.06.2022
 * PURPOSE    : 3D animation project.
 *              .
 */
#include "anim/anim.h"
#include <time.h>
/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */

static UINT64
StartTime,    /* Start program time */
OldTime,      /* Previous frame time */
OldTimeFPS,   /* Old time FPS measurement */
PauseTime,    /* Time during pause period */
TimePerSec,   /* Timer resolution */
FrameCounter; /* Frames counter */

VOID TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  PP6_Anim.IsPause = FALSE;
  PP6_Anim.FPS = 30.0;
  PauseTime = 0;
} /* End of 'GLB_TimerInit' function */

/* Response timer function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  PP6_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  PP6_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */ 
  if (PP6_Anim.IsPause)
  {
    PP6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    PP6_Anim.DeltaTime = PP6_Anim.GlobalDeltaTime;
    PP6_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    PP6_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;

} /* End of 'GLB_TimerResponse' function */
/*End of 'timer.c' FILE*/
