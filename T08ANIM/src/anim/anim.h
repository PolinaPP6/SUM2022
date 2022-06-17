/* FILE NAME  : anum.h
 * PROGRAMMER : PP6
 * LAST UPDATE: 10.06.2022
 * PURPOSE    : 3D animation project.
 *              Common declaration module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"
#define PP6_MAX_UNITS 3000

typedef struct tagpp6UNIT pp6UNIT;
typedef struct tagpp6ANIM
{
  HWND hWnd;                     
  HDC hDC;                       
  INT W, H;
  pp6UNIT *Units[PP6_MAX_UNITS];
  INT NumOfUnits;                
  DBL
  GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  Time, DeltaTime,             /* Time with pause and interframe interval */
  FPS;                         /* Frames per second value */
  BOOL
  IsPause;                     /* Pause flag */
  BYTE Keys[256];
  BYTE KeysClick[256];
  INT Mdx, Mdy, Mdz, Mx, My, Mz;
} pp6ANIM;

#define UNIT_BASE_FIELDS\
 VOID (*Init)( pp6UNIT *Uni, pp6ANIM *Ani );\
 VOID (*Close)( pp6UNIT *Uni, pp6ANIM *Ani );\
 VOID (*Response)( pp6UNIT *Uni, pp6ANIM *Ani );\
 VOID (*Render)( pp6UNIT *Uni, pp6ANIM *Ani )

struct tagpp6UNIT
{
  UNIT_BASE_FIELDS;
};

VOID PP6_AnimInit( HWND hWnd );
VOID PP6_AnimClose( VOID );
VOID PP6_AnimResize( INT W, INT H );
VOID PP6_AnimCopyFrame( HDC hDC );
VOID PP6_AnimRender( VOID );
VOID PP6_AnimAddUnit( pp6UNIT *Uni );
VOID PP6_AnimFlipFullScreen( VOID );
VOID PP6_AnimExit( VOID );
extern pp6ANIM PP6_Anim;

/*timer*/

VOID TimerInit( VOID );
VOID TimerResponse( VOID );

/*COW*/
pp6UNIT * PP6_UnitCreateCow( VOID );

/*CONTROL*/
pp6UNIT * PP6_UnitCreateControl( VOID );

/*Mouse Wheel*/
extern INT PP6_MouseWheel;

VOID PP6_AnimInputInit( VOID );
VOID PP6_AnimInputResponse( VOID );

#endif /* __anim_h_ */


