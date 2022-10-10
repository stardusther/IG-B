//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B.h"

//*************************************************************************
// _puntos3D
//*************************************************************************

puntos3D::puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
	glPointSize(grosor);
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	for (int i = 0; i < vertices.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[i]);
	}
	glEnd();
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

triangulos3D::triangulos3D()
{
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void triangulos3D::draw_lineas(float r, float g, float b, int grosor)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(grosor);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void triangulos3D::draw_solido(float r, float g, float b)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

// Inicializar vector de colores con un color para cada cara del objeto
void triangulos3D::inicializar_colores()
{
	colores.resize(caras.size());
	for (int i = 0; i < caras.size(); i++)
	{
		colores[i].x = (rand() % 100) / 100.0;
		colores[i].y = (rand() % 100) / 100.0;
		colores[i].z = (rand() % 100) / 100.0;
	}
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************
// Función que dibuja en modo sólido con un color diferente para cada cara triangular 
void triangulos3D::draw_solido_colores()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		glColor3fv((GLfloat *)&colores[i]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// clase cubo
//*************************************************************************

cubo::cubo(float tam)
{
	// vertices
	vertices.resize(8);
	vertices[0].x = -tam;
	vertices[0].y = -tam;
	vertices[0].z = tam;
	vertices[1].x = tam;
	vertices[1].y = -tam;
	vertices[1].z = tam;
	vertices[2].x = tam;
	vertices[2].y = tam;
	vertices[2].z = tam;
	vertices[3].x = -tam;
	vertices[3].y = tam;
	vertices[3].z = tam;
	vertices[4].x = -tam;
	vertices[4].y = -tam;
	vertices[4].z = -tam;
	vertices[5].x = tam;
	vertices[5].y = -tam;
	vertices[5].z = -tam;
	vertices[6].x = tam;
	vertices[6].y = tam;
	vertices[6].z = -tam;
	vertices[7].x = -tam;
	vertices[7].y = tam;
	vertices[7].z = -tam;

	// caras
	caras.resize(12);
	caras[0]._0 = 0;	caras[1]._0 = 2;	caras[2]._0 = 1;	caras[3]._0 = 6;	caras[4]._0 = 5;	caras[5]._0 = 7;
	caras[0]._1 = 1;	caras[1]._1 = 3;	caras[2]._1 = 5;	caras[3]._1 = 2;	caras[4]._1 = 4;	caras[5]._1 = 6;
	caras[0]._2 = 2;	caras[1]._2 = 0;	caras[2]._2 = 6;	caras[3]._2 = 1;	caras[4]._2 = 7;	caras[5]._2 = 5;
	
	
	caras[6]._0 = 4;	caras[7]._0 = 3;	caras[8]._0 = 3;	caras[9]._0 = 6;	caras[10]._0 = 4;	caras[11]._0 = 1;
	caras[6]._1 = 0;	caras[7]._1 = 7;	caras[8]._1 = 2;	caras[9]._1 = 7;	caras[10]._1 = 5;	caras[11]._1 = 0;
	caras[6]._2 = 3;	caras[7]._2 = 4;	caras[8]._2 = 6;	caras[9]._2 = 3;	caras[10]._2 = 1;	caras[11]._2 = 4;

}

//*************************************************************************
// clase piramide
//*************************************************************************

piramide::piramide(float tam, float al)
{

	// vertices
	vertices.resize(5);
	vertices[0].x = -tam;
	vertices[0].y = 0;
	vertices[0].z = tam;
	vertices[1].x = tam;
	vertices[1].y = 0;
	vertices[1].z = tam;
	vertices[2].x = tam;
	vertices[2].y = 0;
	vertices[2].z = -tam;
	vertices[3].x = -tam;
	vertices[3].y = 0;
	vertices[3].z = -tam;
	vertices[4].x = 0;
	vertices[4].y = al;
	vertices[4].z = 0;

	caras.resize(6);
	caras[0]._0 = 0;
	caras[0]._1 = 1;
	caras[0]._2 = 4;
	caras[1]._0 = 1;
	caras[1]._1 = 2;
	caras[1]._2 = 4;
	caras[2]._0 = 2;
	caras[2]._1 = 3;
	caras[2]._2 = 4;
	caras[3]._0 = 3;
	caras[3]._1 = 0;
	caras[3]._2 = 4;
	caras[4]._0 = 3;
	caras[4]._1 = 1;
	caras[4]._2 = 0;
	caras[5]._0 = 3;
	caras[5]._1 = 2;
	caras[5]._2 = 1;
}
