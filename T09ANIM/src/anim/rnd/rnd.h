/* FILE NAME   : rnd.h
 * PROGRAMMER  : PP6
 * LAST UPDATE : 09.06.2022
 * PURPOSE     : 3D animation project.
 *               Startup module.
 */
#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include <glew.h>

#include "def.h"
#include "pp6.h"
#include "res/rndres.h"

extern HWND PP6_hRndWnd;                 /* Work window handle */
extern HDC PP6_hRndDC;              /* Work window memory device context  */
extern INT PP6_RndFrameW, PP6_RndFrameH; /* Work window size */
extern HGLRC PP6_hRndGLRC;               /* Work OpenGL rendering context */

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
  VEC P;   /* Vertex position */
  VEC2 T;  /* tecsture  */
  VEC N;   /* normal */
  VEC4 C;  /* color (r,g,b,a) */
} pp6VERTEX;

typedef enum tagpp6PRIM_TYPE
{
  PP6_RND_PRIM_TRIMESH,
  PP6_RND_PRIM_GRID
}pp6PRIM_TYPE;



typedef struct tagpp6PRIM
{
  pp6PRIM_TYPE Type;
  INT
   VA,
   VBuf,
   IBuf,
   NumOfV,   /* Number of vertices */
   NumOfI,
   NumOfElements;   /* Number of idices */
  MATR Trans;
  VEC MinBB, MaxBB;/* Additional transformation matrix */
} pp6PRIM;

/**/
VEC4 Vec4Set( FLT A, FLT B, FLT C, FLT D );
VEC4 Vec4Set1( FLT A );
VEC2 Vec2Set( FLT A, FLT B );
VEC2 Vec2Set1( FLT A );

VOID PP6_RndInit( HWND hWnd );
VOID PP6_RndClose( VOID );
VOID PP6_RndResize( INT W, INT H );
VOID PP6_RndCopyFrame( VOID );
VOID PP6_RndStart( VOID );
VOID PP6_RndEnd( VOID );
VOID PP6_RndProjSet( VOID );
VOID PP6_RndCamSet( VEC Loc, VEC At, VEC Up );
VOID PP6_RndPrimCreate( pp6PRIM *Pr, pp6VERTEX *V, INT NoofV, INT *I, INT NoofI );
VOID PP6_RndPrimFree( pp6PRIM *Pr );
VOID PP6_RndPrimDraw( pp6PRIM *Pr, MATR World );
BOOL PP6_RndPrimLoad( pp6PRIM *Pr, CHAR *FileName);
VOID PP6_RndTriMeshEvalNormals( pp6VERTEX *V, INT NumOfV, INT *I, INT NumOfI);
#endif /* __rnd_h_ */