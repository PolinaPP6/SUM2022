/* T06DETG.C
 * Programmer: PP6
 * DATE: 04.06.2022
 * PURPOSE: finding det
 */
#include <stdio.h>
#include <windows.h>
#include <math.h>

typedef DOUBLE DBL;

#define MAX 10

DBL A[MAX][MAX], det;

INT N;

INT P[MAX];

BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;
 
  N = 0;
  if ((F = fopen("DETG.TXT", "r")) == NULL)
    return FALSE;
  fscanf(F, "%d", &N);
  if (N > MAX)
    N = MAX;
  else
    if (N < 0)
      N = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
} /* End of 'LoadMatrix' function */

/* Swap function */
VOID Swap( DBL *A, DBL *B )
{
  DBL tmp = *A;

    *A = *B;
    *B = tmp;
}/* End of 'Swap' function */

DBL Gauss( VOID )
{
  INT i, max_col, max_row, x, y, k = 0;
  DBL coef;

  det = 1;
  for (i = 0; i < N; i++)
  {
    /* look for maximum matrix element */
    max_row = max_col = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
          max_row = y, max_col = x;
    if (A[max_row][max_col] == 0)
    {
      det = 0;
      break;
    }
    if (max_row != i)
    {
      /* Swap max_row and i row (elements/columns: [i..N-1]) */
      for (x = i; x < N; x++)
        Swap(&A[max_row][x], &A[i][x]);
      det = -det;
    }
 
    if (max_col != i)
    {
      /* Swap max_col and i column (elements/columns: [0..N-1]) */
      for (x = 0; x < N; x++)
        Swap(&A[max_col][x], &A[i][x]);
      det = -det;
    }
      /* Subtrack from every row k:[i+1..N-1] row [i] multipled by (A[k][i] / A[i][i]) */
    for (k = i + 1; k < N; k++)
    {
      coef = A[k][i] / A[i][i];
      A[k][i] = 0;
      for (x = i + 1; x < N; x++)
         A[k][x] -= A[i][x] * coef;
    }
   det *= A[i][i];
  }
  return det;
}

VOID main( VOID )
{
  INT i;

  if (LoadMatrix("DETG.TXT"))
  {
     for (i = 0; i < N; i++)
       P[i] = i;
     printf("%lf", Gauss());
  }
  else
    printf("error");
  getchar();
  getchar();
}