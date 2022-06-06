/* T04PERM.C
 * Programmer: PP6
 * DATE: 04.06.2022
 * PURPOSE: 
 */
#include <stdio.h>
#include<windows.h>

#define MAX 10
INT P[MAX];
BOOL IsParity, save_parity;

VOID Store( VOID )
{
  FILE *F;
  INT i;
 
  F = fopen("PERM.TXT", "a");
  if (F == NULL)
    return;
  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d,", P[i]);
  fprintf(F, "%d – parity: %s\n", P[MAX - 1], IsParity ? "even" : "odd");
 
  fclose(F);
} /* End of 'Store' function */

VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

    *A = *B;
    *B = tmp;
}

VOID Go( INT Pos )
{
  INT i, x;

  if (Pos == MAX)
    Store();
  else
  {
      save_parity = IsParity;
      Go(Pos + 1);
      for (i = Pos + 1; i < MAX; i++)
    {
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
      Go(Pos + 1);
    }
      x = P[Pos];
      for (i = Pos + 1; i < MAX; i++)
        P[i - 1] =P[i];
      P[MAX - 1] = x;
      IsParity = save_parity;

  }
}
VOID main( VOID )
{
  INT i;

  for(i = 0; i < MAX; i++)
    P[i] = i + 1;
    Go(0);

getchar();
getchar();
}