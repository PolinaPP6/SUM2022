/* FILE NAME  : rndres.c
 * PROGRAMMER : PP6
 * LAST UPDATE: 14.06.2022
 * PURPOSE    : 3D animation project.
 *              Render subsystem implementation module.
 *              Render system resourses handle module.
 */

#include "rndres.h"

/* Resourses system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndResInit( VOID )
{
  PP6_RndShdInit();
} /* End of 'PP6_RndResInit' function */

/* Resourses system deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PP6_RndResClose( VOID )
{
  PP6_RndShdClose();
} /* End of 'PP6_RndResClose' function */

/* END OF 'rndres.c' FILE */
