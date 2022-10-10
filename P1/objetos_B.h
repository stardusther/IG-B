//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#define GL_SILENCE_DEPRECATION

#if defined(__APPLE__) // Para que funcione en apple
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#endif

#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE = 5000;

//*************************************************************************
// clase punto
//*************************************************************************

class puntos3D
{
public:
	puntos3D();
	void draw_puntos(float r, float g, float b, int grosor);
	
	vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class triangulos3D : public puntos3D
{
public:
	triangulos3D();
	void draw_lineas(float r, float g, float b, int grosor);
	void draw_solido(float r, float g, float b);
	void draw_solido_colores();
	void inicializar_colores(); // Inicializa los colores de las caras

	//vector<_vertex3f> vertices; // vector de vertices
	vector<_vertex3i> caras;
	vector<_vertex3f> colores; // Vector para almacenar los colores
};

//*************************************************************************
// clase cubo
//*************************************************************************

class cubo : public triangulos3D
{
public:
	cubo(float tam = 0.5);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class piramide : public triangulos3D
{
public:
	piramide(float tam = 0.5, float al = 1.0);
};
