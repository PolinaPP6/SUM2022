/* FILE NAME   : rnddata.c
 * PROGRAMMER  : PP6
 * LAST UPDATE : 09.06.2022
 * PURPOSE     : 3D animation project.
 *               Rendering system declaration module.
 */
#include "rnd.h"

HWND PP6_hRndWnd;                 /* Work window handle */
HDC PP6_hRndDC;              /* Work window memory device context  */
INT PP6_RndFrameW, PP6_RndFrameH; /* Work window size */
HGLRC PP6_hRndGLRC;               /* Work OpenGL rendering context */

DBL
  PP6_RndProjSize = 0.1,  /* Project plane fit square */
  PP6_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  PP6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  PP6_RndMatrView, /* View coordinate system matrix */
  PP6_RndMatrProj, /* Projection coordinate system matrix */
  PP6_RndMatrVP;   /* Stored (View * Proj) matrix */

