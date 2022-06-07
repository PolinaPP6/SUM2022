/* T07GLOBE.C
 * Programmer: PP6
 * DATE: 06.06.2022
 * PURPOSE: draw clock
 */
#include <windows.h>
#include "mth.h"
#include "timer.h"
VOID GlobeSet( DOUBLE R );
VOID GlobeDraw(HDC hDC, INT W, INT H);
VEC RotateX( VEC p, DBL ANGLE);
VEC RotateY( VEC p, DBL ANGLE);
VEC RotateZ( VEC p, DBL ANGLE);