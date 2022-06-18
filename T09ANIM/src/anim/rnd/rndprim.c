/* FILE NAME   : rndprim.c
 * PROGRAMMER  : PP6
 * LAST UPDATE : 17.06.2022
 * PURPOSE     : 3D animation project.
 *               Primitive module.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "rnd.h"


VOID PP6_RndPrimCreate( pp6PRIM *Pr, pp6PRIM_TYPE Type, pp6VERTEX *V, INT NoofV, INT *I, INT NoofI )
{
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(pp6PRIM));

  glGenBuffers(1, &Pr->VBuf);
  glGenVertexArrays(1, &Pr->VA);

  glBindVertexArray(Pr->VA);

  glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);

  glBufferData(GL_ARRAY_BUFFER, sizeof(pp6VERTEX) * NoofV, V, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(pp6VERTEX),
                        (VOID *)0); 
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(pp6VERTEX),
                        (VOID *)sizeof(VEC)); 
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(pp6VERTEX),
                        (VOID *)(sizeof(VEC) + sizeof(VEC2))); 
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(pp6VERTEX),
                        (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); 

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glBindVertexArray(0);

  glGenBuffers(1, &Pr->IBuf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);

  /*Store data sizes*/
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  /*Set default transform (identity)*/
  Pr->Type = Type;
  Pr->Trans = MatrIdentity();
  Pr->Trans = MatrScale(VecSet(0.1, 0.1, 0.1));
} /* End of 'PP6_RndPrimCreate' function */

VOID PP6_RndPrimFree( pp6PRIM *Pr )
{
  glBindVertexArray(Pr->VA);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);

  glDeleteBuffers(1, &Pr->IBuf);

  /* Set to 0 all primitive data */
  memset(Pr, 0, sizeof(pp6PRIM));
}

