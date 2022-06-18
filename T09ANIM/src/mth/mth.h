/* FILE NAME: mth.h
 * PROGRAMMER: PP6
* DATE: 07.06.2022
* PURPOSE: 3D math implementation module.
 */

#ifndef __mth_h_
#define __mth_h_

#include <windows.h>
#include <math.h>

/* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define R2D(A) ((A) * (180 / PI))
#define Degree2Radian(a) D2R(a)

/* Base float point types */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Space vector/point representation type */
typedef struct tagVEC
{
  FLT X, Y, Z; /* Vector coordinates */
} VEC;

/* 2 Space vector/point representation type */
typedef struct tagVEC2
{
  FLT X, Y; /* Vector coordinates */
} VEC2;

/* Space vector/point representation type */
typedef struct tagVEC4
{
  FLT X, Y, Z, W; /* Vector coordinates */
} VEC4;

/* type for matrix - array by size */
typedef struct tagMATR
{
  FLT A[4][4];
} MATR;

/*implementation functions*/
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v = {X, Y, Z};
  return v;
}/* End of 'VecSet' function */

/*implementation functions*/
__inline VEC2 Vec2Set( FLT X, FLT Y )
{
  VEC2 v = {X, Y};
  return v;
}/* End of 'Vec2Set' function */

/*implementation functions*/
__inline VEC4 VecSet4( FLT X, FLT Y, FLT Z, FLT W )
{
  VEC4 v = {X, Y, Z, W};
  return v;
}/* End of 'VecSet4' function */

#define COM_MIN(A, B) ((A) < (B) ? (A) : (B))
#define COM_MAX(A, B) ((A) > (B) ? (A) : (B))

/**/
__inline VEC VecMinVec( VEC V1, VEC V2 )
{
  return VecSet(COM_MIN(V1.X, V2.X), COM_MIN(V1.Y, V2.Y), COM_MIN(V1.Z, V2.Z));
} /**/

/**/
__inline VEC VecMaxVec( VEC V1, VEC V2 )
{
  return VecSet(COM_MAX(V1.X, V2.X), COM_MAX(V1.Y, V2.Y), COM_MAX(V1.Z, V2.Z));
} /**/
/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Set two vectors function.
 * ARGUMENTS:
 *   - vectors to be set:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

 /* multiply a vector by a number
 * ARGUMENTS:
 *   - vector to be mul:
 *       VEC V1, FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulNum( VEC V1, FLT N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

/* div a vector by a number
 * ARGUMENTS:
 *   - vector to be div:
 *       VEC V1, FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC V1, FLT N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
} /* End of 'VecDivNum' function */

/* neg a vector
 * ARGUMENTS:
 *   - vector to be Neg:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* dot product of vectors
 * ARGUMENTS:
 *   - dot vectors
 *       VEC V1, V2;
 * RETURNS:
 *   (FLT) result vector.
 */
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
 return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}/* End of 'VecDotVec' function */
 
/* cross product of vectors
 * ARGUMENTS:
 *   - cross vectors
 *       VEC V1, V2;
 *   - 
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}/* End of 'VecCrossVec' function */

/* vector length squared
 * ARGUMENTS:
 *   - cross vectors
 *       VEC V;
 * RETURNS:
 *   (FLT) length.
 */

__inline FLT VecLen2( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return len;
}/* End of 'VecLen2' function */

/* vector length
 * ARGUMENTS:
 *   - vector length
 *       VEC V;
 * RETURNS:
 *   (FLT) length.
 */
__inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}/* End of 'VecLen' function */

/* vector length
 * ARGUMENTS:
 *   - cross vectors
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNormalize( VEC V )   
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}/* End of 'VecNormalize' function */

/*  vector coordinates are multiplied by a 4x3 matrix
 * ARGUMENTS:
 *   - mul coordinates by mateix 4x3
 * VEC V, Matr M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
}/* End of 'PointTransform' function */

/*  vector coordinates are multiplied by a 3x3 matrix
 * ARGUMENTS:
 *   - mul coordinates by mateix 3x3
 * VEC V, Matr M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}/* End of 'VectorTransform' function */

