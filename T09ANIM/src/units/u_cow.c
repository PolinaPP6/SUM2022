/* FILE NAME  : u_cow.c
 * PROGRAMMER : PP6
 * LAST UPDATE: 11.06.2022
 * PURPOSE    : 3D animation project.
 *              .
 */
#include "Units/units.h"
#include "anim/anim.h"

typedef struct
{
  UNIT_BASE_FIELDS;
  VEC Pos;
  pp6PRIM Cow;
  pp6PRIM Ground;
} pp6UNIT_COW;


/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       pp6ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitInit( pp6UNIT_COW *Uni, pp6ANIM *Ani )
{
      /* pp6VERTEX V[] =
    {
      {{0, 0, 0}, {0, 0}, {0, 1, 0}, {1, 0, 1, 1}},
      {{1, 0, 0}, {0, 0}, {0, 1, 0}, {1, 0, 0, 1}},
      {{0, 0, -1}, {0, 0}, {0, 1, 0}, {0, 0, 1, 1}},
      {{1, 0, -1}, {0, 0}, {0, 1, 0}, {1, 1, 0, 1}},
    };
  INT I[] = {0, 1, 2, 2, 1, 3};

  PP6_RndPrimCreate(&Uni->Ground, PP6_RND_PRIM_TRIMESH, V, 4, I, 6);*/
  Uni->Pos = VecSet(0, 0, 0);
  PP6_RndPrimLoad(&Uni->Cow, "bin/models/cow.obj");
} /* End of 'VG4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitClose( pp6UNIT_COW *Uni, pp6ANIM *Ani )
{
  PP6_RndPrimFree(&Uni->Cow);
 /* PP6_RndPrimFree(&Uni->Ground);*/
} /* End of 'VG4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitResponse( pp6UNIT_COW *Uni, pp6ANIM *Ani )
{
  ///Uni->Pos.X = 0.5 * sin(Ani->Time);
} /* End of '_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       pp6ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitRender( pp6UNIT_COW *Uni, pp6ANIM *Ani )
{
 /* INT i, j;
  for (i = 0; i <= 100; i++)
    for (j = 0; j <= 100; j++)
      PP6_RndPrimDraw(&Uni->Ground, MatrTranslate(VecSet(j, 0, i))); */
  PP6_RndPrimDraw(&Uni->Cow, MatrTranslate(Uni->Pos));
} /* End of 'PP6_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (pp6UNIT *) pointer to created unit.
 */
pp6UNIT * PP6_UnitCreateCow( VOID )
{
  pp6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = PP6_AnimUnitCreate(sizeof(pp6UNIT_COW)))== NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)PP6_UnitInit;
  Uni->Close = (VOID *)PP6_UnitClose;
  Uni->Response = (VOID *)PP6_UnitResponse;
  Uni->Render = (VOID *)PP6_UnitRender;

  return Uni;
} /* End of 'PP6_AnimUnitCreate' function */


