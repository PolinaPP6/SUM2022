//* Pavlova Polina *//
#include <stdio.h>
#include <windows.h>

void main( void )
{
  int x;
  char Buf[100];

  scanf("%i", &x);
  sprintf(Buf, "Hi! x = %i", x);
  MessageBox(NULL, Buf, "Caption", MB_YESNO | MB_DEFBUTTON2);
}