/*  vector coordinates are multiplied by a 4x4 matrix and div w
 * ARGUMENTS:
 *   - mul coordinates by mateix 4x4
 * VEC V, Matr M;
 *   - 
 * 
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulMatr( VEC V, MATR M )
{
  FLT w;

  w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
}/* End of 'VecMulMatr' function */

/*  create 4x4 matrix
 * ARGUMENTS:
 *   - mul coordinates by mateix 4x4
 * Matr FLT A00, FLT A01, FLT A02, FLT A03,
 * FLT A10, FLT A11, FLT A12, FLT A13,
 * FLT A20, FLT A21, FLT A22, FLT A23,
 * FLT A30, FLT A31, FLT A32, FLT A33,
 * RETURNS:
 *   (Matr) result.
 */
__inline MATR MatrSet(FLT A00, FLT A01, FLT A02, FLT A03,
                      FLT A10, FLT A11, FLT A12, FLT A13,
                      FLT A20, FLT A21, FLT A22, FLT A23,
                      FLT A30, FLT A31, FLT A32, FLT A33)
{
  MATR r =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33},
    }
  };
  return r;
}/* End of 'VecMulMatr' function */
/*
*  vector coordinates are multiplied by a 4x4 matrix and div w
 * ARGUMENTS:
 *   - mul coordinates by mateix 4x4
 * VEC V, Matr M;
 *   - 
 * 
 * RETURNS:
 *   (VEC) result vector.
 */
__inline MATR MatrIdentity( VOID )
{
  return MatrSet(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);
}/* End of 'MatrIdentity' function */

/*  
 * ARGUMENTS:
 *   - mul coordinates by mateix 3x3
 * VEC V, Matr M;
 * RETURNS:
 *   (Matr) result vector.
 */
__inline MATR MatrTranslate( VEC T )
{
  return MatrSet(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                T.X, T.Y, T.Z, 1);
}/* End of 'MatrTranslate' function */

/*  
 * ARGUMENTS:
 *   - mul coordinates by mateix 3x3
 * VEC V, Matr M;
 * RETURNS:
 *   (Matr) result vector.
 */
__inline MATR MatrScale( VEC S )
{
  return MatrSet(S.X, 0, 0, 0,
                 0, S.Y, 0, 0,
                 0, 0, S.Z, 0,
                 0, 0, 0, 1);
} /* End of 'MatrScale' function */

__inline MATR MatrRotate( FLT AngleInDegree, VEC V )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  VEC A = VecNormalize(V);
  MATR m =
  {
    {
      {c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - A.Y * s, 0},
      {A.X * A.Y * (1 - c) - A.Z * s, A.Y * A.Y * (1 - c) + c, A.Y * A.Z * (1 - c) + A.X * s, 0},
      {A.Z * A.X * (1 - c) + A.Y * s, A.Z * A.Y * (1 - c) - A.X * s, A.Z * A.Z * (1 - c) + c, 0},
      {0, 0, 0, 1},
    }  
  };
  return m;
}

__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, c, s, 0},
      {0,-s, c, 0},
      {0, 0, 0, 1},
    }  
  };
  return m;
}
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
   MATR m =
  {
    {
      {c, 0, -s, 0},
      {0, 1, 0, 0},
      {s, 0, c, 0},
      {0, 0, 0, 1},
    }  
  };
  return m;
}
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  MATR m =
  {
    {
      {c, s, 0, 0},
      {-s, c, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1},
    }  
  };
  return m;
}
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  INT i, j, k;
  MATR r = {{{0}}};

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (k = 0; k < 4; k++)
         r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
}
__inline MATR MatrTranspose( MATR M )
{
  return MatrSet(M.A[0][0], M.A[1][0], M.A[2][0], M.A[3][0],
                 M.A[0][1], M.A[1][1], M.A[2][1], M.A[3][1],
                 M.A[0][2], M.A[1][2], M.A[2][2], M.A[3][2],
                 M.A[0][3], M.A[1][3], M.A[2][3], M.A[3][3]);
}

/**/
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                            FLT A21, FLT A22, FLT A23,
                            FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}/**/

