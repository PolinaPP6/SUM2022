/* FILE NAME  : rndfnt.c
 * PROGRAMMER : PP6
 * LAST UPDATE: 18.06.2022
 * PURPOSE    : 3D animation project.
 *              .
 */
#include <string.h>
#include <stdio.h>

#include "pp6.h"

/* Font data */
static pp6FONT PP6_RndFntFont;

/* Font characters primitives */
static pp6PRIM PP6_RndFntChars[256];

/* Font material */
static INT PP6_RndFntMtlNo;

/* Load font from .G3DF file function.
 * ARGUMENTS:
 *   - font file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL PP6_RndFntLoad( CHAR *FileName )
{
  FILE *F;
  DWORD Sign, W, H;
  pp6VERTEX Chars[256][4];
  DWORD *tex;
  pp6MATERIAL mtl;
  INT i;

  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DF")
  {
    fclose(F);
    return FALSE;
  }
  fread(&PP6_RndFntFont, sizeof(pp6FONT), 1, F);
  fread(Chars, sizeof(pp6VERTEX) * 4, 256, F);
  fread(&W, 4, 1, F);
  fread(&H, 4, 1, F);
  if ((tex = malloc(W * H * 4)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  fread(tex, 4, W * H, F);
  fclose(F);

  mtl = PP6_RndMtlGetDef();
  strncpy(mtl.Name, FileName, PP6_STR_MAX - 1);
  mtl.Tex[0] = PP6_RndTexAddImg(FileName, W, H, 4, tex);
  free(tex);
  mtl.ShdNo = PP6_RndShdAdd("font");
  PP6_RndFntMtlNo = PP6_RndMtlAdd(&mtl);

  for (i = 0; i < 256; i++)
  {
    PP6_RndPrimFree(&PP6_RndFntChars[i]);
    PP6_RndPrimCreate(&PP6_RndFntChars[i], PP6_RND_PRIM_TRISTRIP, Chars[i], 4, NULL, 0);
    PP6_RndFntChars[i].MtlNo = PP6_RndFntMtlNo;
  }

  return TRUE;
} /* End of 'PP6_RndFntLoad' function */

/* Init font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndFntInit( VOID )
{
  PP6_RndFntLoad("bin/fonts/arial.g3df");
} /* End of 'PP6_RndFntInit' function */

/* Deinit font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndFntClose( CHAR *FileName )
{
  INT i;

  for (i = 0; i < 256; i++)
    PP6_RndPrimFree(&PP6_RndFntChars[i]);
  memset(PP6_RndFntChars, 0, sizeof(PP6_RndFntChars));
} /* End of 'PP6_RndFntClose' function */

/* Draw string function.
 * ARGUMENTS:
 *   - string to draw:
 *       CHAR *Str;
 *   - draw position:
 *       VEC Pos;
 *   = font size:
 *      FLT Size;
 * RETURNS: None.
 */
VOID PP6_RndFntDraw( CHAR *Str, VEC Pos, FLT Size )
{
  VEC p = Pos;

  while (*Str != 0)
  {
    if (*Str == '\n')
      Pos.X = p.X, Pos.Y -= Size;
    else
      if (PP6_RndFntFont.AdvanceX[(UCHAR)*Str] != 0)
      {
        PP6_RndPrimDraw(&PP6_RndFntChars[(UCHAR)*Str],
          MatrMulMatr(MatrScale(VecSet(Size, Size, 1)), MatrTranslate(Pos)));
        Pos.X += PP6_RndFntFont.AdvanceX[(UCHAR)*Str] * Size;
      }
    Str++;
  }
} /* End of 'PP6_RndFntDraw' function */


