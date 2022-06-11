/* FILE NAME  : u_ctrl.c
 * PROGRAMMER : PP6
 * LAST UPDATE: 10.06.2022
 * PURPOSE    : 3D animation project.
 *              .
 */
#include "Units/units.h"
#include "anim/anim.h"

/*typedef struct
{
  UNIT_BASE_FIELDS;

}pp6UNIT_CONTROL*/

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       pp6ANIM *Ani;
 * RETURNS: None.
 */
/*static VOID PP6_UnitInit( pp6UNIT_CONTROL *Uni, pp6ANIM *Ani )
{
}/* End of 'VG4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
/*static VOID PP6_UnitClose( pp6UNIT_CONTROL *Uni, pp6ANIM *Ani )
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
/*static VOID PP6_UnitResponse( pp6UNIT_CONTROL *Uni, pp6ANIM *Ani )
/*{
  Uni->CamLoc =
    PointTransform(Uni->CamLoc,
      MatrRotateY(Ani->DeltaTime * Uni->AngleSpeed * Ani->Mdx));
  if ((GetSyncKeyState('P') & 0 x 8000) != 0)
    Ani->Isause = True;
} /* End of 'VG4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
/*static VOID PP6_UnitRender( pp6UNIT_CONTROL *Uni, pp6ANIM *Ani )
/*{
} /* End of 'VG4_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
/*pp6UNIT * PP6_AnimUnitCreate( INT Size )
{
  pp6UNIT *Uni;

  /* Memory allocation */
  /*if (Size < sizeof(pp6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
 /* Uni->Init = PP6_UnitInit;
  Uni->Close = PP6_UnitClose;
  Uni->Response = PP6_UnitResponse;
  Uni->Render = PP6_UnitRender;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */
