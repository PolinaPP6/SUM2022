/* T02EYES.C
 * Programmer: PP6
 * DATE: 02.06.2022
 * PURPOSE: draw eyes
 */
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define WND_CLASS_NAME "My window class"

void DrawEye( HDC hDC, INT x, INT y, INT r, INT r1, INT mx, INT my );

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  POINT pt;
  SYSTEMTIME st;
  PAINTSTRUCT ps;
  CHAR Buf[100];
  static INT W, H;
  static HDC hMemDC;
  static HBITMAP hBm;

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;
    SetTimer(hWnd, 47, 100, NULL);
    return 0;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 47);
    PostQuitMessage(0);
    return 0;

  case WM_COMMAND:
    switch(LOWORD(wParam))
    {
    case 777:
      PostMessage(hWnd, WM_CLOSE, 0, 0);
      return 0;
    }
    return 0;

  case WM_TIMER:
    Rectangle(hMemDC, 0, 0, W, H);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    DrawEye(hMemDC, W / 2, H / 2, 100, 50, pt.x, pt.y);
    DrawEye(hMemDC, W / 10, H / 2, 100, 50, pt.x, pt.y);

    GetLocalTime(&st);
    TextOut(hMemDC, 0, 0, Buf, wsprintf(Buf, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond));

    hDC = GetDC(hWnd);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd, h1Wnd;
  MSG msg;
  HBRUSH hbr;

  hbr = CreateSolidBrush(RGB(252, 247, 134));

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = hbr;
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
    CreateWindow(WND_CLASS_NAME, "OPS", WS_OVERLAPPEDWINDOW, 400, 400, 400, 400, NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  h1Wnd =
    CreateWindow("BUTTON", "OMG", WS_CHILD, 40, 40, 40, 40, hWnd, (HMENU)777, hInstance, NULL);
  ShowWindow(h1Wnd, SW_SHOWNORMAL);

  UpdateWindow(hWnd);
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  DeleteObject(hbr);
  return msg.wParam;
}

void DrawEye( HDC hDC, INT x, INT y, INT r, INT r1, INT mx, INT my )
{
  double lin = sqrt((mx - x) * (mx - x) + (my - y) * (my - y));

  SelectObject(hDC, GetStockObject(DC_PEN));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(255, 255, 255));
  SetDCPenColor(hDC, RGB(0, 0, 0));
  Ellipse(hDC, x - r, y - r, x + r, y + r);
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  Ellipse(hDC, x + (INT)((mx - x) * (r - r1) / lin) - r1, y + (INT)((my - y) * (r - r1) / lin) - r1,
               x + (INT)((mx - x) * (r - r1) / lin) + r1, y + (INT)((my - y) * (r - r1) / lin) + r1);
}


