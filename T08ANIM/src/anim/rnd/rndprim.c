/* FILE NAME   : rndprim.c
 * PROGRAMMER  : PP6
 * LAST UPDATE : 09.06.2022
 * PURPOSE     : 3D animation project.
 *               Primitive module.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "rnd.h"


BOOL PP6_RndPrimCreate( pp6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(pp6PRIM));
  /* Calculate memory size for primiyive data */
  size = sizeof(pp6VERTEX) * NoofV + sizeof(INT) * NoofI;
  /* Allocate memory */
  Pr->V = malloc(size);
  if (Pr->V == NULL)
    return FALSE;
  /* Fill all allocated memory by 0 */
  memset(Pr->V, 0, size);
  /* Set index array pointer */
  Pr->I = (INT *)(Pr->V + NoofV);
  /*Store data sizes*/
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  /*Set default transform (identity)*/
  Pr->Trans = MatrIdentity();
  return TRUE;
}/* End of 'PP6_RndPrimCreate' function */

VOID PP6_RndPrimFree( pp6PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  /* Set to 0 all primitive data */
  memset(Pr, 0, sizeof(pp6PRIM));
}

VOID PP6_RndPrimDraw( pp6PRIM *Pr, MATR World )
{
  INT i;
  MATR M = MatrMulMatr(Pr->Trans, MatrMulMatr(World, PP6_RndMatrVP));

  if (PP6_RndProjPointsSize < Pr->NumOfV)
  {
    if (PP6_RndProjPoints != NULL)
      free(PP6_RndProjPoints);
    PP6_RndProjPointsSize = 0;
    /* Allocate memory for projections */
    if ((PP6_RndProjPoints = malloc(sizeof(POINT) * Pr->NumOfV)) == NULL)
      return;
    PP6_RndProjPointsSize = Pr->NumOfV;
  }
  /* Project all vertices */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    /* Convert from World to NDC */
    VEC p = VecMulMatr(Pr->V[i].P, M);

    /* Convert from World to NDC */
    PP6_RndProjPoints[i].x = (INT)((p.X + 1) * PP6_RndFrameW / 2);
    PP6_RndProjPoints[i].y = (INT)((-p.Y + 1) * PP6_RndFrameH / 2);
  }
  /* Draw all triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(PP6_hRndDCFrame, PP6_RndProjPoints[Pr->I[i]].x, PP6_RndProjPoints[Pr->I[i]].y, NULL);
    LineTo(PP6_hRndDCFrame, PP6_RndProjPoints[Pr->I[i + 1]].x, PP6_RndProjPoints[Pr->I[i + 1]].y);
    LineTo(PP6_hRndDCFrame, PP6_RndProjPoints[Pr->I[i + 2]].x, PP6_RndProjPoints[Pr->I[i + 2]].y);
    LineTo(PP6_hRndDCFrame, PP6_RndProjPoints[Pr->I[i]].x, PP6_RndProjPoints[Pr->I[i]].y);
  }
}/* End of 'PP6_RndPrimDraw' function */

BOOL PP6_RndPrimLoad( pp6PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT nv = 0, ni = 0;
  static CHAR Buf[1000];

  memset(Pr, 0, sizeof(pp6PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertexes and indexes */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, i;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
          n++;
      ni += (n - 2) * 3;
    }

  /* Create primitive */
  if (!PP6_RndPrimCreate(Pr, nv, ni))
  {
    fclose(F);
    return FALSE;
  }

  /* Load primitive */
  rewind(F);
  nv = ni = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, i, nc, n0, n1;
	
      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) &&!isspace((UCHAR)Buf[i]))
        {
          sscanf(Buf + i, "%d", &nc);
          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Pr->I[ni++] = n0 - 1;
            Pr->I[ni++] = n1 - 1;
            Pr->I[ni++] = nc - 1;
            n1 = nc;
          }
          n++;
        }
    }
  fclose(F);
  return TRUE;
} /* End of 'VG4_RndPrimLoad' function */