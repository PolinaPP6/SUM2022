/* FILE NAME  : u_g3dm.c
 * PROGRAMMER : PP6
 * LAST UPDATE: 18.06.2022
 * PURPOSE    : 3D animation project.
 *              .
 */
#include "Units/units.h"
#include "anim/anim.h"

typedef struct
{
  UNIT_BASE_FIELDS;
  VEC Pos1, Pos2;
  pp6PRIMS g3dm1;
  pp6PRIMS g3dm2;
} pp6UNIT_G3DM;


/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pp6UNIT *Uni;
 *   - animation context:
 *       pp6ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitInit( pp6UNIT_G3DM *Uni, pp6ANIM *Ani )
{
  Uni->Pos1 = VecSet(0, -69, 10);
  Uni->Pos2 = VecSet(0, -100, 0);
  PP6_RndPrimsLoad(&Uni->g3dm1, "bin/models/elephant.g3dm");
  PP6_RndPrimsLoad(&Uni->g3dm2, "bin/models/TORTOISE.g3dm");
} /* End of 'PP6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pp6UNIT *Uni;
 *   - animation context:
 *       pp6ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitClose( pp6UNIT_G3DM *Uni, pp6ANIM *Ani )
{
  PP6_RndPrimsFree(&Uni->g3dm1);
  PP6_RndPrimsFree(&Uni->g3dm2);
 /* PP6_RndPrimFree(&Uni->Ground);*/
} /* End of 'PP6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pp6UNIT *Uni;
 *   - animation context:
 *       pp6ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitResponse( pp6UNIT_G3DM *Uni, pp6ANIM *Ani )
{
} /* End of '_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pp6UNIT *Uni;
 *   - animation context:
 *       pp6ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitRender( pp6UNIT_G3DM *Uni, pp6ANIM *Ani )
{
  PP6_RndPrimsDraw(&Uni->g3dm1, MatrTranslate(Uni->Pos1));
  PP6_RndPrimsDraw(&Uni->g3dm2, MatrTranslate(Uni->Pos2));
} /* End of 'PP6_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (pp6UNIT *) pointer to created unit.
 */
pp6UNIT * PP6_UnitCreateg3dm( VOID )
{
  pp6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = PP6_AnimUnitCreate(sizeof(pp6UNIT_G3DM)))== NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)PP6_UnitInit;
  Uni->Close = (VOID *)PP6_UnitClose;
  Uni->Response = (VOID *)PP6_UnitResponse;
  Uni->Render = (VOID *)PP6_UnitRender;

  return Uni;
} /* End of 'PP6_AnimUnitCreate' function */