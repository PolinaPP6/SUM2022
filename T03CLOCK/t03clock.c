/* T02EYES.C
 * Programmer: PP6
 * DATE: 02.06.2022
 * PURPOSE: draw clock
 */
#include <stdlib.h>
#include <math.h>
#include <windows.h>

/**/
#define WND_CLASS_NAME "My window class"

/*draw hands*/
VOID DrawHand( HDC hDC, INT X, INT Y, INT X1, INT Y1 );
VOID DrawHand1( HDC hDC, INT X, INT Y, INT X1, INT Y1 );
VOID DrawHand2( HDC hDC, INT X, INT Y, INT X1, INT Y1 );
VOID BEATYLINE( HDC hDC, INT X, INT Y, DOUBLE ANGLE, INT L, INT W, COLORREF Color );
VOID FlipFullScreen( HWND hWnd );
/**/
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  POINT pt;
  POINT pnts[] = 
  {
     {0, 100}, {20, 70}, {0, -100}, {-20, 70}
  };
  PAINTSTRUCT ps;
  CHAR Buf[100];
  BITMAP bm;
  SYSTEMTIME st;
  double p = 3.14159265358979323846;
  /* HFONT hFnt, hFntOld;
  RECT rc; */
  static INT W, H;
  static HDC hMemDC;
  static HDC hMemDC1;
  static HBITMAP hBm;
  static HBITMAP hBm1;

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDC1 = CreateCompatibleDC(hDC);
    hBm1 = LoadImage(NULL, "CLOCK.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC1, hBm1);
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
    if (hBm1 != NULL)
      DeleteObject(hBm1);
    DeleteDC(hMemDC);
    DeleteDC(hMemDC1);
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
    SelectObject(hMemDC, GetStockObject(NULL_PEN));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(255, 255, 255));
    Rectangle(hMemDC, 0, 0, W, H);
    SelectObject(hMemDC, GetStockObject(DC_PEN));

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    GetLocalTime(&st);

    /* Draw clockface */
    GetObject(hBm1, sizeof(BITMAP), &bm);
    StretchBlt(hMemDC, (W - bm.bmWidth) / 2, (H - bm.bmHeight) / 2, bm.bmWidth, bm.bmHeight,
      hMemDC1, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    /* Output time as text */
    GetLocalTime(&st);
    TextOut(hMemDC, 0, 0, Buf, wsprintf(Buf, "%02d:%02d:%02d", st.wHour,
      st.wMinute, st.wSecond));

        /* create and use font */
    /*hFntOld = SelectObject(hMemDC, hFnt);
    hFnt = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
      RUSSIAN_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY,VARIABLE_PITCH | FF_SCRIPT, "consolas");
    SelectObject(hMemDC, hFntOld);
    DeleteObject(hFnt);*/

    /* Color background */
    /*SetTextColor(hMemDC, RGB(67, 98, 167));
    SetBkColor(hMemDC, RGB(26, 89, 178));
    SetBkMode(hMemDC, TRANSPARENT);*/

    /* 
    rc.left = 0;
    rc.top = H * 3 / 4;
    rc.right = W;
    rc.bottom = H;
    GetClientRect(hWnd, &rc);
    DrawText(hMemDC, Buf, 100, &rc, DT_CENTER | DT_SINGLELINE | DT_BOTTOM);*/

    /* Draw hands */
    /*DrawHand(hMemDC,
      W / 2, H / 2,
      (INT)(W / 2 + ((bm.bmWidth) / 2) * sin(st.wSecond * 2 * p / 60)),
      (INT)(H / 2 - ((bm.bmHeight) / 2) * cos(st.wSecond * 2 * p / 60)));
    DrawHand1(hMemDC,
      W / 2, H / 2,
      (INT)(W / 2 + ((bm.bmWidth) / 2) * sin(st.wMinute * 2 * p / 60)),
      (INT)(H / 2 - ((bm.bmHeight) / 2) * cos(st.wMinute * 2 * p / 60)));
    DrawHand2(hMemDC,
      W / 2, H / 2,
      (INT)(W / 2 + ((bm.bmWidth) / 2) * sin((st.wHour % 12 + st.wMinute / 60.0) * 2 * p / 12)),
      (INT)(H / 2 - ((bm.bmHeight) / 2) * cos((st.wHour % 12 + st.wMinute / 60.0) * 2 * p / 12)));*/
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    BEATYLINE( hMemDC, W / 2, H / 2,(st.wHour % 12 + st.wMinute / 60.0) * 2 * p / 12, H * 2 / 8, 30, RGB(0, 0, 255));
    BEATYLINE( hMemDC, W / 2, H / 2, st.wMinute * 2 * p / 60, H * 1 / 3, 20, RGB(0, 255, 0));
    BEATYLINE( hMemDC, W / 2, H / 2, st.wSecond * 2 * p / 60, H * 3 / 8, 10, RGB(255, 0, 0));

    /* Copy back buffer to screen */
    hDC = GetDC(hWnd);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      PostMessage(hWnd, WM_CLOSE, 0, 0);
    else if (wParam == VK_F11)
     FlipFullScreen(hWnd);

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
    CreateWindow(WND_CLASS_NAME, "OPS", WS_OVERLAPPEDWINDOW, 600, 600, 600, 600, NULL, NULL, hInstance, NULL);
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

/* draw secondhand */
VOID DrawHand( HDC hDC, INT X, INT Y, INT X1, INT Y1 )
{
  HPEN hPen, holdPen;
  SYSTEMTIME st;
  DOUBLE p = 3.14159265358979323846;

  GetLocalTime(&st);
  hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
  holdPen = SelectObject(hDC, hPen);

  MoveToEx(hDC, X, Y, NULL);
  LineTo(hDC, X1, Y1);

  SelectObject(hDC, holdPen);
  DeleteObject(hPen);
}

/* draw minutehand */
VOID DrawHand1( HDC hDC, INT X, INT Y, INT X1, INT Y1 )
{
  HPEN hPen, holdPen;
  SYSTEMTIME st;
  DOUBLE p = 3.14159265358979323846;

  GetLocalTime(&st);
  hPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
  holdPen = SelectObject(hDC, hPen);

  MoveToEx(hDC, X, Y, NULL);
  LineTo(hDC, X1, Y1);

  SelectObject(hDC, holdPen);
  DeleteObject(hPen);
}

/* draw hourhand */
VOID DrawHand2( HDC hDC, INT X, INT Y, INT X1, INT Y1 )
{
  HPEN hPen, holdPen;
  SYSTEMTIME st;
  DOUBLE p = 3.14159265358979323846;

  GetLocalTime(&st);
  hPen = CreatePen(PS_SOLID, 30, RGB(255, 255, 255));
  holdPen = SelectObject(hDC, hPen);

  MoveToEx(hDC, X, Y, NULL);
  LineTo(hDC, X1, Y1);

  SelectObject(hDC, holdPen);
  DeleteObject(hPen);
}
/* draw polygon */
VOID BEATYLINE( HDC hDC, INT X, INT Y, DOUBLE ANGLE, INT L, INT W, COLORREF Color )
{
  POINT pt;
  INT i;
  POINT pnts[] =
  {
     {0, L}, {W, L * 3 / 4}, {0, -L / 3}, {-W, L * 3 / 4}
  };
  POINT pnts1[sizeof(pnts) / sizeof(pnts[0])];
  DOUBLE si, co;

  SetDCBrushColor(hDC, Color);

  si = sin(ANGLE);
  co = cos(ANGLE);
  for (i = 0; i < sizeof(pnts) / sizeof(pnts[0]); i++)
  {
    pnts1[i].x = (INT)(X + (pnts[i].x * co + pnts[i].y * si));
    pnts1[i].y = (INT)(Y - (pnts[i].y * co - pnts[i].x * si));
  }
  Polygon(hDC, pnts1, sizeof(pnts1) / sizeof(pnts[0]));
}

/* full screen */
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;
 
  if (!IsFullScreen)
  {
    HMONITOR hmon;
    MONITORINFO mi;
    RECT rc;
 
    /* Save old window size and position */
    GetWindowRect(hWnd, &SaveRect);
 
    /* Go to full screen mode */
 
    /* oBTAIN NEAREST MONITOR */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hmon, &mi);
 
    /* Expand window */
    rc = mi.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
 
    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left,
      rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Restore from full screen mode */
    SetWindowPos(hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left,
      SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
} /* End of 'FlipFullScreen' function */


