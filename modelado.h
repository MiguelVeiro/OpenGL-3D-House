/*************************************************************************/
/*                                                                       */
/*   modelado.h												             */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

#ifndef MODELADO_H
#define MODELADO_H

/* Identificador para la display list de la escena */
GLuint escena;

/* Define un arco de la escena */
void ArcoSolid (void);

/* Define los arcos de la escena */
void ArcosSolid (void);

/* Define el suelo de la escena */
void SueloSolid(void);

/* Crea la display list para la escena */
void CreaEscenaIluminacion (void);


#endif