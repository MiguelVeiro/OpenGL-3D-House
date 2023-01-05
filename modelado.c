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

void zonaCubos(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float xTemp = 0.0;
	float yTemp = 0.0;
	float zTemp = 0.0;

	float inc_x = 0.0;
	float inc_y = 0.0;
	float inc_z = 0.0;

	// Nos movemos a las coordenadas de inicio
	glTranslatef(x1, y1, z1);
	
	// Nos vamos moviendo por el eje X
	for (xTemp = x1; xTemp <= x2; xTemp = xTemp + 1.0)
	{
		// Reseteamos los pasos dados en el eje Y
		inc_y = 0.0;

		for (yTemp = y1; yTemp <= y2; yTemp = yTemp + 1.0)
		{
			// Dibujamos el cubo
			igSolidCube();

			// Avanzamos una posición en el eje Y
			glTranslatef(0.0, 1.0, 0.0);

			// Anotamos el paso en el eje Y
			inc_y += 1.0;
		}

		// Deshacemos el incremento en el eje Y
		glTranslatef(0.0, -inc_y, 0.0);

		// Avanzamos una posición en el eje X
		glTranslatef(1.0, 0.0, 0.0);

		// Anotamos el paso en el eje X
		inc_x += 1.0;
	}
	// Deshacemos el incremento en el eje X
	glTranslatef(-inc_x, 0.0, 0.0);

	// Deshacemos el incremento inicial, para volver al origen
	glTranslatef(-x1, -y1, -z1);
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

			glScalef(0.2, 0.2, 0.2);
			textura0();
			SueloSolid();
			textura4();
			//glScalef(20, 20, 20);
			//SemiEsfera();
			//glColor3f(0.5, 0.5, 0.25);
			textura4();
			//glScalef(0, 0, 0);
			//igSolidSphere(20,20);
			//igSolidCube();
			//glTranslatef(1.0, 0.0, 0.0);
			//igSolidCube();
			zonaCubos(1.0, 0.0, 0.0, 1.0, 2.0, 0.0);
			zonaCubos(10.0, 0.0, 0.0, 20.0, 0.0, 0.0);
			textura0();
			igSolidCube();

		glPopMatrix();
		glEndList ();
	}
}