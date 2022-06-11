/* FILE NAME  : units.h
 * PROGRAMMER : PP6
 * LAST UPDATE: 11.06.2022
 * PURPOSE    : 3D animation project.
 *              .
 */
#include "anim/anim.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm")

INT PP6_MouseWheel;

BYTE Keys[256];
BYTE KeysClick[256];
BYTE KeysOld[256];

static VOID PP6_AnimKeyboardInit( VOID )
{
  GetKeyboardState(Keys);
  {
    INT i;
    for (i = 0; i < 256; i++)
    {
      Keys[i] >>= 7;
      KeysClick[i] = Keys[i] && !KeysOld[i];
    }
  memcpy(KeysOld, Keys, 256);
  }
}

static VOID PP6_AnimKeyboardResponse( VOID )
{
}

static VOID PP6_AnimMouseInit( VOID )
{
}

static VOID PP6_AnimMouseResponse( VOID )
{
}

static VOID PP6_AnimJoystickInit( VOID )
{
 
}

static VOID PP6_AnimJoystickResponse( VOID )
{
}

VOID PP6_AnimInputInit( VOID )
{
 PP6_AnimKeyboardInit();
 PP6_AnimMouseInit();
 PP6_AnimJoystickInit();
}

VOID PP6_AnimInputResponse( VOID )
{
 PP6_AnimKeyboardResponse();
 PP6_AnimMouseResponse();
 PP6_AnimJoystickResponse();
}
