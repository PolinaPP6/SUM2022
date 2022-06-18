/* FILE NAME  : rndres.h
 * PROGRAMMER : PP6
 * LAST UPDATE: 14.06.2022
 * PURPOSE    : 3D animation project.
 *              Render subsystem implementation module.
 *              Rendering resourse handle declaration module.
 */

#ifndef __rndres_h_
#define __rndres_h_

#include "def.h"

/* Maximum resourse string size */
#define PP6_STR_MAX 300
/* Shaders stock maximum size */
#define PP6_MAX_SHADERS 30
/* Textures stock */
#define PP6_MAX_TEXTURES 30
/* Material stock */
#define PP6_MAX_MATERIALS 30


/* Resourses system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndResInit( VOID );

/* Resourses system deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndResClose( VOID );

/***
 * Shaders support
 ***/

/* Shader program store type */
typedef struct tagpp6SHADER
{
  CHAR Name[PP6_STR_MAX]; /* Shader filename prefix */
  UINT ProgId;            /* Shader program Id */
} pp6SHADER;

/*Texture representation type*/
typedef struct tagpp6TEXTURE
{
  CHAR Name[PP6_STR_MAX]; /* Texture name */
  UINT TexId;            /* OpenGL texture Id */
  INT W, H;       /*Texture size in pixels*/
} pp6TEXTURE;


/*Material representation type*/
typedef struct tagpp6MATERIAL
{
  CHAR Name[PP6_STR_MAX]; /* Material name */
  /*Illumination coefficients*/
  VEC Ka, Kd, Ks; /* Ambient, diffuse, specular coefficients */
  INT Tex[8];     /* Texture refererences from texture  table */
  FLT Trans;
  FLT Ph;/*Texture size in pixels*/
  /* Shader string */
  INT ShdNo;
  CHAR ShaderStr[PP6_STR_MAX];
} pp6MATERIAL;

/* Font description structure */
typedef struct tagpp6FONT
{
  DWORD LineH, BaseH; /* Font line height and base line height in pixels */
  FLT AdvanceX[256];  /* Every letter shift right value (0 if no letter present) */
} pp6FONT;

extern pp6SHADER PP6_RndShaders[PP6_MAX_SHADERS];    /* Array of shaders */
extern INT PP6_RndShadersSize;                       /* Shadres array store size */
extern pp6TEXTURE PP6_RndTextures[PP6_MAX_TEXTURES]; /* Array of textures */
extern INT PP6_RndTexturesSize;                      /* Textures array store size */
extern pp6MATERIAL PP6_RndMaterials[PP6_MAX_MATERIALS]; /* Array of materials */
extern INT PP6_RndMaterialsSize;                        /* Materials array store size */


/* Shader storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndShdInit( VOID );

/* Shader storage deinitialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndShdClose( VOID );

/* Update from file all load shaders function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndShdUpdate( VOID );

/* Texture store system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */

/* Add shader to stock from file function.
 * ARGUMENTS:
 *   - shader file path to load:
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) new shader stock number.
 */
INT PP6_RndShdAdd( CHAR *ShaderFileNamePrefix );

VOID PP6_RndTexInit( VOID );

/* Texture store system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndTexClose( VOID );

/* Add new texture to texture store system function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size:
 *       INT W, H;
 *   - number of terxture pixels color components:
 *       INT C;
 *   - pointer to pixels color data:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) added texture table number.
 */
INT PP6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );

/* Add texture image from file function.
 * ARGUMENTS:
 *   - texture image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) texture table index or -1 if error is occured.
 */
INT PP6_RndTexAddFromFile( CHAR *FileName );

/* Material store system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndMtlInit( VOID );

/* Material store system deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndMtlClose( VOID );

/* Add material function.
 * ARGUMENTS:
 *   - material data structure pointer:
 *       pp6MATERIAL *Mtl;
 * RETURNS:
 *   (INT) material table index or -1 if error is occured.
 */
INT PP6_RndMtlAdd( pp6MATERIAL *Mtl );

/* Material apply function.
 * ARGUMENTS:
 *   - material table index:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) apply result shader program identifier.
 */
INT PP6_RndMtlApply( INT MtlNo );

/* Get default material function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (pp6MATERIAL) default material.
 */
pp6MATERIAL PP6_RndMtlGetDef( VOID );

/* Get material pointer by materials table number function.
 * ARGUMENTS:
 *   - number of masterial at materials table:
 *       INT MtlNo;
 * RETURNS:
 *   (pp6MATERIAL *) material pointer.
 */
pp6MATERIAL * PP6_RndMtlGet( INT MtlNo );

/* Get material by name function.
 * ARGUMENTS:
 *   - material name to find:
 *       CHAR *Name;
 * RETURNS:
 *   (INT) found material table number.
 */
INT PP6_RndMtlGetByName( CHAR *Name );

/* Load font from .G3DF file function.
 * ARGUMENTS:
 *   - font file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL PP6_RndFntLoad( CHAR *FileName );

/* Init font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndFntInit( VOID );

/* Deinit font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndFntClose( CHAR *FileName );

/* Draw string function.
 * ARGUMENTS:
 *   - string to draw:
 *       CHAR *Str;
 *   - draw position:
 *       VEC Pos;
 *   = font size:
 *      FLT Size;
 * RETURNS: None.
 */
VOID PP6_RndFntDraw( CHAR *Str, VEC Pos, FLT Size );
#endif /* __rndres_h_ */

/* END OF 'rndres.h' FILE */
