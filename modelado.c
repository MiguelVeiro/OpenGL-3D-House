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
	glTranslatef(x1, y1, -z1);
	
	// Nos vamos moviendo por el eje X
	for (xTemp = x1; xTemp <= x2; xTemp = xTemp + 1.0)
	{
		// Reseteamos los pasos dados en el eje Y
		inc_y = 0.0;

		for (yTemp = y1; yTemp <= y2; yTemp = yTemp + 1.0)
		{
			// Reseteamos los pasos dados en el eje Z
			inc_z = 0.0;

			for (zTemp = z1; zTemp <= z2; zTemp = zTemp + 1.0)
			{
				// Dibujamos el cubo
				igSolidCube();

				// Avanzamos una posición en el eje Z (hacia atrás)
				glTranslatef(0.0, 0.0, -1.0);

				// Anotamos el paso en el eje Z
				inc_z -= 1.0;
			}

			// Deshacemos el decremento en el eje Z
			glTranslatef(0.0, 0.0, -inc_z);

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
	glTranslatef(-x1, -y1, z1);
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

			//SemiEsfera();
			glScalef(0.3, 0.3, 0.3);
			textura0();
			SueloSolid();

			// Bloque del principio
			textura0();
			zonaCubos(
				1.0, 0.0, 0.0,
				11.0, 1.0, 0.0
			);
			zonaCubos(
				1.0, 0.0, 1.0,
				1.0, 1.0, 2.0
			);
			zonaCubos(
				11.0, 0.0, 1.0,
				11.0, 1.0, 2.0
			);

			// Jardín abajo
			textura3();
			zonaCubos(
				2.0, 1.0, 1.0,
				10.0, 1.0, 2.0
			);

			// Zona entrada
			textura0();
			zonaCubos(
				16.0, 0.0, 2.0,
				16.0, 0.0, 3.0
			);
			zonaCubos(
				20.0, 0.0, 2.0,
				20.0, 0.0, 3.0
			);
			zonaCubos(
				21.0, 0.0, 3.0,
				21.0, 0.0, 3.0
			);
			zonaCubos(
				21.0, 0.0, 4.0,
				22.0, 0.0, 7.0
			);
			zonaCubos(
				20.0, 0.0, 7.0,
				20.0, 0.0, 7.0
			);
			zonaCubos(
				15.0, 0.0, 7.0,
				15.0, 0.0, 7.0
			);
			zonaCubos(
				15.0, 0.0, 3.0,
				15.0, 0.0, 3.0
			);
			textura1();
			zonaCubos(
				15.0, 0.0, 4.0,
				20.0, 0.0, 6.0
			);
			zonaCubos(
				17.0, 0.0, 3.0,
				19.0, 0.0, 3.0
			);

			//Piscina
			textura0();
			zonaCubos(
				14.0, 0.0, 6.0,
				14.0, 0.0, 18.0
			);
			zonaCubos(
				15.0, 0.0, 18.0,
				22.0, 0.0, 18.0
			);
			zonaCubos(
				21.0, 0.0, 8.0,
				22.0, 0.0, 17.0
			);

			// Pared entrada y escaleras
			zonaCubos(
				1.0, 0.0, 3.0,
				14.0, 1.0, 3.0
			);
			zonaCubos(
				1.0, 2.0, 3.0,
				3.0, 4.0, 3.0
			);
			zonaCubos(
				4.0, 4.0, 3.0,
				8.0, 4.0, 3.0
			);
			zonaCubos(
				7.0, 2.0, 3.0,
				10.0, 3.0, 3.0
			);
			zonaCubos(
				11.0, 2.0, 3.0,
				12.0, 2.0, 3.0
			);

			// Pared lateral izquierda piso 0
			zonaCubos(
				1.0, 0.0, 4.0,
				1.0, 4.0, 18.0
			);

			// Pared debajo escaleras principales
			zonaCubos(
				10.0, 1.0, 4.0,
				10.0, 2.0, 5.0
			);

			// Suelo lana piso 0
			textura2();
			zonaCubos(
				2.0, 0.0, 4.0,
				7.0, 0.0, 9.0
			);
			zonaCubos(
				8.0, 0.0, 4.0,
				9.0, 0.0, 5.0
			);
			zonaCubos(
				8.0, 0.0, 7.0,
				8.0, 0.0, 9.0
			);
			zonaCubos(
				2.0, 0.0, 10.0,
				6.0, 0.0, 10.0
			);

			// Pared pegada a escaleras y baño
			textura0();
			zonaCubos(
				8.0, 1.0, 6.0,
				9.0, 4.0, 6.0
			);
			zonaCubos(
				10.0, 1.0, 6.0,
				13.0, 2.0, 6.0
			);
			zonaCubos(
				13.0, 3.0, 6.0,
				13.0, 3.0, 6.0
			);
			zonaCubos(
				11.0, 3.0, 6.0,
				11.0, 3.0, 6.0
			);
			zonaCubos(
				10.0, 4.0, 6.0,
				13.0, 4.0, 6.0
			);

			// Pared lado piscina
			zonaCubos(
				10.0, 4.0, 6.0,
				13.0, 4.0, 6.0
			);

			// Pared que da a la piscina
			zonaCubos(
				13.0, 1.0, 7.0,
				13.0, 1.0, 7.0
			);
			zonaCubos(
				13.0, 4.0, 7.0,
				13.0, 4.0, 7.0
			);
			zonaCubos(
				13.0, 1.0, 8.0,
				13.0, 4.0, 9.0
			);
			zonaCubos(
				13.0, 1.0, 10.0,
				13.0, 2.0, 18.0
			);
			zonaCubos(
				13.0, 3.0, 11.0,
				13.0, 3.0, 12.0
			);
			zonaCubos(
				13.0, 3.0, 18.0,
				13.0, 3.0, 18.0
			);
			textura1();
			zonaCubos(
				13.0, 3.0, 14.0,
				13.0, 3.0, 14.0
			);
			zonaCubos(
				13.0, 3.0, 17.0,
				13.0, 3.0, 17.0
			);

			// Suelo baño
			zonaCubos(
				9.0, 0.0, 8.0,
				9.0, 0.0, 8.0
			);
			zonaCubos(
				10.0, 0.0, 7.0,
				12.0, 0.0, 9.0
			);

			// Pared y marco baño
			textura0();
			zonaCubos(
				9.0, 1.0, 7.0,
				9.0, 3.0, 7.0
			);
			zonaCubos(
				9.0, 1.0, 9.0,
				9.0, 3.0, 9.0
			);
			zonaCubos(
				9.0, 3.0, 8.0,
				9.0, 3.0, 8.0
			);
			zonaCubos(
				10.0, 1.0, 10.0,
				12.0, 2.0, 10.0
			);
			zonaCubos(
				10.0, 3.0, 10.0,
				11.0, 3.0, 10.0
			);
			zonaCubos(
				9.0, 1.0, 10.0,
				9.0, 3.0, 10.0
			);

			// Paredes salón
			zonaCubos(
				7.0, 1.0, 10.0,
				8.0, 3.0, 10.0
			);
			zonaCubos(
				5.0, 1.0, 11.0,
				6.0, 3.0, 11.0
			);
			zonaCubos(
				2.0, 1.0, 11.0,
				2.0, 3.0, 11.0
			);
			zonaCubos(
				3.0, 3.0, 11.0,
				4.0, 3.0, 11.0
			);

			// Suelo zona escaleras bajo
			textura1();
			zonaCubos(
				2.0, 0.0, 11.0,
				12.0, 0.0, 17.0
			);

			// Marco puerta separadora abajo
			textura0();
			zonaCubos(
				7.0, 1.0, 11.0,
				7.0, 3.0, 13.0
			);
			zonaCubos(
				7.0, 1.0, 16.0,
				7.0, 3.0, 17.0
			);
			zonaCubos(
				7.0, 3.0, 14.0,
				7.0, 3.0, 15.0
			);

			// Pared atrás de todo piso 0 + pared escaleras
			zonaCubos(
				2.0, 0.0, 18.0,
				13.0, 5.0, 18.0
			);
			zonaCubos(
				2.0, 1.0, 17.0,
				6.0, 4.0, 17.0
			);

			// Suelo piso 1
			textura1();
			zonaCubos(
				2.0, 4.0, 4.0,
				7.0, 4.0, 7.0
			);
			zonaCubos(
				7.0, 4.0, 7.0,
				12.0, 4.0, 9.0
			);
			textura0();
			zonaCubos(
				3.0, 4.0, 8.0,
				5.0, 4.0, 8.0
			);
			zonaCubos(
				6.0, 4.0, 9.0,
				6.0, 4.0, 10.0
			);
			zonaCubos(
				7.0, 4.0, 10.0,
				23.0, 4.0, 10.0
			);
			zonaCubos(
				13.0, 4.0, 11.0,
				13.0, 4.0, 17.0
			);
			zonaCubos(
				23.0, 4.0, 11.0,
				23.0, 4.0, 18.0
			);
			zonaCubos(
				15.0, 4.0, 18.0,
				22.0, 4.0, 18.0
			);
			textura1();
			zonaCubos(
				2.0, 4.0, 9.0,
				5.0, 4.0, 15.0
			);
			zonaCubos(
				6.0, 4.0, 11.0,
				12.0, 4.0, 15.0
			);
			zonaCubos(
				7.0, 4.0, 16.0,
				12.0, 4.0, 17.0
			);
			zonaCubos(
				14.0, 4.0, 11.0,
				22.0, 4.0, 17.0
			);

			// Pilares piscina
			zonaCubos(
				22.0, 1.0, 10.0,
				22.0, 3.0, 10.0
			);
			zonaCubos(
				22.0, 1.0, 17.0,
				22.0, 3.0, 17.0
			);

			// Jardín exterior
			textura3();
			zonaCubos(
				23.0, 0.0, 5.0,
				23.0, 1.0, 19.0
			);
			zonaCubos(
				13.0, 0.0, 19.0,
				22.0, 1.0, 19.0
			);
			zonaCubos(
				2.0, 0.0, 19.0,
				6.0, 1.0, 19.0
			);
			zonaCubos(
				0.0, 0.0, 4.0,
				0.0, 1.0, 8.0
			);
			zonaCubos(
				0.0, 0.0, 11.0,
				0.0, 1.0, 15.0
			);

			// Pared final primer piso
			textura0();
			zonaCubos(
				13.0, 5.0, 18.0,
				14.0, 7.0, 18.0
			);
			zonaCubos(
				5.0, 6.0, 18.0,
				9.0, 6.0, 18.0
			);
			zonaCubos(
				3.0, 7.0, 18.0,
				9.0, 7.0, 18.0
			);
			zonaCubos(
				14.0, 4.0, 18.0,
				14.0, 4.0, 18.0
			);
			textura1();
			zonaCubos(
				15.0, 5.0, 17.0,
				22.0, 7.0, 17.0
			);

			// Pared derecha primer piso
			zonaCubos(
				22.0, 5.0, 11.0,
				22.0, 7.0, 12.0
			);
			zonaCubos(
				22.0, 5.0, 13.0,
				22.0, 5.0, 15.0
			);
			zonaCubos(
				22.0, 5.0, 16.0,
				22.0, 7.0, 16.0
			);

			// Pared frontal primer piso
			zonaCubos(
				15.0, 5.0, 11.0,
				16.0, 7.0, 11.0
			);
			zonaCubos(
				17.0, 5.0, 11.0,
				20.0, 5.0, 11.0
			);
			zonaCubos(
				21.0, 5.0, 11.0,
				22.0, 7.0, 11.0
			);

			// Pilares primer piso
			textura0();
			zonaCubos(
				2.0, 5.0, 8.0,
				2.0, 7.0, 8.0
			);
			zonaCubos(
				6.0, 5.0, 8.0,
				6.0, 7.0, 8.0
			);
			zonaCubos(
				11.0, 5.0, 10.0,
				11.0, 7.0, 10.0
			);
			zonaCubos(
				14.0, 5.0, 11.0,
				14.0, 7.0, 11.0
			);

			// Pared izquierda primer piso
			zonaCubos(
				2.0, 5.0, 11.0,
				2.0, 7.0, 18.0
			);

			// Suelo segundo piso
			textura1();
			zonaCubos(
				2.0, 8.0, 8.0,
				6.0, 8.0, 16.0
			);
			zonaCubos(
				7.0, 8.0, 8.0,
				10.0, 8.0, 17.0
			);
			zonaCubos(
				11.0, 8.0, 8.0,
				11.0, 8.0, 9.0
			);

			// Pared izquierda segundo piso
			textura0();
			zonaCubos(
				1.0, 8.0, 7.0,
				1.0, 12.0, 9.0
			);
			zonaCubos(
				1.0, 8.0, 10.0,
				1.0, 9.0, 11.0
			);
			zonaCubos(
				1.0, 12.0, 10.0,
				1.0, 12.0, 11.0
			);
			zonaCubos(
				1.0, 8.0, 12.0,
				1.0, 12.0, 18.0
			);

			// Marco suelo segundo piso
			zonaCubos(
				2.0, 8.0, 7.0,
				12.0, 8.0, 7.0
			);
			zonaCubos(
				11.0, 8.0, 10.0,
				18.0, 8.0, 10.0
			);
			zonaCubos(
				11.0, 8.0, 11.0,
				11.0, 8.0, 17.0
			);
			zonaCubos(
				2.0, 8.0, 18.0,
				23.0, 8.0, 18.0
			);
			zonaCubos(
				19.0, 8.0, 10.0,
				23.0, 8.0, 17.0
			);
			zonaCubos(
				12.0, 8.0, 8.0,
				12.0, 8.0, 9.0
			);

			// Jardín superior
			textura3();
			zonaCubos(
				12.0, 8.0, 11.0,
				18.0, 8.0, 17.0
			);

			// Pared trasera segundo piso
			textura0();
			zonaCubos(
				2.0, 9.0, 18.0,
				3.0, 12.0, 18.0
			);
			zonaCubos(
				4.0, 9.0, 18.0,
				6.0, 9.0, 18.0
			);
			zonaCubos(
				4.0, 11.0, 18.0,
				6.0, 12.0, 18.0
			);
			zonaCubos(
				7.0, 9.0, 18.0,
				7.0, 12.0, 18.0
			);
			zonaCubos(
				8.0, 9.0, 18.0,
				9.0, 9.0, 18.0
			);
			zonaCubos(
				8.0, 11.0, 18.0,
				9.0, 12.0, 18.0
			);
			zonaCubos(
				10.0, 9.0, 18.0,
				11.0, 12.0, 18.0
			);

			// Separacion libreria segundo piso
			zonaCubos(
				4.0, 9.0, 15.0,
				7.0, 9.0, 15.0
			);
			zonaCubos(
				4.0, 11.0, 15.0,
				7.0, 11.0, 15.0
			);
			zonaCubos(
				7.0, 9.0, 16.0,
				7.0, 9.0, 17.0
			);
			zonaCubos(
				7.0, 11.0, 16.0,
				7.0, 11.0, 17.0
			);

			// Pared y repisa de madera segundo piso frontal
			textura1();
			zonaCubos(
				2.0, 9.0, 8.0,
				3.0, 11.0, 8.0
			);
			zonaCubos(
				4.0, 9.0, 8.0,
				11.0, 9.0, 8.0
			);
			zonaCubos(
				11.0, 9.0, 9.0,
				11.0, 11.0, 13.0
			);

			// Marco jardín superior
			zonaCubos(
				12.0, 9.0, 11.0,
				18.0, 9.0, 11.0
			);
			zonaCubos(
				11.0, 9.0, 17.0,
				18.0, 9.0, 17.0
			);
			zonaCubos(
				11.0, 10.0, 17.0,
				11.0, 11.0, 17.0
			);

			// Suelo tercer piso
			textura0();
			zonaCubos(
				2.0, 12.0, 7.0,
				7.0, 12.0, 15.0
			);
			zonaCubos(
				8.0, 12.0, 7.0,
				11.0, 12.0, 18.0
			);
			zonaCubos(
				2.0, 12.0, 17.0,
				7.0, 12.0, 17.0
			);

			// Pared derecha tercer piso
			zonaCubos(
				12.0, 12.0, 7.0,
				12.0, 16.0, 8.0
			);
			zonaCubos(
				12.0, 12.0, 8.0,
				12.0, 12.0, 18.0
			);
			zonaCubos(
				12.0, 16.0, 9.0,
				12.0, 16.0, 18.0
			);
			zonaCubos(
				12.0, 13.0, 10.0,
				12.0, 15.0, 11.0
			);
			zonaCubos(
				12.0, 13.0, 13.0,
				12.0, 15.0, 14.0
			);
			zonaCubos(
				12.0, 13.0, 16.0,
				12.0, 15.0, 18.0
			);

			// Pared frontal tercer piso
			textura1();
			zonaCubos(
				3.0, 13.0, 8.0,
				11.0, 13.0, 8.0
			);
			zonaCubos(
				10.0, 14.0, 8.0,
				11.0, 15.0, 8.0
			);

			// Pared izquierda tercer piso
			zonaCubos(
				2.0, 13.0, 8.0,
				2.0, 15.0, 11.0
			);
			zonaCubos(
				2.0, 13.0, 12.0,
				2.0, 13.0, 17.0
			);

			// Pared atras tercer piso
			zonaCubos(
				3.0, 13.0, 17.0,
				11.0, 13.0, 17.0
			);
			zonaCubos(
				11.0, 14.0, 17.0,
				11.0, 15.0, 17.0
			);

			// Techo tercer piso
			textura0();
			zonaCubos(
				1.0, 16.0, 7.0,
				11.0, 16.0, 18.0
			);

		glPopMatrix();
		glEndList ();
	}
}