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
#include "mth.h"


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
      Geom[i][j].X = 0.5 * R * sin(theta) * sin(phi);
      Geom[i][j].Y = 2 * R * cos(theta);
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
  DBL /*r,*/ t = clock() / (DBL)CLOCKS_PER_SEC, Wp, Hp, size, ProjDist;
  MATR m;

  /*r = (W < H ? W : H) / 2;*/
  ProjDist = size = 1;
  Wp = Hp = size;
  if (Wp > Hp)
    Wp *= (DBL)W / H;
  else
    Hp *= (DBL)H / W;

  m = MatrIdentity();
  m = MatrMulMatr(MatrRotateX(12 * GLB_Time),
      MatrMulMatr(MatrRotateY(0 * 145 * sin(GLB_Time)),
      MatrMulMatr(/*MatrTranslate(VecSet(0, 0 * fabs(sin(GLB_Time * 2)) -0.5, -2 - GLB_Time * 0.0)),*/
                  MatrView(VecSet(0 * 2 * sin(GLB_Time), 0, 10), VecSet(0, 0, 0), VecSet(0, 1, 0)),
                  MatrFrustum(-Wp / 2, Wp / 2, -Hp / 2, Hp / 2, ProjDist, 200))));
  /*
  m = MatrFrustum(-Wp / 2, Wp / 2, -Hp / 2, Hp / 2, ProjDist, 200);
  m = MatrRotateX(12 * GLB_Time);
  m = MatrView(VecSet(0 * 2 * sin(GLB_Time), 0, 1), VecSet(0, 0, 0), VecSet(0, 1, 0));
  */

  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      VEC p = VecMulMatr(Geom[i][j], m);
      
      /*
      DBL xp, yp;

      p = Geom[i][j];
      p = RotateX(p, t * 30);
      p = RotateY(p, t * 20);
      p = RotateZ(p, t * 10);
      xp = p.X * ProjDist / (-p.Z);
      yp = p.Y * ProjDist / (-p.Z);
      */

      pnts[i][j].x = (INT)((p.X + 1) * W / 2);
      pnts[i][j].y = (INT)((-p.Y + 1) * H / 2);
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
          (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y) >= 0)
        Polygon(hDC, ps, 4);
    }
}
