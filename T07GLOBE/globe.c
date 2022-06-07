/* T07GLOBE.C
 * Programmer: PP6
 * DATE: 06.06.2022
 * PURPOSE: draw globe
 */
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "globe.h"
#include <time.h>

#define GRID_H 15
#define GRID_W 30

#define pi 3.14159265358979323846

static VEC Geom[GRID_H][GRID_W];

/*array filling*/
VOID GlobeSet( DOUBLE R )
{
  INT i, j;
  DBL theta, phi;

  for (i = 0, theta = 0; i < GRID_H; i++, theta += 1 * pi / (GRID_H - 1))
    for (j = 0, phi = 0; j < GRID_W; j++, phi += 2 * pi / (GRID_W - 1))
    {
      Geom[i][j].X = R * sin(theta) * sin(phi);
      Geom[i][j].Y = R * cos(theta);
      Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
}

/**/
VEC RotateX( VEC p, DBL ANGLE )
{
  DBL a = ANGLE * pi / 180;
  VEC Np;

  Np.Y = p.Y * cos(a) - p.Z * sin(a);
  Np.Z = p.Y * sin(a) + p.Z * cos(a);
  Np.X = p.X;
  return Np;

}

/**/
VEC RotateY( VEC p, DBL ANGLE)
{
  DBL a = ANGLE * pi / 180;
  VEC Np;

  Np.X = p.X * cos(a) - p.Z * sin(a);
  Np.Y = p.X * sin(a) + p.Z * cos(a);
  Np.Z = p.Z;
  return Np;

}

/**/
VEC RotateZ( VEC p, DBL ANGLE)
{
  DBL a = ANGLE * pi / 180;
  VEC Np;

  Np.X = p.X * cos(a) - p.Y * sin(a);
  Np.Y = p.X * sin(a) + p.Y * cos(a);
  Np.Z = p.Z;
  return Np;

}
/**/
VOID GlobeDraw(HDC hDC, INT W, INT H)
{
  static POINT pnts[GRID_H][GRID_W];
  POINT ps[4];
  INT i, j;
  DBL r, t = clock() / (DBL)CLOCKS_PER_SEC;
  VEC p;

  r = (W < H ? W : H) / 2;

  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      p = Geom[i][j];
      p = RotateX(p, t * 30);
      p = RotateY(p, t * 20);
      p = RotateZ(p, t * 10);
      pnts[i][j].x = (INT)((r * p.X) + W / 2);
      pnts[i][j].y = (INT)(-(r * p.Y) + H / 2);
    }
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
      Ellipse(hDC, pnts[i][j].x - 3, pnts[i][j].y - 3, pnts[i][j].x + 3, pnts[i][j].y + 3);

  for (i = 0; i < GRID_H; i++)
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 1; j < GRID_W ; j++)
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }
  for (j = 0; j < GRID_W; j++)
  {
    MoveToEx(hDC, pnts[0][j].x, pnts[0][j].y, NULL);
    for (i = 1; i < GRID_H; i++)
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }
  srand(30);
  for (i = 0; i < GRID_H - 1; i++)
    for (j = 0; j < GRID_W - 1; j++)
    {
      SelectObject(hDC, GetStockObject(DC_BRUSH));
      SetDCBrushColor(hDC, RGB(222, 222, 222));
      ps[0] = pnts[i][j];
      ps[1] = pnts[i][j + 1];
      ps[2] = pnts[i + 1][j + 1];
      ps[3] = pnts[i + 1][j];
      if ((ps[0].x - ps[1].x) * (ps[0].y + ps[1].y) +
          (ps[1].x - ps[2].x) * (ps[1].y + ps[2].y) +
          (ps[2].x - ps[3].x) * (ps[2].y + ps[3].y) +
          (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y) <= 0)
        Polygon(hDC, ps, 4);
    }
}
