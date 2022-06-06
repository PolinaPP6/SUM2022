/* T05DET.C
 * Programmer: PP6
 * DATE: 04.06.2022
 * PURPOSE: square matrix determinant 
 */
#include <stdio.h>
#include <windows.h>

/* Helpful float point double precision type */
typedef DOUBLE DBL;
 
/* Array max size */
#define MAX 10
/* Source matrix */
DBL A[MAX][MAX], Det;
/* Source matrix size */
INT N;
 
/* Permutation table */
INT P[MAX];
/* Current permutation parity flag */ 
BOOL IsParity;
 
/* Load matrix function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
/* Load matrix function */
BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;
 
  N = 0;
  if ((F = fopen("DET.TXT", "r")) == NULL)
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
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

    *A = *B;
    *B = tmp;
}/* End of 'Swap' function */

/* count det */
VOID Go( INT Pos )
{
  INT i, x;
  DOUBLE prod;
  BOOL save_parity;

  if (Pos == N)
   {
      for (i = 0, prod = 1; i < N; i++)
        prod *= A[i][P[i]];
      Det += prod * (IsParity ? 1 : - 1);
   }
  else
  {
      save_parity = IsParity;
      Go(Pos + 1);
      for (i = Pos + 1; i < N; i++)
    {
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
      Go(Pos + 1);
    }
      x = P[Pos];
      for (i = Pos + 1; i < N; i++)
        P[i - 1] =P[i];
      P[N - 1] = x;
      IsParity = save_parity;
  }
} /* End of 'Go' function */

VOID main( VOID )
{
  INT i;

  if (LoadMatrix("DET.TXT"))
  {
     for (i = 0; i < N; i++)
       P[i] = i;
     Go(0);
     printf("%lf", Det);
  }
  else
    printf("error");
  getchar();
  getchar();
}/* End of 't05det.c' file */