VOID PP6_RndPrimDraw( pp6PRIM *Pr, MATR World )
{
  MATR
    w = MatrMulMatr(Pr->Trans, World),
    winv = MatrTranspose(MatrInverse(w)),
    WVP = MatrMulMatr(w, PP6_RndMatrVP);
  INT loc;
  INT PP6_RndProgId;
  INT gl_prim_type = Pr->Type == PP6_RND_PRIM_TRIMESH ? GL_TRIANGLES :
                     Pr->Type == PP6_RND_PRIM_TRISTRIP ? GL_TRIANGLE_STRIP :
                     Pr->Type == PP6_RND_PRIM_LINES ? GL_LINES :
                     GL_POINTS;

  glLoadMatrixf(WVP.A[0]);

  PP6_RndProgId = PP6_RndMtlApply(Pr->MtlNo);

  if ((loc = glGetUniformLocation(PP6_RndProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, WVP.A[0]);
  if ((loc = glGetUniformLocation(PP6_RndProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, w.A[0]);
  if ((loc = glGetUniformLocation(PP6_RndProgId, "MatrWInv")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, winv.A[0]);
  if ((loc = glGetUniformLocation(PP6_RndProgId, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &PP6_RndCamLoc.X);
  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
  glDrawElements(gl_prim_type, Pr->NumOfI, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0);
  glUseProgram(0);
} /* End of 'PP6_RndPrimDraw' function */

BOOL PP6_RndPrimLoad( pp6PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT nv = 0, ni = 0, NoofV, NoofI, size;
  pp6VERTEX *V;
  VEC L = VecNormalize(VecSet(1, 1, 1));
  INT *I;
  INT i;
  FLT nl;
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
  NoofV = nv;
  NoofI = ni;
  size = sizeof(pp6VERTEX) * NoofV + sizeof(INT) * NoofI;
  if ((V = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  I = (INT *)(V + NoofV);
  memset(V, 0, size);

  /* Load primitive */
  rewind(F);
  nv = ni = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT i, n = 0, nc, n0, n1;

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
            I[ni++] = n0 - 1;
            I[ni++] = n1 - 1;
            I[ni++] = nc - 1;
            n1 = nc;
          }
          n++;
        }
    }
  fclose(F);
  PP6_RndTriMeshAutoNormals(V, nv, I, ni);
  for (i = 0; i < nv; i++)
  {
    V[i].N = VecNormalize(V[i].N);

    nl = VecDotVec(V[i].N, L);

    if (nl < 0.1)
      nl = 0.1;
    V[i].C = VecSet4(0.6 * nl, 0.1 * nl, 0.5 * nl, 1);
  }
  PP6_RndPrimCreate(Pr, PP6_RND_PRIM_TRIMESH, V, nv, I, ni);
  free(V);
  return TRUE;
} /* End of 'PP6_RndPrimLoad' function */

VOID PP6_RndTriMeshAutoNormals( pp6VERTEX *V, INT NumOfV, INT *I, INT NumOfI)
  {
    INT i;

    for (i = 0; i < NumOfV; i++)
      V[i].N = VecSet(0, 0, 0);
    for (i = 0; i < NumOfI; i += 3)
    {
      VEC
        p0 = V[I[i]].P,
        p1 = V[I[i + 1]].P,
        p2 = V[I[i + 2]].P,
        N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));

      V[I[i]].N = VecAddVec(V[I[i]].N, N);
      V[I[i + 1]].N = VecAddVec(V[I[i + 1]].N, N);
      V[I[i + 2]].N = VecAddVec(V[I[i + 2]].N, N);
    }
    for (i = 0; i < NumOfV; i++)
      V[i].N = VecNormalize(V[i].N);
  }

/*GRID*/
BOOL PP6_RndPrimCreateGrid( pp6PRIM *Pr, INT SplitW, INT SplitH, pp6VERTEX *V )
{
  INT *Ind;
  INT k, i, j, num_of_indices;


  memset(Pr, 0, sizeof(pp6PRIM));
  num_of_indices = (SplitH - 1) * (SplitW * 2 + 1) - 1;
  if ((Ind = malloc(sizeof(INT) * num_of_indices)) == NULL)
    return FALSE;

  /* Set indexes */
  for (k = 0, i = 0; i < SplitH - 1; i++)
  {
    for (j = 0; j < SplitW; j++)
    {
      Ind[k++] = (i + 1) * SplitW + j;
      Ind[k++] = (i + 0) * SplitW + j;
    }
    if (i != SplitH - 2)
      Ind[k++] = -1;
  }
  PP6_RndPrimCreate(Pr, PP6_RND_PRIM_TRISTRIP, V, SplitW * SplitH, Ind, num_of_indices);
  return TRUE;
}
VOID PP6_RndPrimGridEvalNormals( INT SplitW, INT SplitH, pp6VERTEX *V )
{
  INT i, j;

  for (i = 0; i < SplitW * SplitH; i++)
    V[i].N = VecSet(0, 0, 0);

  for (i = 0; i < SplitH - 1; i++)
    for (j = 0; j < SplitW - 1; j++)
    {
      pp6VERTEX
        *P00 = &V[i * SplitW + j],
        *P01 = &V[i * SplitW + j + 1],
        *P10 = &V[(i + 1) * SplitW + j],
        *P11 = &V[(i + 1) * SplitW + j + 1];
      VEC N;

      N = VecNormalize(VecCrossVec(VecSubVec(P00->P, P10->P),
                                   VecSubVec(P11->P, P10->P)));
      P00->N = VecAddVec(P00->N, N);
      P10->N = VecAddVec(P10->N, N);
      P11->N = VecAddVec(P11->N, N);

      N = VecNormalize(VecCrossVec(VecSubVec(P11->P, P01->P),
                                   VecSubVec(P00->P, P01->P)));
      P00->N = VecAddVec(P00->N, N);
      P01->N = VecAddVec(P01->N, N);
      P11->N = VecAddVec(P11->N, N);
  }
  for (i = 0; i < SplitW * SplitH; i++)
    V[i].N = VecNormalize(V[i].N);
}
