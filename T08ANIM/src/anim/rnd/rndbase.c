/* FILE NAME   : rndbase.c
 * PROGRAMMER  : PP6
 * LAST UPDATE : 09.06.2022
 * PURPOSE     : 3D animation project.
 *               Startup module.
 */
#include "rnd.h"

VOID PP6_RndInit( HWND hWnd )
{
  HDC hDC;

  PP6_hRndWnd = hWnd;
  hDC = GetDC(hWnd);
  PP6_RndProjPoints = NULL;
  PP6_RndProjPointsSize = 0;
  PP6_hRndDCFrame = CreateCompatibleDC(hDC);
  PP6_hRndBmFrame = NULL;
  PP6_RndCamSet(VecSet(0, 1, 50), VecSet(0, 0, 1), VecSet(0, 1, 0));
  ReleaseDC(hWnd, hDC);
}

VOID PP6_RndClose( VOID )
{
  if (PP6_hRndBmFrame != NULL)
    DeleteObject(PP6_hRndBmFrame);
  DeleteDC(PP6_hRndDCFrame);
  if (PP6_RndProjPoints != NULL)
    free(PP6_RndProjPoints), PP6_RndProjPoints = NULL;
  PP6_RndProjPointsSize = 0;
}

VOID PP6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(PP6_hRndWnd);

  if (PP6_hRndBmFrame)
    DeleteObject(PP6_hRndBmFrame);
  PP6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(PP6_hRndWnd, hDC);	
  SelectObject(PP6_hRndDCFrame, PP6_hRndBmFrame);

  /* save size */
  PP6_RndFrameW = W;
  PP6_RndFrameH = H;

  /*  */
  PP6_RndProjSet();
}

VOID PP6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, PP6_RndFrameW, PP6_RndFrameH,
    PP6_hRndDCFrame, 0, 0, SRCCOPY);
}

VOID PP6_RndStart( VOID )
{
  SelectObject(PP6_hRndDCFrame, GetStockObject(DC_BRUSH));
  SelectObject(PP6_hRndDCFrame, GetStockObject(DC_PEN));
  SetDCBrushColor(PP6_hRndDCFrame, RGB(246, 223, 215));
  Rectangle(PP6_hRndDCFrame, 0, 0, PP6_RndFrameW, PP6_RndFrameH);
}

VOID PP6_RndEnd( VOID )
{
}

VOID PP6_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = PP6_RndProjSize;
  /* Correct aspect ratio */
  if (PP6_RndFrameW > PP6_RndFrameH)
    rx *= (DBL)PP6_RndFrameW / PP6_RndFrameH;
  else
    ry *= (DBL)PP6_RndFrameH / PP6_RndFrameW;

  PP6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      PP6_RndProjDist, PP6_RndProjFarClip);
  PP6_RndMatrVP = MatrMulMatr(PP6_RndMatrView, PP6_RndMatrProj);
}

VOID PP6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  PP6_RndMatrView = MatrView(Loc, At, Up);
  PP6_RndMatrVP = MatrMulMatr(PP6_RndMatrView, PP6_RndMatrProj);
}
