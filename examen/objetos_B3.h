//**************************************************************************
// Práctica 2 
//**************************************************************************

#if defined(__APPLE__) // Para que funcione en apple
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#endif

#include <vector>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
vector<_vertex3f> colores_vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_colores();
void 	draw(_modo modo, float r, float g, float b, float grosor);

/* asignación de colores */
void 	colors_random();
void 	colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);


vector<_vertex3i> caras;
vector<_vertex3f> colores_caras;
};

//*************************************************************************
// objetos o modelos
//*************************************************************************

class _octaedro: public _triangulos3D
{
public:
       _octaedro(float tam=0.5);
};
//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5, bool tapa_inf=true, bool tapa_sup=true);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=1.0, bool tapa_inf=true, bool tapa_sup=true);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

void  parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************
// tipo indica si es una figura por revolución normal o bien un cono o una esfera
// tipo=0 normal, tipo=1 cono, tipo=2 esfera
// tapa_in=0 sin tapa, tapa_in=1 con tapa
// tapa_su=0 sin tapa, tapa_su=1 con tapa

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
       
void parametros(vector<_vertex3f> perfil, int num, int tipo, bool tapa_inf=true, bool tapa_sup=true);
};

 
//************************************************************************
// cilindro
//************************************************************************

class _cilindro: public _rotacion
{
public:
       _cilindro(float radio=1.0, float altura=2.0, int num=12, bool tapa_inf=true, bool tapa_sup=true);
};

//************************************************************************
// cono
//************************************************************************

class _cono: public _rotacion
{
public:
       _cono(float radio=1, float altura=2, int num=6, bool tapa_inf=true, bool tapa_sup=true);
};

//************************************************************************
// esfera
//************************************************************************

class _esfera: public _rotacion
{
public:
       _esfera(float radio=1, int num1=6, int num2=6, bool tapa_inf=true, bool tapa_sup=true);
};


//************************************************************************
// rotacion archivo PLY
//************************************************************************

class _rotacion_PLY: public _rotacion
{
public:
       _rotacion_PLY();
void  parametros_PLY(char *archivo, int num);
};


//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion: public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};


//************************************************************************
// práctica 3, objeto jerárquico articulado NINTENDO SWITCH
//************************************************************************

class _semiesfera: public _rotacion
{
public:
       _semiesfera(float radio, int num1, int num2, bool tapa_inf=true, bool tapa_sup=true);
};



//************************************************************************
// Clase para la pantalla
//************************************************************************

class _pantalla: public _triangulos3D {
public:
       _pantalla();
       float rotacion_pie = 0;
       float rotacion_pie_max = 45;
void  draw(_modo modo, float r, float g, float b, float grosor);

protected:
       _cubo pantalla_ext;
       _cubo pantalla_int;
       _cubo pie;
};

// *****************************************************************
// clase para el objeto jerárquico: joystick
// *****************************************************************

class _joystick: public _triangulos3D {
public:
       _joystick();
void  draw(_modo modo, float r, float g, float b, float grosor);
protected:
       _cilindro palo_joystick;
       _cilindro boton;
};

//************************************************************************
// Clase para el mando de la nintendo 
//************************************************************************

class _mando: public _triangulos3D {
public:
       _mando();
       float giro_joystick;
       float max_giro_joystick = 23;
       float pulsacion_boton;
       float pulsacion_boton_min;
       
       void draw(_modo modo, float r, float g, float b, float grosor);

protected:
       /* float alto;
       float ancho;
       float profundo; */
       
       _cilindro arriba;
       _cilindro abajo;
       _cilindro izquierda;
       _cilindro derecha;
       
       _joystick joystick;
       _cubo base;
       _esfera parte_arriba;
       _esfera parte_abajo;
};

//************************************************************************
// Objeto jerárquico: NINTENDO SWITCH
//************************************************************************
class _nintendo: public _triangulos3D 
{
public:
       _nintendo();
       _mando mando_izq;
       _mando mando_dch;
       _pantalla pantalla;

       float sacar_mando;
       float sacar_mando_max = 2;

void draw(_modo modo, float r, float g, float b, float grosor);
       
};

class _pirindolo: public _triangulos3D
{
       public:
       float altura_cilindro = 0.2;
       float trans_altura = 0;
       _pirindolo();
       _esfera esfera;
       _cilindro cilindro;

       void draw(_modo modo, float r, float g, float b, float grosor);
};

class _brazo: public _triangulos3D {
public:
       float altura_base = 0.2;
       float largo_base = 1.5;
       float profundidad_base = 0.4;

       _brazo();
       _pirindolo pirindolo;
       
       void draw(_modo modo, float r, float g, float b, float grosor);
protected:
       _cubo base;

};

class _construccion:public _triangulos3D{
public:
       float altura_cono = 2;
       float rotacion_cono = 0;
       _construccion();
       _cono cono;
       _brazo brazo;
       //_pirindolo pirindolo;

       void draw(_modo modo, float r, float g, float b, float grosor);
};

class _figura_ : public _triangulos3D
{
       public:
       _figura_();
       _construccion construccion;
};
