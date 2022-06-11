/* FILE NAME   : rnd.h
 * PROGRAMMER  : PP6
 * LAST UPDATE : 09.06.2022
 * PURPOSE     : 3D animation project.
 *               Startup module.
 */
#ifndef __rnd_h_
#define __rnd_h_

#include "def.h"

extern HWND PP6_hRndWnd;                 /* Work window handle */
extern HDC PP6_hRndDCFrame;              /* Work window memory device context  */
extern HBITMAP PP6_hRndBmFrame;          /* Work window background bitmap handle */
extern INT PP6_RndFrameW, PP6_RndFrameH; /* Work window size */
extern POINT *PP6_RndProjPoints;         /* Buffer for store projection points for primitive rendering */
extern INT PP6_RndProjPointsSize;        /* Projection storage buffer size */

extern DBL
  PP6_RndProjSize,     /* Project plane fit square */
  PP6_RndProjDist,     /* Distance to project plane from viewer (near) */
  PP6_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  PP6_RndMatrView, /* View coordinate system matrix */
  PP6_RndMatrProj, /* Projection coordinate system matrix */
  PP6_RndMatrVP;   /* Stored (View * Proj) matrix */

typedef struct tagpp6VERTEX
{
  VEC P;/* Vertex position */
}pp6VERTEX;
typedef struct tagpp6PRIM
{
  pp6VERTEX *V; /* Vertex attribytes array */
  INT NumOfV;   /* Number of vertices */
  INT *I;       /* Index array (for trimesh - by 3 ones) */
  INT NumOfI;   /* Number of idices */
  MATR Trans;   /* Additional transformation matrix */
}pp6PRIM;

VOID PP6_RndInit( HWND hWnd );
VOID PP6_RndClose( VOID );
VOID PP6_RndResize( INT W, INT H );
VOID PP6_RndCopyFrame( HDC hDC );
VOID PP6_RndStart( VOID );
VOID PP6_RndEnd( VOID );
VOID PP6_RndProjSet( VOID );
VOID PP6_RndCamSet( VEC Loc, VEC At, VEC Up );
BOOL PP6_RndPrimCreate( pp6PRIM *Pr, INT NoofV, INT NoofI );
VOID PP6_RndPrimFree( pp6PRIM *Pr );
VOID PP6_RndPrimDraw( pp6PRIM *Pr, MATR World );
BOOL PP6_RndPrimLoad( pp6PRIM *Pr, CHAR *FileName);
#endif /* __rnd_h_ */