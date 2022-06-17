/* FILE NAME  : u_ctrl.c
 * PROGRAMMER : PP6
 * LAST UPDATE: 10.06.2022
 * PURPOSE    : 3D animation project.
 *              .
 */
#include <stdio.h>
#include "Units/units.h"
#include "anim/anim.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm")
typedef struct
{
  UNIT_BASE_FIELDS;
  VEC CamLoc, CamDir;
  DBL speed, AngleSpeed;
}pp6UNIT_CONTROL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       pp6ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitInit( pp6UNIT_CONTROL *Uni, pp6ANIM *Ani )
{
  Uni->CamLoc = VecSet(0, 1, 50);
  Uni->speed = 0.1;
  Uni->CamDir = VecNormalize(VecSet(-1, -1, -1));
  Uni->AngleSpeed = 0.1;
}/* End of 'VG4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitClose( pp6UNIT_CONTROL *Uni, pp6ANIM *Ani )
{
} /* End of 'VG4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitResponse( pp6UNIT_CONTROL *Uni, pp6ANIM *Ani )
{
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  /*Keys*/
  Uni->CamLoc = 
    VecAddVec(Uni->CamLoc,
     VecMulNum(Uni->CamDir, Ani->DeltaTime * Uni->speed *
      (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));
  /*WheelMouse*/
  Uni->CamLoc =
    PointTransform(Uni->CamLoc,
      MatrRotateY(Ani->Keys[VK_LBUTTON] *
        Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdx));
  PP6_RndCamSet(Uni->CamLoc, VecSet(0, 0, 0), VecSet(0, 1, 0));

} /* End of 'VG4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitRender( pp6UNIT_CONTROL *Uni, pp6ANIM *Ani )
{
  static CHAR Buf[102];
  SetTextColor(Ani->hDC, RGB(0, 0, 0));
  SetBkMode(Ani->hDC, TRANSPARENT);
  TextOut(Ani->hDC, 10, 10, Buf, sprintf(Buf, "FPS; %0.3f, %f, %f", Ani->FPS, Ani->Mx, Ani->My));
} /* End of 'VG4_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
pp6UNIT * PP6_UnitCreateControl( VOID )
{
  pp6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = PP6_AnimUnitCreate(sizeof(pp6UNIT_CONTROL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)PP6_UnitInit;
  Uni->Close = (VOID *)PP6_UnitClose;
  Uni->Response = (VOID *)PP6_UnitResponse;
  Uni->Render = (VOID *)PP6_UnitRender;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */
