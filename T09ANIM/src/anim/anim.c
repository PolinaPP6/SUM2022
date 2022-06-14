/* FILE NAME  : anum.h
 * PROGRAMMER : PP6
 * LAST UPDATE: 10.06.2022
 * PURPOSE    : 3D animation project.
 *              Common declaration module.
 */
#include "anim.h"
pp6ANIM PP6_Anim;

VOID PP6_AnimInit( HWND PP6_hRndWnd )
{
  PP6_Anim.hWnd = PP6_hRndWnd;
  PP6_RndInit(PP6_hRndWnd);


  TimerInit();
}

VOID PP6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < PP6_Anim.NumOfUnits; i++)
  {
    PP6_Anim.Units[i]->Close(PP6_Anim.Units[i], &PP6_Anim);
    free(PP6_Anim.Units[i]);
    PP6_Anim.Units[i] = NULL;
  }
  PP6_Anim.NumOfUnits = 0;
  PP6_RndClose();
}

VOID PP6_AnimResize( INT W, INT H )
{
  PP6_Anim.W = W;
  PP6_Anim.H = H;
  PP6_RndResize(PP6_Anim.W, PP6_Anim.H);
}

VOID PP6_AnimCopyFrame( VOID )
{
  PP6_RndCopyFrame();
}

VOID PP6_AnimRender( VOID )
{
  INT i;

  TimerResponse();

  for (i = 0; i < PP6_Anim.NumOfUnits; i++)
    PP6_Anim.Units[i]->Response(PP6_Anim.Units[i], &PP6_Anim);

  PP6_RndStart();
  for (i = 0; i < PP6_Anim.NumOfUnits; i++)
    PP6_Anim.Units[i]->Render(PP6_Anim.Units[i], &PP6_Anim);
  PP6_RndEnd();
}

VOID PP6_AnimAddUnit( pp6UNIT *Uni )
{
  if (PP6_Anim.NumOfUnits < PP6_MAX_UNITS)
    PP6_Anim.Units[PP6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &PP6_Anim);
}

VOID PP6_AnimFlipFullScreen( VOID )
{

}

VOID PP6_AnimExit( VOID )
{

}
