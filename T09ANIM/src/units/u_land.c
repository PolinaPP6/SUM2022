/* FILE NAME  : u_land.c
 * PROGRAMMER : PP6
 * LAST UPDATE: 17.06.2022
 * PURPOSE    : 3D animation project.
 *              .
 */
#include "Units/units.h"
#include "anim/anim.h"

typedef struct
{
  UNIT_BASE_FIELDS;
  pp6PRIM LandScape;
  VEC Pos;
} pp6UNIT_LAND;


/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       pp6ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitInit( pp6UNIT_LAND *Uni, pp6ANIM *Ani )
{
  HBITMAP hBm;
  BITMAP bm;
  pp6VERTEX *V;
  INT w, h;
  pp6MATERIAL mtl = PP6_RndMtlGetDef();

  if ((hBm = LoadImage(NULL, "bin/heights/hf.bmp", IMAGE_BITMAP, 0, 0,
                       LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    GetObject(hBm, sizeof(bm), &bm);
    w = bm.bmWidth;
    h = bm.bmHeight;
    if ((bm.bmBitsPixel == 8 || bm.bmBitsPixel == 24) &&
        (V = malloc(w * h * sizeof(pp6VERTEX))) != NULL)
    {
      BYTE *Bits = bm.bmBits;
      INT x, y;

      for (y = 0; y < h; y++)
        for (x = 0; x < w; x++)
        {
          INT hgt = Bits[(h - 1 - y) * bm.bmWidthBytes + x * (bm.bmBitsPixel / 8)];

          V[y * w + x].P = VecSet(x / (w - 1.0),
                                  hgt / 255.0,
                                  1 - y / (h - 1.0));
          V[y * w + x].T = Vec2Set(x / (w - 1.0), 1 - y / (h - 1.0));
        }
      strcpy(mtl.Name, "Landscape Material");
      PP6_RndPrimGridEvalNormals(w, h, V);
      PP6_RndPrimCreateGrid(&Uni->LandScape, w, h, V);
      mtl.Tex[0] = PP6_RndTexAddFromFile("bin/heights/hftex.bmp");
      Uni->LandScape.MtlNo = PP6_RndMtlAdd(&mtl);
      Uni->Pos = VecSet(0, 0, 0);
      Uni->LandScape.Trans = MatrMulMatr(MatrTranslate(VecSet(-0.5, 0, -0.5)), MatrScale(VecSet(100, 60, 100)));
      free(V);
    }
    DeleteObject(hBm);
  }
} /* End of 'PP6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitClose( pp6UNIT_LAND *Uni, pp6ANIM *Ani )
{
  PP6_RndPrimFree(&Uni->LandScape);
} /* End of 'VG4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitResponse( pp6UNIT_LAND *Uni, pp6ANIM *Ani )
{
  ///Uni->Pos.X = 0.5 * sin(Ani->Time);
} /* End of 'VG4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID PP6_UnitRender( pp6UNIT_LAND *Uni, pp6ANIM *Ani )
{
  PP6_RndPrimDraw(&Uni->LandScape, MatrTranslate(Uni->Pos));
} /* End of 'VG4_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
pp6UNIT * PP6_UnitCreateLand( VOID )
{
  pp6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = PP6_AnimUnitCreate(sizeof(pp6UNIT_LAND)))== NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)PP6_UnitInit;
  Uni->Close = (VOID *)PP6_UnitClose;
  Uni->Response = (VOID *)PP6_UnitResponse;
  Uni->Render = (VOID *)PP6_UnitRender;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */
