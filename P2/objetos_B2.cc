//**************************************************************************
// Práctica 2
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
	int i;
	glPointSize(grosor);
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	for (i = 0; i < vertices.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[i]);
	}
	glEnd();
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(grosor);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < caras.size(); i++)
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

void _triangulos3D::draw_solido(float r, float g, float b)
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
void _triangulos3D::inicializar_colores()
{
	colores.resize(caras.size());
	for (int i = 0; i < caras.size(); i++)
	{
		colores[i].x= (rand() % 100) / 100.0;
		colores[i].y = (rand() % 100) / 100.0;
		colores[i].z = (rand() % 100) / 100.0;
	}
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************
// Función que dibuja en modo sólido con un color diferente para cada cara triangular
void _triangulos3D::draw_solido_colores()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		// Recuperar el color de la cara
		glColor3fv((GLfloat *)&colores[i]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]); // Asignar colores a los vértices de la cara
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
	switch (modo)
	{
	case POINTS:
		draw_puntos(r, g, b, grosor);
		break;
	case EDGES:
		draw_aristas(r, g, b, grosor);
		break;
	case SOLID:
		draw_solido(r, g, b);
		break;
	case SOLID_COLORS:
		draw_solido_colores();
		break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
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
	caras[0]._0 = 0;
	caras[1]._0 = 2;
	caras[2]._0 = 1;
	caras[3]._0 = 6;
	caras[4]._0 = 5;
	caras[5]._0 = 7;
	caras[0]._1 = 1;
	caras[1]._1 = 3;
	caras[2]._1 = 5;
	caras[3]._1 = 2;
	caras[4]._1 = 4;
	caras[5]._1 = 6;
	caras[0]._2 = 2;
	caras[1]._2 = 0;
	caras[2]._2 = 6;
	caras[3]._2 = 1;
	caras[4]._2 = 7;
	caras[5]._2 = 5;

	caras[6]._0 = 4;
	caras[7]._0 = 3;
	caras[8]._0 = 3;
	caras[9]._0 = 6;
	caras[10]._0 = 4;
	caras[11]._0 = 1;
	caras[6]._1 = 0;
	caras[7]._1 = 7;
	caras[8]._1 = 2;
	caras[9]._1 = 7;
	caras[10]._1 = 5;
	caras[11]._1 = 0;
	caras[6]._2 = 3;
	caras[7]._2 = 4;
	caras[8]._2 = 6;
	caras[9]._2 = 3;
	caras[10]._2 = 1;
	caras[11]._2 = 4;
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
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

//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply()
{
	// leer lista de coordenadas de vértices y lista de indices de vértices
}

void _objeto_ply::parametros(char *archivo)
{
	int n_ver, n_car;

	vector<float> ver_ply;
	vector<int> car_ply;

	_file_ply::read(archivo, ver_ply, car_ply);

	n_ver = ver_ply.size() / 3;
	n_car = car_ply.size() / 3;

	printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

	vertices.resize(n_ver);
	caras.resize(n_car);

	for(int i=0; i<n_ver; i++) // Convertir vector de vértices
	{
		vertices[i].x = ver_ply[i*3];
		vertices[i].y = ver_ply[i*3+1];
		vertices[i].z = ver_ply[i*3+2];
	}

	for(int i=0; i<n_car; i++) // Convertir vector de caras
	{
		caras[i]._0 = car_ply[i*3];
		caras[i]._1 = car_ply[i*3+1];
		caras[i]._2 = car_ply[i*3+2];
	}

	// Asignar colores random a las caras del objeto
	colores.resize(n_car);
	for(int i=0; i<n_car; i++)
	{
		colores[i].r = (rand() % 100) / 100.0;
		colores[i].g = (rand() % 100) / 100.0;
		colores[i].b = (rand() % 100) / 100.0;
	}

}

//************************************************************************
// objetos por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}

// Crear un ply por revolución
_rotacion::_rotacion(const char *archivo, int num){
	int n_ver, n_car;

	vector<float> ver_ply;
	vector<int> car_ply;

	// Leer el archivo ply
	_file_ply::read(archivo, ver_ply, car_ply);

	n_ver = ver_ply.size()/3;
	n_car = car_ply.size()/3;

	// Guardar las caras del perfil
	vector<_vertex3f> perfil;
	_vertex3f aux;

	for(int i=0; i<n_ver; i++){
		aux.x = ver_ply[i*3];
		aux.y = ver_ply[i*3+1];
		aux.z = ver_ply[i*3+2];
		perfil.push_back(aux);
	}

	// Crear el objeto por revolución
	parametros(perfil, num);
}


void _rotacion::parametros(vector<_vertex3f> perfil, int num)
{
	int i, j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértices

	num_aux = perfil.size();
	vertices.resize(num_aux * num);
	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux; i++)
		{
			vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.y = perfil[i].y;
			vertices[i + j * num_aux] = vertice_aux;
		}
	}

	// tratamiento de las caras (REVISAR)
	caras.resize(num_aux * num * 2);
	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux - 1; i++)
		{
			if (j < num - 1)
			{
				cara_aux._0 = i + j * num_aux;
				cara_aux._1 = i + (j + 1) * num_aux;
				cara_aux._2 = i + 1 + j * num_aux;
				caras[i * 2 + j * num_aux * 2] = cara_aux;
				cara_aux._0 = i + (j + 1) * num_aux;
				cara_aux._1 = i + 1 + (j + 1) * num_aux;
				cara_aux._2 = i + 1 + j * num_aux;
				caras[i * 2 + 1 + j * num_aux * 2] = cara_aux;
			}
			else
			{
				cara_aux._0 = i + j * num_aux;
				cara_aux._1 = i + num_aux;
				cara_aux._2 = i + 1 + j * num_aux;
				caras[i * 2 + j * num_aux * 2] = cara_aux;
				cara_aux._0 = i + num_aux;
				cara_aux._1 = i + 1 + num_aux;
				cara_aux._2 = i + 1 + j * num_aux;
				caras[i * 2 + 1 + j * num_aux * 2] = cara_aux;
			}
		}
	}

	// crear la tapa inferior del sólido por revolución 
	if (fabs(perfil[0].x) > 0.0)
	{
		vertice_aux.x = 0.0;
		vertice_aux.y = perfil[0].y;
		vertice_aux.z = 0.0;
		vertices.push_back(vertice_aux);
		for (j = 0; j < num; j++)
		{
			cara_aux._0 = vertices.size() - 1;
			if (j < num - 1)
			{
				cara_aux._1 = j * num_aux;
				cara_aux._2 = (j + 1) * num_aux;
			}
			else
			{
				cara_aux._1 = j * num_aux;
				cara_aux._2 = 0;
			}
			caras.push_back(cara_aux);
		}
	}

	// tapa superior
	if (fabs(perfil[num_aux - 1].x) > 0.0)
	{
		vertice_aux.x = 0.0;
		vertice_aux.y = perfil[num_aux - 1].y;
		vertice_aux.z = 0.0;
		vertices.push_back(vertice_aux);
		for (j = 0; j < num; j++)
		{
			cara_aux._0 = vertices.size() - 1;
			if (j < num - 1)
			{
				cara_aux._1 = (j + 1) * num_aux - 1;
				cara_aux._2 = j * num_aux - 1;
			}
			else
			{
				cara_aux._1 = num_aux - 1;
				cara_aux._2 = j * num_aux - 1;
			}
			caras.push_back(cara_aux);
		}
	}
}

// crear un cono por revolución
_cono::_cono(int num1, int num2, float radio, float altura){
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x = radio;
	aux.y = 0;
	aux.z = 0;
	perfil.push_back(aux);

	aux.x = 0;
	aux.y = altura;
	aux.z = 0;
	perfil.push_back(aux);

	parametros(perfil, num1);
}

// Crear un cilindro por revolución
_cilindro::_cilindro(int num, float radio, float altura){
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x = radio;
	aux.y = 0;
	aux.z = 0;
	perfil.push_back(aux);

	aux.x = radio;
	aux.y = altura;
	aux.z = 0;
	perfil.push_back(aux);

	parametros(perfil, num);

	// Asignar colores random a las caras del cilindro
	/*for (int i = 0; i < caras.size(); i++){
		_color4f color;
		color.r = (rand() % 100) / 100.0;
		color.g = (rand() % 100) / 100.0;
		color.b = (rand() % 100) / 100.0;
		color.a = 1.0;
		colores.push_back(color);
	}*/
}

// esfera
_esfera::_esfera(int num1, int num2, float radio){
	vector<_vertex3f> perfil;
	_vertex3f aux;

	for (int i = 1; i < num1; i++){
		aux.x = radio * sin(M_PI * i / num1);
		aux.y = radio * cos(M_PI * i / num1);
		aux.z = 0;
		perfil.push_back(aux);
	}

	parametros(perfil, num1);

	// Asignar colores random a las caras de la ESFERA
	/*for (int i = 0; i < caras.size(); i++){
		_color4f color;
		color.r = (rand() % 100) / 100.0;
		color.g = (rand() % 100) / 100.0;
		color.b = (rand() % 100) / 100.0;
		color.a = 1.0;
		colores.push_back(color);
	}*/
}


//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
	int i;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértice

	num_aux = poligono.size();
	vertices.resize(num_aux * 2);
	for (i = 0; i < num_aux; i++)
	{
		vertices[2 * i] = poligono[i];
		vertices[2 * i + 1].x = poligono[i].x + x;
		vertices[2 * i + 1].y = poligono[i].y + y;
		vertices[2 * i + 1].z = poligono[i].z + z;
	}

	// tratamiento de las caras

	caras.resize(num_aux * 2);
	int c = 0;
	for (i = 0; i < num_aux; i++)
	{
		caras[c]._0 = i * 2;
		caras[c]._1 = (i * 2 + 2) % (num_aux * 2);
		caras[c]._2 = i * 2 + 1;
		c = c + 1;
		caras[c]._0 = (i * 2 + 2) % (num_aux * 2);
		caras[c]._1 = (i * 2 + 2) % (num_aux * 2) + 1;
		caras[c]._2 = i * 2 + 1;
		c = c + 1;
	}
}
