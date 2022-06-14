/* FILE NAME  : units.h
 * PROGRAMMER : PP6
 * LAST UPDATE: 11.06.2022
 * PURPOSE    : 3D animation project.
 *              .
 */
#include "anim/anim.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm")
#include <string.h>

INT PP6_MouseWheel;

/*Keys*/
static BYTE KeysOld[256];

static VOID PP6_AnimKeyboardInit( VOID )
{
  INT i;

  GetKeyboardState(PP6_Anim.Keys);
  memcpy(KeysOld, PP6_Anim.Keys, 256);
  for (i = 0; i < 256; i++)
    PP6_Anim.KeysClick[i] = 0;
}

static VOID PP6_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(PP6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    PP6_Anim.Keys[i] >>= 7;
    PP6_Anim.KeysClick[i] = PP6_Anim.Keys[i] && !KeysOld[i];
  }
  memcpy(KeysOld, PP6_Anim.Keys, 256);
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
