/*************************************************************************/
/*                                                                       */
/*                 glig.h LIBRERIA DE MODELADO GEOMETRICO	             */
/*                                                                       */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/



/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v) */
/*   de un espacio parametrico en R2 */
float xSuperQuadric(float u, float v, float R, float s1, float s2);

/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v) */
/*   de un espacio parametrico en R2 */
float ySuperQuadric(float u, float v, float R, float s1, float s2);

/* Devuelve la coordenada de un punto en R3 a partir de un punto (u,v) */
/*   de un espacio parametrico en R2 */
float zSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en x para un incremento de u, derivada de x con respecto de u */
float dxuSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de u */
float dyuSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de u */
float dzuSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en x para un incremento de v, derivada de x con respecto de v */
float dxvSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en y para un incremento de u, derivada de y con respecto de v */
float dyvSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la variacion en z para un incremento de u, derivada de z con respecto de v */
float dzvSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la componente x del vector normal a la supercuadrica en (u,v) */
float nxSuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la componente y del vector normal a la supercuadrica en (u,v) */
float nySuperQuadric(float u, float v, float R, float s1, float s2);

/* Calcula la componente z del vector normal a la supercuadrica en (u,v) */
float nzSuperQuadric(float u, float v, float R, float s1, float s2);


/* Crea una cuadrica segun los parametros que se le pasan */
void igCreateQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2);

/* Crea una esfera a partir de las ecuaciones de la supercuadrica */
void igWireSphere (int pu, int pv);

/* Crea un rulo a partir de las ecuaciones de la supercuadrica */
void igWireRulo (int pu, int pv);

/* Crea un dado a partir de las ecuaciones de la supercuadrica */
void igWireDado (int pu, int pv);

/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica */
void igWireSemiSphere (int pu, int pv);

/* Crea un cono a partir de las ecuaciones de la supercuadrica */
void igWireCone (int pu, int pv);

/* Dibuja un cuadrado de arista unidad y centrado en el origen */
void igWireCube (void);

/* Crea una cuadrica segun los parametros que se le pasan */
void igCreateSolidQuadricObject (int pu, int pv, float uMax, float vMax, float R, float s1, float s2);


/* Crea una esfera a partir de las ecuaciones de la supercuadrica */
void igSolidSphere (int pu, int pv);

/* Crea un rulo a partir de las ecuaciones de la supercuadrica */
void igSolidRulo (int pu, int pv);

/* Crea un dado a partir de las ecuaciones de la supercuadrica */
void igSolidDado (int pu, int pv);

/* Crea una semiesfera a partir de las ecuaciones de la supercuadrica */
void igSolidSemiSphere (int pu, int pv);

/* Crea un cono a partir de las ecuaciones de la supercuadrica */
void igSolidCone (int pu, int pv);

/* Dibuja un cuadrado de arista unidad y centrado en el origen */
void igSolidCube (void);