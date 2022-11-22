//**************************************************************************
// Práctica 3
//**************************************************************************

#include "objetos_B3.h"
#include "file_ply_stl.hpp"
#include <time.h>

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
  //**** usando vertex_array ****
  glPointSize(grosor);
  glColor3f(r, g, b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  glDrawArrays(GL_POINTS, 0, vertices.size());

  /*int i;
  glPointSize(grosor);
  glColor3f(r,g,b);
  glBegin(GL_POINTS);
  for (i=0;i<vertices.size();i++){
    glVertex3fv((GLfloat *) &vertices[i]);
    }
  glEnd();*/
}

//*************************************************************************
// Cálculo de normales de caras
//*************************************************************************

void _triangulos3D::calcular_normales_caras()
{
  int i, n_c;
  n_c = caras.size();
  _vertex3f va, vb;
  float modulo;
  normales_caras.resize(n_c);

  for (int i = 0; i < n_c; i++)
  {
    va = vertices[caras[i]._1] - vertices[caras[i]._0];
    vb = vertices[caras[i]._2] - vertices[caras[i]._0];
    // hacemos el producto vectorial (determinante de i,j,k de va y de vb)
    normales_caras[i].x = va.y * vb.z - va.z * vb.y;
    normales_caras[i].y = va.z * vb.x - va.x * vb.z;
    normales_caras[i].z = va.x * vb.y - va.y * vb.x;
    modulo = sqrt(normales_caras[i].x * normales_caras[i].x +
                  normales_caras[i].y * normales_caras[i].y +
                  normales_caras[i].z * normales_caras[i].z);
    normales_caras[i].x /= modulo;
    normales_caras[i].y /= modulo;
    normales_caras[i].z /= modulo;
  }
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
  // Inicialización de la luz ambiente
  ambiente_difuso = _vertex4f(0.9, 0.5, 0.1, 1.0);
  especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
  brillo = 110;
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  //**** usando vertex_array ****
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(r, g, b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  glDrawElements(GL_TRIANGLES, caras.size() * 3, GL_UNSIGNED_INT, &caras[0]);

  /*int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores()
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glColor3f(colores_caras[i].r, colores_caras[i].g, colores_caras[i].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo iluminacion para las caras
//*************************************************************************
void _triangulos3D::draw_solido_plano()
{
  int i;
  glEnable(GL_LIGHTING);
  glShadeModel(GL_FLAT);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *)&ambiente_difuso);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glNormal3f(normales_caras[i].r, normales_caras[i].g, normales_caras[i].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
  glDisable(GL_LIGHTING);
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
  case SOLID_FLAT:
    draw_solido_plano();
    break;

  }
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
  int i, n_c;
  n_c = caras.size();
  colores_caras.resize(n_c);
  srand(time(NULL));
  for (i = 0; i < n_c; i++)
  {
    colores_caras[i].r = rand() % 1000 / 1000.0;
    colores_caras[i].g = rand() % 1000 / 1000.0;
    colores_caras[i].b = rand() % 1000 / 1000.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_flat(float r, float g, float b, float p_lx, float p_ly, float p_lz)
{
  int i, n_c;
  _vertex3f l;
  float modulo, escalar;
  num_caras = caras.size();
  colores_caras.resize(num_caras);

  for (int i = 0; i < num_caras; i++) {
    colores_caras[i].r = 0.1 * r;
    colores_caras[i].g = 0.1 * g;
    colores_caras[i].b = 0.101 * b; // 0.101 por algo de que las sombras se ven más azules en la vida real
    l.x = p_lx - vertices[caras[i]._0].x;
    l.y = p_ly - vertices[caras[i]._0].y;
    l.z = p_lz - vertices[caras[i]._0].z;
    modulo = sqrt(l.x * l.x + l.y * l.y + l.z * l.z);
    l.x /= modulo;
    l.y /= modulo;
    l.z /= modulo;
    escalar = normales_caras[i].x * l.x + normales_caras[i].y * l.y + normales_caras[i].z * l.z;
    
    if (escalar > 0.0) {
      colores_caras[i].r += r * escalar;
      colores_caras[i].g += g * escalar;
      colores_caras[i].b += b * escalar;
    }
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
  int i, n_c;
  n_c = caras.size();
  colores_caras.resize(n_c);
  for (i = 0; i < n_c; i++)
  {
    if (i % 2 == 0)
    {
      colores_caras[i].r = r1;
      colores_caras[i].g = g1;
      colores_caras[i].b = b1;
    }
    else
    {
      colores_caras[i].r = r2;
      colores_caras[i].g = g2;
      colores_caras[i].b = b2;
    }
  }
}

//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam, bool tapa_inf, bool tapa_sup)
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

  // triangulos
  caras.resize(12);

  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 3;
  caras[1]._0 = 3;
  caras[1]._1 = 1;
  caras[1]._2 = 2;
  caras[2]._0 = 1;
  caras[2]._1 = 5;
  caras[2]._2 = 2;
  caras[3]._0 = 5;
  caras[3]._1 = 6;
  caras[3]._2 = 2;
  caras[4]._0 = 5;
  caras[4]._1 = 4;
  caras[4]._2 = 6;
  caras[5]._0 = 4;
  caras[5]._1 = 7;
  caras[5]._2 = 6;
  caras[6]._0 = 0;
  caras[6]._1 = 7;
  caras[6]._2 = 4;
  caras[7]._0 = 0;
  caras[7]._1 = 3;
  caras[7]._2 = 7;

  if (tapa_sup)
  {
    caras[8]._0 = 3;
    caras[8]._1 = 2;
    caras[8]._2 = 7;
    caras[9]._0 = 2;
    caras[9]._1 = 6;
    caras[9]._2 = 7;
  }

  if (tapa_inf)
  {
    caras[10]._0 = 0;
    caras[10]._1 = 1;
    caras[10]._2 = 4;
    caras[11]._0 = 1;
    caras[11]._1 = 5;
    caras[11]._2 = 4;
  }

  // colores de las caras
  colors_random();
  calcular_normales_caras();
  colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // ambiando los tres ultimos parámetros cambiamos de dónde viene la luz

}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al, bool tapa_inf, bool tapa_sup)
{
  int i;
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

  if (tapa_inf)
  {
    caras[4]._0 = 3;
    caras[4]._1 = 1;
    caras[4]._2 = 0;
    caras[5]._0 = 3;
    caras[5]._1 = 2;
    caras[5]._2 = 1;
  }

  // colores de las caras
  colors_random();
  calcular_normales_caras();
  colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // ambiando los tres ultimos parámetros cambiamos de dónde viene la luz

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
  int i, n_ver, n_car;

  vector<float> ver_ply;
  vector<int> car_ply;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3;
  n_car = car_ply.size() / 3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);
  
  // vértices
  for (i = 0; i < n_ver; i++)
  {
    vertices[i].x = ver_ply[3 * i];
    vertices[i].y = ver_ply[3 * i + 1];
    vertices[i].z = ver_ply[3 * i + 2];
  }

  // caras
  for (i = 0; i < n_car; i++)
  {
    caras[i].x = car_ply[3 * i];
    caras[i].y = car_ply[3 * i + 1];
    caras[i].z = car_ply[3 * i + 2];
  }

  colores_caras.resize(n_car);
  srand(10);

  // colores
  float sum;
  int n;
  colores_caras.resize(caras.size());

  for (i = 0; i < caras.size(); i++)
  {
    if (vertices[caras[i]._0].y >= 0)
    {
      colores_caras[i].r = rand() % 1000 / 1000.0;
      colores_caras[i].b = 0.0;
      colores_caras[i].g = 0.8;
    }
    else
    {
      n = rand() % 10;
      sum = rand() % 100 / 500.0;
      if (n < 5)
        colores_caras[i].r = 0.251 + sum;
      else
        colores_caras[i].r = 0.251 - sum;
      if (n > 5)
        colores_caras[i].b = 0.805 + sum;
      else
        colores_caras[i].b = 0.805 - sum;
      if (n > 5)
        colores_caras[i].g = 0.816 + sum;
      else
        colores_caras[i].g = 0.816 - sum;
    }
  }

  calcular_normales_caras();
  colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // Cambiando los tres ultimos parámetros cambiamos de dónde viene la luz

}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}
/*
  Tipo 0: normal
  Tipo 1: cono
  Tipo 2: esfera
*/
void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, bool tapa_inf, bool tapa_sup)
{
  int i, j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  float radio;

  // tratamiento de los vértice
  radio = sqrt(perfil[0].x * perfil[0].x + perfil[0].y * perfil[0].y);

  num_aux = perfil.size();
  if (tipo == 1)
    num_aux = num_aux - 1;
  vertices.resize(num_aux * num + 2);
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

  caras.resize(2 * (num_aux - 1) * num + 2 * num);
  int c = 0;
  for (j = 0; j < num; j++)
  {
    for (i = 0; i < num_aux - 1; i++)
    {
      caras[c]._0 = i + j * num_aux;
      caras[c]._1 = ((j + 1) % num) * num_aux + i;
      caras[c]._2 = 1 + i + j * num_aux;
      c += 1;
      caras[c]._0 = ((j + 1) % num) * num_aux + i;
      caras[c]._1 = ((j + 1) % num) * num_aux + 1 + i;
      caras[c]._2 = 1 + i + j * num_aux;
      c += 1;
    }
  }

  int total = num_aux * num;

  // tapa inferior
  if (tapa_inf)
  {
    vertices[total].x = 0.0;
    if (tipo == 2)
      vertices[total].y = -radio;
    else
      vertices[total].y = perfil[0].y;
    vertices[total].z = 0.0;

    for (j = 0; j < num; j++)
    {
      caras[c]._0 = j * num_aux;
      caras[c]._1 = ((j + 1) % num) * num_aux;
      caras[c]._2 = total;
      c += 1;
    }
  }

  // tapa superior
  if (tapa_sup)
  {
    vertices[total + 1].x = 0.0;
    if (tipo == 1)
      vertices[total + 1].y = perfil[1].y;
    if (tipo == 0)
      vertices[total + 1].y = perfil[num_aux - 1].y;
    if (tipo == 2)
      vertices[total + 1].y = radio;
    vertices[total + 1].z = 0.0;

    for (j = 0; j < num; j++)
    {
      caras[c]._0 = total + 1;
      caras[c]._1 = ((j + 1) % num) * num_aux + num_aux - 1;
      caras[c]._2 = num_aux - 1 + j * num_aux;
      c += 1;
    }
  }

  // colores de las caras
  colors_random();
  calcular_normales_caras();
  colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // Cambiando los tres ultimos parámetros cambiamos de dónde viene la luz

}

//************************************************************************
// objeto cilindro (caso especial de rotacion)
//************************************************************************

_cilindro::_cilindro(float radio, float altura, int num, bool tapa_inf, bool tapa_sup)
{
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x = radio;
  aux.y = -altura / 2.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = radio;
  aux.y = altura / 2.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  parametros(perfil, num, 0, tapa_inf, tapa_sup);
}

//************************************************************************
// objeto cono (caso especial de rotacion)
//************************************************************************

_cono::_cono(float radio, float altura, int num, bool tapa_inf, bool tapa_sup)
{
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x = radio;
  aux.y = 0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = 0.0;
  aux.y = altura;
  aux.z = 0.0;
  perfil.push_back(aux);
  parametros(perfil, num, 1, tapa_inf, tapa_sup); // ambas tapas
}

//************************************************************************
// objeto esfera (caso especial de rotacion)
//************************************************************************

_esfera::_esfera(float radio, int num1, int num2, bool tapa_inf, bool tapa_sup)
{
  vector<_vertex3f> perfil;
  _vertex3f aux;
  int i;
  for (i = 1; i < num1; i++)
  {
    aux.x = radio * cos(M_PI * i / (num1 * 1.0) - M_PI / 2.0);
    aux.y = radio * sin(M_PI * i / (num1 * 1.0) - M_PI / 2.0);
    aux.z = 0.0;
    perfil.push_back(aux);
  }
  parametros(perfil, num2, 2, tapa_inf, tapa_sup); // ninguna tapa
}

//************************************************************************
// rotacion archivo PLY (caso especial de rotacion)
//************************************************************************

_rotacion_PLY::_rotacion_PLY()
{
}

void _rotacion_PLY::parametros_PLY(char *archivo, int num)
{
}

//************************************************************************

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

  // colores de las caras
  colors_random();
  calcular_normales_caras();
  colors_flat(0.9,0.7,0.0,-20.0,20.0,-20.0); // Cambiando los tres ultimos parámetros cambiamos de dónde viene la luz

}

