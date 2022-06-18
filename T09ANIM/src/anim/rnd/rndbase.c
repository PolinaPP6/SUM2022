/* FILE NAME   : rndbase.c
 * PROGRAMMER  : PP6
 * LAST UPDATE : 17.06.2022
 * PURPOSE     : 3D animation project.
 *               Startup module.
 */

#include "pp6.h"
#include <wglew.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32")

VOID PP6_RndInit( HWND hWnd )
{
  INT i, nums;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };

  PP6_hRndWnd = hWnd;
  PP6_hRndDC = GetDC(hWnd);
  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(PP6_hRndDC, &pfd);
  DescribePixelFormat(PP6_hRndDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(PP6_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  PP6_hRndGLRC = wglCreateContext(PP6_hRndDC);
  wglMakeCurrent(PP6_hRndDC, PP6_hRndGLRC);

  /* Initializing GLEW library */
  if (glewInit() != GLEW_OK)
  {
    MessageBox(PP6_hRndWnd, "Error extensions initializing", "Error",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(PP6_hRndWnd, "Error: no shaders support", "Error", MB_ICONERROR | MB_OK);
    exit(0);
  }

  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(PP6_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(PP6_hRndDC, NULL, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(PP6_hRndGLRC);

  PP6_hRndGLRC = hRC;
  wglMakeCurrent(PP6_hRndDC, PP6_hRndGLRC);

  glClearColor(0.7, 0.2, 0.13, 1);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  PP6_RndCamSet(VecSet(0, 1, 50), VecSet(0, 0, 1), VecSet(0, 1, 0));
  PP6_RndResInit();
}

VOID PP6_RndClose( VOID )
{
  PP6_RndResClose();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(PP6_hRndGLRC);
  ReleaseDC(PP6_hRndWnd, PP6_hRndDC);
}

VOID PP6_RndResize( INT W, INT H )
{
  /* save size */
  PP6_RndFrameW = W;
  PP6_RndFrameH = H;

  glViewport(0, 0, W, H);
  /*  */
  PP6_RndProjSet();
}

VOID PP6_RndCopyFrame( VOID )
{
  SwapBuffers(PP6_hRndDC);
}

VOID PP6_RndStart( VOID )
{
  static DBL ReloadTime;

  if (PP6_Anim.GlobalTime - ReloadTime > 2)
  {
    ReloadTime = PP6_Anim.GlobalTime;

    PP6_RndShdUpdate();
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

VOID PP6_RndEnd( VOID )
{
  glFinish();
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

  PP6_RndCamLoc = Loc;
  PP6_RndCamRight = VecSet(PP6_RndMatrView.A[0][0], PP6_RndMatrView.A[1][0], PP6_RndMatrView.A[2][0]);
  PP6_RndCamUp = VecSet(PP6_RndMatrView.A[0][1], PP6_RndMatrView.A[1][1], PP6_RndMatrView.A[2][1]);
  PP6_RndCamDir = VecSet(-PP6_RndMatrView.A[0][2], -PP6_RndMatrView.A[1][2], -PP6_RndMatrView.A[2][2]);
  PP6_RndCamAt = At;
  
  PP6_RndMatrVP = MatrMulMatr(PP6_RndMatrView, PP6_RndMatrProj);
}
