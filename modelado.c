/*************************************************************************/
/*                                                                       */
/*   modelado.c                                                          */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/

#include "glut.h"
#include "glig.h"
#include "material.h"
#include "modelado.h"

/********************* ESCENA ILUMINACION ****************/

/******************************************************************************************/
/* Define un arco de la escena                                                            */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void ArcoSolid (void)
{
	glPushMatrix();
		glTranslatef(0.75,0.0,0.0);
		glScalef(0.2,1.0,0.2);
		igSolidRulo(10,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.75,0.0,0.0);
		glScalef(0.2,1.0,0.2);
		igSolidRulo(10,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0,1.0,0.0);
		glRotatef(90,0.0,0.0,1.0);
		glScalef(0.05,2.3,0.5);
		igSolidCube();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0,-0.98,0.0);
		glRotatef(90,0.0,0.0,1.0);
		glScalef(0.05,2.3,0.5);
		igSolidCube();
	glPopMatrix();
}

/******************************************************************************************/
/* Define los arcos de la escena                                                          */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void ArcosSolid (void)
{
	int i;

	glScalef(0.9,0.9,0.9);
	for(i=0;i<12;i++){
		glPushMatrix();
			glRotatef(i*360/12,0.0,1.0,0.0);
			glTranslatef(0.0,0.0,-2.0);
			glScalef(0.5,0.5,0.5);
			ArcoSolid();
		glPopMatrix();
	}
}

/******************************************************************************************/
/* Define el suelo de la escena                                                           */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void SueloSolid(void)
{
    glPushMatrix();
		glTranslatef(0.0,-0.5,0.0);
		glRotatef(360/48.0,0.0,1.0,0.0);
		glScalef(2.1,0.005,2.1);
		igSolidSemiSphere(10,50);
    glPopMatrix();
}

void SemiEsfera()
{
	glPushMatrix();
		glFrontFace(GL_CCW); // Defino sentido antihorario porque quiero ver las cara de dentro
							 // de la esfera que me van a recubrir la escena
		glScalef(10, 10, 10);
		igSolidSemiSphere(20,20);
		glFrontFace(GL_CW); // El resto de objetos se pintan en sentido horario
	glPopMatrix();
}

void ZonaCubos(x1, y1, z1, x2, y2, z2)
{
	//float xTemp = x1;
	//float yTemp = y1;
	//float zTemp = z1;

	float xTemp, yTemp, zTemp;
	float inc_x, inc_y, inc_z = 0.0;

	// Nos movemos a las coordenadas de inicio
	glTranslatef(x1, y1, z1);

	for (xTemp = x1; xTemp <= x2; xTemp += 1.0)
	{
		for (yTemp = y1; yTemp <= y2; yTemp += 1.0)
		{
			for (zTemp = z1; zTemp <= z2; zTemp += 1.0)
			{
				// Pintamos
				igSolidCube();

				// Nos movemos en el eje Z
				glTranslatef(0.0, 0.0, 1.0);

				// Guardamos el paso
				inc_z += 1.0;
			}

			// Retrocedemos en el eje Z lo que avanzamos antes
			glTranslatef(0.0, 0.0, -inc_z);

			// Nos movemos en el eje Y
			glTranslate(0.0, 1.0, 0.0);
		}

		// Nos movemos en el eje X
		glTranslatef(1.0, 0.0, 0.0);
	}
	// Nos movemos de vuelta al principio
	glTranslatef(-x2, -y2, -z2);

	/*while (xTemp <= x2 && yTemp <= y2 && zTemp <= z2)
	{
		if (xTemp <= 2)
		{
			xTemp += 1;

		}
		igSolidCube();
	}*/

}

/******************************************************************************************/
/* Crea la display list para la escena                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaEscena(void)
{
	escena = glGenLists (1);

	if (escena != 0)
	{
		glNewList (escena, GL_COMPILE);
		glPushMatrix();

			textura0();
			SueloSolid();
			textura4();
			//glScalef(20, 20, 20);
			SemiEsfera();
			//glColor3f(0.5, 0.5, 0.25);
			textura2();
			//glScalef(0, 0, 0);
			//igSolidSphere(20,20);
			//igSolidCube();
			//glTranslatef(1.0, 0.0, 0.0);
			//igSolidCube();
			ZonaCubos(0.0, 0.0, 0.0, 2.0, 0.0, 0.0);

		glPopMatrix();
		glEndList ();
	}
}