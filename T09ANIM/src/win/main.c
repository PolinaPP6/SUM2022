/* FILE NAME   : main.c
 * PROGRAMMER  : PP6
 * LAST UPDATE : 08.06.2022
 * PURPOSE     : 3D animation project.
 *               Startup module.
 */
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>

#include "pp6.h"

/**/
#define WND_CLASS_NAME "My window class"

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - message type (see WM_***):
 *       UINT Msg;
 *   - message 'word' parameter:
 *       WPARAM wParam;
 *   - message 'long' parameter:
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;

  switch (Msg)
  {
  case WM_CREATE:
    PP6_AnimInit(hWnd);
    SetTimer(hWnd, 47, 100, NULL);
    return 0;

  case WM_SIZE:
    PP6_AnimResize(LOWORD(lParam), HIWORD(lParam));
    PP6_AnimRender();
    PP6_AnimCopyFrame();
    return 0;

  case WM_DESTROY:
    PP6_AnimClose();
    KillTimer(hWnd, 47);
    PostQuitMessage(0);
    return 0;

  case WM_TIMER:
    PP6_AnimRender();
    PP6_AnimCopyFrame();
    return 0;

  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      PostMessage(hWnd, WM_CLOSE, 0, 0);
    else if (wParam == VK_F11)
      ;
    return 0;

  case WM_MOUSEWHEEL:
    PP6_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;

  case WM_LBUTTONDOWN:
    SetCapture(hWnd);
    return 0;

  case WM_LBUTTONUP:
    ReleaseCapture();
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    PP6_AnimCopyFrame();
    EndPaint(hWnd, &ps);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
   /*case WM_GETMINMAXINFO:                        
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;*/
  }
/* End of 'WinFunc' function */

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  SetDbgMemHooks();

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  hWnd =
    CreateWindow(WND_CLASS_NAME, "OPS", WS_OVERLAPPEDWINDOW, 600, 600, 600, 600, NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  PP6_AnimAddUnit(PP6_UnitCreateCow());
  PP6_AnimAddUnit(PP6_UnitCreateControl());
  PP6_AnimAddUnit(PP6_UnitCreateLand());
  PP6_AnimAddUnit(PP6_UnitCreateg3dm());
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 47, 0);
  return msg.wParam;
}/* End of 'WinMain' function */
/* END OF 'main.c' FILE */