//************************************************************************
// práctica 3, objeto jerárquico articulado: NINTENDO SWITCH
//************************************************************************
/* _semiesfera::_semiesfera(float radio, int num1, int num2, bool tapa_inf=true, bool tapa_sup=true){
  vector<_vertex3f> perfil;
  _vertex3f aux;
  int i;
  for (i = 1; i < num1; i++)
  {
    aux.x = radio * cos(M_PI * i / (num1 * 1.0) - M_PI / 2.0);
    aux.y = radio * sin(M_PI * i / (num1 * 1.0) - M_PI / 2.0);
    aux.z = 0.0;
    perfil.push_back(aux);
  }
  parametros(perfil, num2, 2, tapa_inf, tapa_sup); // ninguna tapa

} */

_joystick::_joystick()
{
  palo_joystick = _cilindro(0.1, 0.2, 12, false, false);
  boton = _cilindro(0.3, 0.2, 12, true, true);
};

void _joystick::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  palo_joystick.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.2, 0);
  boton.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

_mando::_mando()
{
  // cuerpo
  base = _cubo(0.7, true, true);
  // botones
  arriba = _cilindro(0.2, 0.1, 12, false, true);
  abajo = _cilindro(0.2, 0.1, 12, false, true);
  izquierda = _cilindro(0.2, 0.1, 12, false, true);
  derecha = _cilindro(0.2, 0.1, 12, false, true);

  parte_arriba = _esfera(0.14, 6, 6, true, true);
  parte_abajo = _esfera(0.14, 6, 6, true, true);

  // Para las
  giro_joystick = 0;
  pulsacion_boton = 0;
  pulsacion_boton_min = 0.05;
}

