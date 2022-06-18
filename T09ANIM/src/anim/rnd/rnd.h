/* FILE NAME   : rnd.h
 * PROGRAMMER  : PP6
 * LAST UPDATE : 18.06.2022
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

extern VEC
  PP6_RndCamLoc,
  PP6_RndCamDir,
  PP6_RndCamUp,
  PP6_RndCamRight,
  PP6_RndCamAt;

typedef struct tagpp6VERTEX
{
  VEC P;   /* Vertex position */
  VEC2 T;  /* tecsture  */
  VEC N;   /* normal */
  VEC4 C;  /* color (r,g,b,a) */
} pp6VERTEX;

typedef enum tagpp6PRIM_TYPE
{
  PP6_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles */
  PP6_RND_PRIM_TRISTRIP, /* Triangle strip - array of stripped triangles */
  PP6_RND_PRIM_LINES,    /* Line segments (by 2 points) */
  PP6_RND_PRIM_POINTS,   /* Arrauy of points */
}pp6PRIM_TYPE;



typedef struct tagpp6PRIM
{
  pp6PRIM_TYPE Type;
  INT
   VA,
   VBuf,
   IBuf,
   NumOfV,           /* Number of vertices */
   NumOfI,
   NumOfElements;    /* Number of idices */
  MATR Trans;
  VEC MinBB, MaxBB;  /* Additional transformation matrix */
  INT MtlNo;         /* Material number in material array */
} pp6PRIM;

/* Primitive collection data type */
typedef struct tagpp6PRIMS
{
  INT NumOfPrims; /* Number of primitives in array */  
  pp6PRIM *Prims; /* Array of primitives */
  MATR Trans;     /* Common transformation matrix */
} pp6PRIMS;

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
VOID PP6_RndPrimCreate( pp6PRIM *Pr, pp6PRIM_TYPE Type, pp6VERTEX *V, INT NoofV, INT *I, INT NoofI );
VOID PP6_RndPrimFree( pp6PRIM *Pr );
VOID PP6_RndPrimDraw( pp6PRIM *Pr, MATR World );
BOOL PP6_RndPrimLoad( pp6PRIM *Pr, CHAR *FileName);
VOID PP6_RndTriMeshAutoNormals( pp6VERTEX *V, INT NumOfV, INT *I, INT NumOfI);

/*GRID*/
BOOL PP6_RndPrimCreateGrid( pp6PRIM *Pr, INT SplitW, INT SplitH, pp6VERTEX *V );
VOID PP6_RndPrimGridEvalNormals( INT SplitW, INT SplitH, pp6VERTEX *V );

/*prims*/
/* Create array of primitives function.
* ARGUMENTS:
 *   - pointer to primitives structure:
 *       pp6PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL PP6_RndPrimsCreate( pp6PRIMS *Prs, INT NumOfPrims );

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       pp6PRIMS *Prs;
 * RETURNS: None.
 */
VOID PP6_RndPrimsFree( pp6PRIMS *Prs );

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       pp6PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID PP6_RndPrimsDraw( pp6PRIMS *Prs, MATR World );

/* Load array of primitives from .G3DM file function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       pp6PRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL PP6_RndPrimsLoad( pp6PRIMS *Prs, CHAR *FileName );





#endif /* __rnd_h_ */