/* FILE NAME  : u_ctrl.c
 * PROGRAMMER : PP6
 * LAST UPDATE: 17.06.2022
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
  pp6PRIM Axes;
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
  FLT Dist, plen, sinT, cosT, sinP, cosP, Azimuth, Elevator, Hp, Wp, sx, sy;
  VEC dv;

   if (Ani->KeysClick['W'] && Ani->Keys[VK_SHIFT])
  {
    INT mode[2];

    glGetIntegerv(GL_POLYGON_MODE, mode);
    glPolygonMode(GL_FRONT_AND_BACK, mode[0] == GL_FILL ? GL_LINE : GL_FILL);
  }

  if (Ani->Keys[VK_CONTROL])
  {
    Dist = VecLen(VecSubVec(PP6_RndCamAt, PP6_RndCamLoc));
    cosT = (PP6_RndCamLoc.Y - PP6_RndCamAt.Y) / Dist;
    sinT = sqrt(1 - cosT * cosT);
    plen = Dist * sinT;

    cosP = (PP6_RndCamLoc.Z - PP6_RndCamAt.Z) / plen;
    sinP = (PP6_RndCamLoc.X - PP6_RndCamAt.X) / plen;

    Azimuth = R2D(atan2(sinP, cosP));
    Elevator = R2D(atan2(sinT, cosT));

    Azimuth += Ani->GlobalDeltaTime *
      (-20 * Ani->Keys[VK_LBUTTON] * Ani->Mdx + 
       30 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]));
    Elevator += Ani->GlobalDeltaTime *
      (-20 * Ani->Keys[VK_LBUTTON] * Ani->Mdy + 
       30 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));

    Dist += Ani->GlobalDeltaTime *
      (2.0 * 1.0 * Ani->Mdz + 
       (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));
    if (Dist < 0.1)
      Dist = 0.1;
   if (Elevator < 0.1)
     Elevator = 0.1;
   else if (Elevator > 179)
     Elevator = 179;

    Wp = PP6_RndProjSize;
    Hp = PP6_RndProjSize;

    if (Ani->W > Ani->H)
      Wp *= (FLT)Ani->W / Ani->H;
    else
      Hp *= (FLT)Ani->H / Ani->W;
    sx = Ani->Keys[VK_RBUTTON] * -Ani->Mdx * Wp / Ani->W * Dist / PP6_RndProjDist;
    sy = Ani->Keys[VK_RBUTTON] * Ani->Mdy * Hp / Ani->H * Dist / PP6_RndProjDist;

    dv = VecAddVec(VecMulNum(PP6_RndCamRight, sx),
                   VecMulNum(PP6_RndCamUp, sy));
    PP6_RndCamAt = VecAddVec(PP6_RndCamAt, dv);
    PP6_RndCamLoc = VecAddVec(PP6_RndCamLoc, dv);

    PP6_RndCamSet(PointTransform(VecSet(0, Dist, 0),
                                 MatrMulMatr(MatrRotateX(Elevator),
                                 MatrMulMatr(MatrRotateY(Azimuth),
                                             MatrTranslate(PP6_RndCamAt)))),
                  PP6_RndCamAt,
                  VecSet(0, 1, 0));
  }
} /* End of 'PP6_UnitResponse' function */

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
  MATR save;
  static CHAR Buf[102];

  sprintf(Buf, "FPS: %.3f", Ani->FPS);
  SetWindowText(Ani->hWnd, Buf);

  glLineWidth(3);
  PP6_RndPrimDraw(&Uni->Axes, MatrIdentity());
  glLineWidth(1);

  save = PP6_RndMatrVP;
  PP6_RndMatrVP = MatrOrtho(0, Ani->W, -Ani->H, 0, -1, 1);
  PP6_RndFntDraw(Buf, VecSet(0, 0, 0), 32);
  PP6_RndMatrVP = save;
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