/**/
__inline FLT MatrDeterm( MATR M )
{
  return
    + M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                                M.A[2][1], M.A[2][2], M.A[2][3],
                                M.A[3][1], M.A[3][2], M.A[3][3]) +

    - M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                                M.A[2][0], M.A[2][2], M.A[2][3],
                                M.A[3][0], M.A[3][2], M.A[3][3]) +

    + M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                                M.A[2][0], M.A[2][1], M.A[2][3],
                                M.A[3][0], M.A[3][1], M.A[3][3]) +


    - M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                                M.A[2][0], M.A[2][1], M.A[2][2],
                                M.A[3][0], M.A[3][1], M.A[3][2]);
} /**/

/**/
__inline MATR MatrInverse( MATR M )
{
  FLT det = MatrDeterm(M);
  MATR r;

  if (det == 0)
  /* build adjoint matrix */
  r.A[0][0] =
    + MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                    M.A[2][1], M.A[2][2], M.A[2][3],
                    M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][0] =
    - MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                    M.A[2][0], M.A[2][2], M.A[2][3],
                    M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][0] =
    + MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                    M.A[2][0], M.A[2][1], M.A[2][3],
                    M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][0] =
    - MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                    M.A[2][0], M.A[2][1], M.A[2][2],
                    M.A[3][0], M.A[3][1], M.A[3][2]) / det;


  r.A[0][1] =
    - MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                    M.A[2][1], M.A[2][2], M.A[2][3],
                    M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][1] =
    + MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                    M.A[2][0], M.A[2][2], M.A[2][3],
                    M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][1] =
    - MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                    M.A[2][0], M.A[2][1], M.A[2][3],
                    M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][1] =
    + MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                    M.A[2][0], M.A[2][1], M.A[2][2],
                    M.A[3][0], M.A[3][1], M.A[3][2]) / det;
  r.A[0][2] =
    + MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                    M.A[1][1], M.A[1][2], M.A[1][3],
                    M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][2] =
    - MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                    M.A[1][0], M.A[1][2], M.A[1][3],
                    M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][2] =
    + MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                    M.A[1][0], M.A[1][1], M.A[1][3],
                    M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][2] =
    - MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                    M.A[1][0], M.A[1][1], M.A[1][2],
                    M.A[3][0], M.A[3][1], M.A[3][2]) / det;

  r.A[0][3] =
    - MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                    M.A[1][1], M.A[1][2], M.A[1][3],
                    M.A[2][1], M.A[2][2], M.A[2][3]) / det;
  r.A[1][3] =
    + MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                    M.A[1][0], M.A[1][2], M.A[1][3],
                    M.A[2][0], M.A[2][2], M.A[2][3]) / det;
  r.A[2][3] =
    - MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                    M.A[1][0], M.A[1][1], M.A[1][3],
                    M.A[2][0], M.A[2][1], M.A[2][3]) / det;
  r.A[3][3] =
    + MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                    M.A[1][0], M.A[1][1], M.A[1][2],
                    M.A[2][0], M.A[2][1], M.A[2][2]) / det;
 return MatrIdentity();
}/**/

/* Perspective (frustum) projection matrix setup function.
 * ARGUMENTS:
 *   - frustum side facets coordinates:
 *       FLT Left, Right, Bottom, Top, Near, Far;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrFrustum( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far )
{
  MATR m =
  {
    {
      {2 * Near / (Right - Left), 0, 0, 0},
      {0, 2 * Near / (Top - Bottom), 0, 0},
      {(Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), -1},
      {0, 0, -2 * Near * Far / (Far - Near), 0}
    }
  };
  return m;
} /* End of 'MatrFrustum' function */

/* Orthographics projection matrix setup function.
 * ARGUMENTS:
 *   - orthographic box side facets coordinates:
 *       FLT Left, Right, Bottom, Top, Near, Far;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrOrtho( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far )
{
  MATR m =
  {
    {
      {2 / (Right - Left), 0, 0, 0},
      {0, 2 / (Top - Bottom), 0, 0},
      {0, 0, -2 / (Far - Near), 0},
      {-(Right + Left) / (Right - Left), -(Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), 1}
    }
  };
  return m;
} /* End of 'MatrOrtho' function */

/* Matrix look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
}/* End of 'MatrView' function */

#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */