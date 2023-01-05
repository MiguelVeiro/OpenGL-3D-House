/*************************************************************************/
/*                                                                       */
/*                 glig.c LIBRERIA DE MODELADO GEOMETRICO	             */
/*                                                                       */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/

#include "glut.h"
#include <math.h>
#include <stdio.h>
#include "glig.h"

#define PI 3.1415926535897932
#define ALFA (0.5-v)*PI
#define BETA 2*PI*u
#define E 0.001
#define F 0.002

/************************* FUNCIONES BASICAS **********************************************/
/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada x de un punto en R3                                              */
/******************************************************************************************/
float xSuperQuadric (float u, float v, float R, float s1, float s2)
{
	float cosalfa, cosbeta, powcosalfa, powcosbeta;

	cosalfa = (float)cos(ALFA);
	cosbeta = (float)cos(BETA);

	if(cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa,s1);
	else
		powcosalfa =(float) - pow(- cosalfa,s1);

	if(cosbeta > 0.0)
		powcosbeta = (float)pow(cosbeta,s2);
	else
		powcosbeta = (float) - pow(- cosbeta,s2);

	return (R*powcosalfa*powcosbeta);

}


/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada y de un punto en R3                                              */
/******************************************************************************************/
float ySuperQuadric (float u, float v, float R, float s1, float s2)
{
	float sinalfa, powsinalfa;

	sinalfa = (float)sin(ALFA);

	if(sinalfa > 0.0)
		powsinalfa = (float)pow(sinalfa,s1);
	else
		powsinalfa = (float)- pow(- sinalfa,s1);

	return (R*powsinalfa);
}


/******************************************************************************************/
/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v)                    */
/*   de un espacio parametrico en R2                                                      */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La coordenada z de un punto en R3                                              */
/******************************************************************************************/
float zSuperQuadric(float u, float v, float R, float s1, float s2)
{
	float cosalfa, sinbeta, powcosalfa, powsinbeta;

	cosalfa = (float)cos(ALFA);
	sinbeta=(float)sin(BETA);

	if(cosalfa > 0.0)
		powcosalfa = (float)pow(cosalfa,s1);
	else
		powcosalfa=(float) - pow(- cosalfa,s1);

	if(sinbeta > 0.0)
		powsinbeta = (float)pow(sinbeta,s2);
	else
		powsinbeta = (float) - pow(- sinbeta,s2);

	return(R*powcosalfa*powsinbeta);
}


/******************************************************************************************/
/* Calcula la variacion en x para un incremento de u, derivada de x con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de x con u                                                        */
/******************************************************************************************/
float dxuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((xSuperQuadric(u+E,v,R,s1,s2)-xSuperQuadric(u-E,v,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de y con u                                                        */
/******************************************************************************************/
float dyuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((ySuperQuadric(u+E,v,R,s1,s2)-ySuperQuadric(u-E,v,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de u     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de z con u                                                        */
/******************************************************************************************/
float dzuSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((zSuperQuadric(u+E,v,R,s1,s2)-zSuperQuadric(u-E,v,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en x para un incremento de v, derivada de x con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de x con v                                                        */
/******************************************************************************************/
float dxvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((xSuperQuadric(u,v+E,R,s1,s2)-xSuperQuadric(u,v-E,R,s1,s2))/(2*E));
}


/******************************************************************************************/
/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de y con u                                                        */
/******************************************************************************************/
float dyvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((ySuperQuadric(u,v+E,R,s1,s2)-ySuperQuadric(u,v-E,R,s1,s2))/(2*E));
}

/******************************************************************************************/
/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de v     */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: La variacion de z con u                                                        */
/******************************************************************************************/
float dzvSuperQuadric(float u, float v, float R, float s1, float s2)
{
	return((zSuperQuadric(u,v+E,R,s1,s2)-zSuperQuadric(u,v-E,R,s1,s2))/(2*E));
}

/******************************************************************************************/
/* Calcula la componente x del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente x del vector normal                                                 */
/******************************************************************************************/
float nxSuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v<= E) v= F;
	if (v>= 1-E) v= 1-F;
	return(dyuSuperQuadric(u,v,R,s1,s2)*dzvSuperQuadric(u,v,R,s1,s2)-
		dyvSuperQuadric(u,v,R,s1,s2)*dzuSuperQuadric(u,v,R,s1,s2));
}

/******************************************************************************************/
/* Calcula la componente y del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente y del vector normal                                                 */
/******************************************************************************************/
float nySuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v<= E) v= F;
	if (v>= 1-E) v= 1-F;
	return(dxvSuperQuadric(u,v,R,s1,s2)*dzuSuperQuadric(u,v,R,s1,s2)-
		dxuSuperQuadric(u,v,R,s1,s2)*dzvSuperQuadric(u,v,R,s1,s2));
}

/******************************************************************************************/
/* Calcula la componente z del vector normal a la supercuadrica en (u,v)                  */
/* Parametros: float u --> Primera coordenada de un punto en R2                           */
/*             float v --> Segunda coordenada de un punto en R2                           */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1 --> Numero de divisiones en u                                     */
/*             float s2 --> Numero de divisiones en v                                     */
/* Salida: Componente z del vector normal                                                 */
/******************************************************************************************/
float nzSuperQuadric(float u, float v, float R, float s1, float s2)
{
	if (v<= E) v= F;
	if (v>= 1-E) v= 1-F;
	return(dxuSuperQuadric(u,v,R,s1,s2)*dyvSuperQuadric(u,v,R,s1,s2)-
		dxvSuperQuadric(u,v,R,s1,s2)*dyuSuperQuadric(u,v,R,s1,s2));
}





/********************** RUTINA DE DIBUJO *********************************/
/******************************************************************************************/
/* Crea una cuadrica segun los parametros que se le pasan                                 */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/*             float uMax --> Valor maximo que alcanza el parametro u                     */
/*             float vMax --> Valor maximo que alcanza el parametro v                     */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1, float s2 --> Definen la forma de la cuadrica                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igCreateQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2)
{ 
    float u, v, inc_u, inc_v; 
    float x, y, z; 
    int i;
	int j;

    v = 0.0; 
    u =0.0; 
    inc_u = uMax/pu; /* donde 10 es el número de puntos en u */ 
	inc_v = vMax/pv;

	for (j = 0; j <= pv; j++)
	{
		glBegin (GL_LINE_LOOP); 
			for (i= 0; i< pu; i++)
			{ 
				x= xSuperQuadric (u, v, R, s1, s2); 
				y= ySuperQuadric (u, v, R, s1, s2); 
				z= zSuperQuadric (u, v, R, s1, s2); 
				glVertex3f (x, y, z); 
				u= u+ inc_u; 
			} 
		glEnd(); 
		v = v + inc_v;
		u = 0.0f;
	}

	v = 0.0f;
	u = 0.0f;
	for (i = 0; i < pu; i++)
	{
		glBegin (GL_LINE_STRIP);
			for (j = 0; j <= pv; j++)
			{
				x= xSuperQuadric (u, v, R, s1, s2); 
				y= ySuperQuadric (u, v, R, s1, s2); 
				z= zSuperQuadric (u, v, R, s1, s2); 
				glVertex3f (x, y, z); 
				v = v + inc_v;
			}
		glEnd ();
		u = u + inc_u;
		v = 0.0f;
	}
}

/******************************************************************************************/
/* Crea una esfera a partir de las ecuaciones de la supercuadrica                         */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireSphere (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un rulo a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireRulo (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f);
}


/******************************************************************************************/
/* Crea un dado a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireDado (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f);
}


/******************************************************************************************/
/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica                     */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireSemiSphere (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un cono a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireCone (int pu, int pv)
{
	igCreateQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f);
}


/******************************************************************************************/
/* Dibuja un cono de arista unidad y centrado en el origen                                */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igWireCube (void)
{
	float vertices[8][3] = {{0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f},
							{0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f}};

	glBegin (GL_LINE_LOOP);
		glVertex3fv (vertices[0]);
		glVertex3fv (vertices[1]);
		glVertex3fv (vertices[2]);
		glVertex3fv (vertices[3]);
	glEnd ();

	glBegin (GL_LINE_LOOP);
		glVertex3fv (vertices[4]);
		glVertex3fv (vertices[5]);
		glVertex3fv (vertices[6]);
		glVertex3fv (vertices[7]);
	glEnd ();

	glBegin (GL_LINES);
		glVertex3fv (vertices[0]);
		glVertex3fv (vertices[4]);
		glVertex3fv (vertices[1]);
		glVertex3fv (vertices[5]);
		glVertex3fv (vertices[2]);
		glVertex3fv (vertices[6]);
		glVertex3fv (vertices[3]);
		glVertex3fv (vertices[7]);
	glEnd ();
}


/******************************************************************************************/
/* Crea una cuadrica segun los parametros que se le pasan                                 */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/*             float uMax --> Valor maximo que alcanza el parametro u                     */
/*             float vMax --> Valor maximo que alcanza el parametro v                     */
/*             float R --> Radio de la esfera envolvente                                  */
/*             float s1, float s2 --> Definen la forma de la cuadrica                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igCreateSolidQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2)
{ 
    float u, v, inc_u, inc_v; 
    float x, y, z; 
    float nx, ny, nz; 
    int i;
	int j;

    v = 0.0; 
    u =0.0; 
    inc_u = uMax/pu; /* donde 10 es el número de puntos en u */ 
	inc_v = vMax/pv;

	for (j = 0; j < pv; j++)
	{
		glBegin (GL_TRIANGLE_STRIP); 
			for (i= 0; i<= pu; i++)
			{ 
				glTexCoord2f (u, v);
				nx = nxSuperQuadric (u, v, R, s1, s2);
				ny = nySuperQuadric (u, v, R, s1, s2);
				nz = nzSuperQuadric (u, v, R, s1, s2);
				glNormal3f (nx, ny, nz);
				x= xSuperQuadric (u, v, R, s1, s2); 
				y= ySuperQuadric (u, v, R, s1, s2); 
				z= zSuperQuadric (u, v, R, s1, s2); 
				glVertex3f (x, y, z);
				
				glTexCoord2f (u, v+inc_v);
				nx = nxSuperQuadric (u, v+inc_v, R, s1, s2);
				ny = nySuperQuadric (u, v+inc_v, R, s1, s2);
				nz = nzSuperQuadric (u, v+inc_v, R, s1, s2);
				glNormal3f (nx, ny, nz);
				x= xSuperQuadric (u, v+inc_v, R, s1, s2); 
				y= ySuperQuadric (u, v+inc_v, R, s1, s2); 
				z= zSuperQuadric (u, v+inc_v, R, s1, s2); 
				glVertex3f (x, y, z); 
				u= u+ inc_u; 
			} 
		glEnd(); 
		v = v + inc_v;
		u = 0.0f;
	}
}

/******************************************************************************************/
/* Crea una esfera a partir de las ecuaciones de la supercuadrica                         */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidSphere (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un rulo a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidRulo (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f);
}


/******************************************************************************************/
/* Crea un dado a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidDado (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f);
}


/******************************************************************************************/
/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica                     */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidSemiSphere (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f);
}


/******************************************************************************************/
/* Crea un cono a partir de las ecuaciones de la supercuadrica                            */
/* Parametros: int pu --> Numero de divisiones del parametro u                            */
/*             int pv --> Numero de divisiones del parametro v                            */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidCone (int pu, int pv)
{
	igCreateSolidQuadricObject (pu, pv, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f);
}


/******************************************************************************************/
/* Dibuja un cono de arista unidad y centrado en el origen                                */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void igSolidCube (void)
{
	float vertices[8][3] = 
	{
		{0.5f, 0.5f, 0.5f},		// 0 delante	superior	derecha
		{0.5f, 0.5f, -0.5f},	// 1 atrás		superior	derecha
		{-0.5f, 0.5f, -0.5f},	// 2 atrás		superior	izquierda
		{-0.5f, 0.5f, 0.5f},	// 3 delante	superior	izquierda
		{0.5f, -0.5f, 0.5f},	// 4 delante	inferior	derecha
		{0.5f, -0.5f, -0.5f},	// 5 atrás		inferior	derecha
		{-0.5f, -0.5f, -0.5f},	// 6 atrás		inferior	izquierda
		{-0.5f, -0.5f, 0.5f}	// 7 delante	inferior	izquierda
	};

	// Creación cara derecha
	glBegin (GL_TRIANGLE_STRIP);
		glNormal3f (1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0, 1.0);		
		glVertex3fv (vertices[4]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv (vertices[0]);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv (vertices[5]);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv (vertices[1]);

		//Finalizar cubo
		/*glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[0]);*/
	glEnd ();

	// Creación cara izquierda
	glBegin(GL_TRIANGLE_STRIP);
		glNormal3f (0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv (vertices[6]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv (vertices[2]);
		glNormal3f (-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv (vertices[7]);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv (vertices[3]);
	glEnd();

	// Creación cara delantera
	glBegin(GL_TRIANGLE_STRIP);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(vertices[0]);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv(vertices[4]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(vertices[3]);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(vertices[7]);
	glEnd();

	// Creación cara trasera
	glBegin(GL_TRIANGLE_STRIP);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(vertices[2]);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv(vertices[6]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(vertices[1]);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(vertices[5]);
	glEnd();

	// Creación cara superior
	glBegin(GL_TRIANGLE_STRIP);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(vertices[1]);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv(vertices[0]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(vertices[2]);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(vertices[3]);
	glEnd();

	// Creación cara inferior
	glBegin (GL_TRIANGLE_STRIP);
		glNormal3f (0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv (vertices[4]);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv (vertices[5]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv (vertices[7]);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv (vertices[6]);
	glEnd ();
}