void _mando::draw(_modo modo, float r, float g, float b, float grosor)
{

  // Botones
  glPushMatrix();
  glTranslatef(0.0, 0.1, 0.175 + pulsacion_boton); // arriba TODO CAMBIAR
  glRotatef(90, 1, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  arriba.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, -0.3, 0.175); // abajo
  glRotatef(90, 1, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  abajo.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.2, -0.1, 0.175); // izquierda
  glRotatef(90, 1, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  izquierda.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.2, -0.1, 0.175); // derecha
  glRotatef(90, 1, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  derecha.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();

  // Joystick
  glPushMatrix();
  glTranslatef(0.0, 0.7, 0.2);
  glScalef(0.65, 0.65, 0.6);
  glRotatef(90, 1, 0, 0);
  // Para las animaciones
  // glRotatef(giro_joystick, 1, 0, 0);
  // glRotatef(giro_joystick, 0, 1, 0);
  glRotatef(giro_joystick, 1, 1, 0);

  // Pintar
  joystick.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();

  /* // Parte de arriba del mando
  glPushMatrix();
  //glScalef(-0.5, -0.5, -0.5);
  glTranslatef(0.0, alto-0.5, 0.0);
  parte_arriba.draw(modo, 0.7, 0.7, 0.7, grosor);
  glPopMatrix(); */

  // Base
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  glScalef(0.6, 1.5, 0.2); // tiene el mismo ancho que la pantalla exterior
  // glScalef(2, 2, 2);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();

  /* // Parte de abajo del mando
  glPushMatrix();
  //glScalef(1.0, 0.2, 1.0);
  glTranslatef(0.0, -alto+0.5, 0.0);
  parte_abajo.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();  */
}

_pantalla::_pantalla()
{
  pantalla_ext = _cubo(0.7, true, true);
  pantalla_int = _cubo(0.6, true, true);
}

void _pantalla::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(1.4, 1, -0.2);
  pantalla_ext.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(1.3, 1, -0.2);
  glTranslatef(0, 0, -0.2);
  pantalla_int.draw(modo, 0.5, 0.5, 0.5, grosor);
  glPopMatrix();
}

_nintendo::_nintendo()
{
  sacar_mando = 0;
}

void _nintendo::draw(_modo modo, float r, float g, float b, float grosor)
{
  // Mando azul
  glPushMatrix();
  glScalef(0.677, 0.677, 0.7);
  glTranslatef(-0.4, 0 + sacar_mando, 0);
  // glTranslatef(0, sacar_mando, 0);
  mando_izq.draw(modo, 0, 0.73, 0.87, grosor); // azul
  glPopMatrix();

  // Base
  glPushMatrix();
  glTranslatef(1, 0, 0);
  glScalef(1, 1, 0.7);
  pantalla.draw(modo, 0, 0, 1, grosor);
  glPopMatrix();

  // Mando rojo (reinventado jaja)
  glPushMatrix();
  glTranslatef(2.25, 0, 0);
  glRotatef(180, 0, 0, 1);
  glScalef(0.677, 0.677, 0.7);
  mando_dch.draw(modo, 1, 0, 0, grosor); // rojo
  glPopMatrix();
};