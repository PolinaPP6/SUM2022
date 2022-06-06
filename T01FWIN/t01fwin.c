/* Pavlova Polina */
#include <windows.h>

#define WND_CLASS_NAME "My window class"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  switch (Msg)

  {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_COMMAND:
    switch(LOWORD(wParam))
    {
    case 777:
      PostMessage(hWnd, WM_CLOSE, 0, 0);
      return 0;
    return 0;
    }
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
    CreateWindow(WND_CLASS_NAME, "OPS", WS_OVERLAPPEDWINDOW, 90, 70, 400, 400, NULL, NULL, hInstance, NULL);
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
  return msg.wParam;
  DeleteObject(hbr);
  return 0;
}

