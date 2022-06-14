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

/* Shaders stock maximum size */
#define PP6_MAX_SHADERS 30

/* Array of shaders */
extern pp6SHADER PP6_RndShaders[PP6_MAX_SHADERS];
/* Shadres array store size */
extern INT PP6_RndShadersSize;

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



#endif /* __rndres_h_ */

/* END OF 'rndres.h' FILE */
