//**************************************************************************
// Práctica 3
//**************************************************************************

#if defined(__APPLE__) // Para que funcione en apple
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"

using namespace std;

// tipos
typedef enum
{
    CUBO,
    PIRAMIDE,
    OBJETO_PLY,
    ROTACION,
    CILINDRO,
    CONO,
    ESFERA,
    EXTRUSION,
    NINTENDO
} _tipo_objeto;
_tipo_objeto t_objeto = NINTENDO; // por defecto
_modo modo = SOLID;               // por defecto

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 650, Window_high = 650;

// objetos
_cubo cubo(0.5, false, false);
_piramide piramide(0.85, 1.3, false, true);
_objeto_ply ply;
_rotacion rotacion;
_cilindro cilindro(1, 2, 32, true, false);
_cono cono(1, 2, 6, true, true);
_esfera esfera(1, 6, 50, false, true);
//_excavadora excavadora;
_nintendo nintendo; // P3
_extrusion *extrusion;
int estadoRaton, xc, yc, cambio;
float factor = 1.0;

// Luces
bool luz2_on = false;
float alfa = 0.0;

// Materiales
_material oro = {{ 0.24725f, 0.1995f, 0.0745f, 1.0f }, 
                 {0.75164f, 0.60648f, 0.22648f, 1.0f}, 
                 {0.628281f, 0.555802f, 0.366065f, 1.0f}, 
                 51.2f};

int activo=-1;  // Para la selección
float escalado = 1.0;
bool ortogonal = false;

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
    //  plano_delantero>0  plano_trasero>PlanoDelantero)
    glFrustum(-Size_x, Size_x, -Size_y, Size_y, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -Observer_distance);
    glRotatef(Observer_angle_x, 1, 0, 0);
    glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

    glDisable(GL_LIGHTING);
    glLineWidth(2);
    glBegin(GL_LINES);
    // eje X, color rojo
    glColor3f(1, 0, 0);
    glVertex3f(-AXIS_SIZE, 0, 0);
    glVertex3f(AXIS_SIZE, 0, 0);
    // eje Y, color verde
    glColor3f(0, 1, 0);
    glVertex3f(0, -AXIS_SIZE, 0);
    glVertex3f(0, AXIS_SIZE, 0);
    // eje Z, color azul
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -AXIS_SIZE);
    glVertex3f(0, 0, AXIS_SIZE);
    glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

    switch (t_objeto)
    {
    case CUBO:
        cubo.draw(modo, 0.0, 1.0, 0.0, 5, oro);
        break;
    case PIRAMIDE:
        piramide.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case OBJETO_PLY:
        ply.draw(modo, 1.0, 0.6, 0.0, 5, oro);
        break;
    case ROTACION:
        rotacion.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case CILINDRO:
        cilindro.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case CONO:
        cono.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case ESFERA:
        esfera.draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    case NINTENDO:
        glPushMatrix();
        // glScalef(0.5,0.5,0.5);
        glTranslatef(-1, 0, 0);
        nintendo.draw(modo, 1.0, 0.0, 0.0, 5, oro); 
        // los colores y el material se van a obviar porque se ponen dentro
        glPopMatrix();
        break;

    case EXTRUSION:
        extrusion->draw(modo, 1.0, 0.0, 0.0, 5, oro);
        break;
    }
}

//***************************************************************************
// Funcion para las luces
//***************************************************************************

void luces (float alfa, bool luz2_on){  //float alfa, float beta
	float    luz1[]={0.4, 0.3, 1.0, 1.0}, // azul neon
            luz_blanca[] = {1.0, 1.0, 1.0, 1.0},
			pos1[]= {0, 20.0, 40.0, 1.0}, // Cuidado con no ponerla dentro del objeto

			luz2[]={0.3, 0.0, 0.6, 1.0}, // morado neon
			pos2[]= {-20.0, 0.0, 100.0, 1.0},

            luz3[] = {0.8, 0.0, 0.8, 1.0}; // rosa neon

	glLightfv (GL_LIGHT1, GL_DIFFUSE, luz_blanca); 
	glLightfv (GL_LIGHT1, GL_SPECULAR, luz_blanca); 
    // Si no le ponemos componente especular, no tiene brillo, 
    // por lo que no cambia segun observador

	glPushMatrix();
	glLightfv (GL_LIGHT1, GL_AMBIENT, luz_blanca);
	glPopMatrix();

	glLightfv (GL_LIGHT2, GL_DIFFUSE, luz2); 
	glLightfv (GL_LIGHT2, GL_SPECULAR, luz2);

	glPushMatrix();
	glRotatef(alfa, 1, 0, 0);
	glLightfv (GL_LIGHT2, GL_POSITION, pos2);
	glPopMatrix();

	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

    if(luz2_on)
	    glEnable(GL_LIGHT2);
    else
        glDisable(GL_LIGHT2);

 }

 void vista_ortogonal(void){
    //Alzado
    glViewport(Window_width*0.5,Window_high*0.5,Window_width*0.5,Window_high*0.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5*escalado,5*escalado,-5*escalado,5*escalado,-100*escalado,100*escalado);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw_axis();
    draw_objects();

    //Planta
    glViewport(0,Window_high*0.5,Window_width*0.5,Window_high*0.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5*escalado,5*escalado,-5*escalado,5*escalado,-100*escalado,100*escalado);
    glRotatef(90,1,0,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw_axis();
    draw_objects();

    //Perfil
    glViewport(0,0,Window_width*0.5,Window_high*0.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5*escalado,5*escalado,-5*escalado,5*escalado,-100*escalado,100*escalado);
    glRotatef(90,0,1,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw_axis();
    draw_objects();

 }

//**************************************************************************
//
//***************************************************************************

void draw(void)
{
    glDrawBuffer(GL_FRONT);
    clean_window();

    if(ortogonal == false){
        glViewport(0, 0, Window_width, Window_high);
        change_projection();
        change_observer();
        luces(alfa, luz2_on);
        draw_axis();
        draw_objects();
    } else {
        vista_ortogonal();
    }

    if(t_objeto == NINTENDO){
        glDrawBuffer(GL_BACK);
        clean_window();
        change_observer();
        nintendo.seleccion();
    }

    glFlush();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1)
{
    float Aspect_ratio;

    Aspect_ratio = (float)Alto1 / (float)Ancho1;
    Size_y = Size_x * Aspect_ratio;
    change_projection();
    glViewport(0, 0, Ancho1, Alto1);
    Window_high = Alto1;
    Window_width = Ancho1;
    glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1, int x, int y)
{
    switch (toupper(Tecla1))
    {
    case 'Q':
        exit(0);
    case '1':
        modo = POINTS;
        break;
    case '2':
        modo = EDGES;
        break;
    case '3':
        modo = SOLID;
        break;
    case '4':
        modo = SOLID_COLORS;
        break;
    case '5':
        modo = SOLID_FLAT;
        break;
    case '6':
        modo = SOLID_SMOOTH;
        break;
    case 'P':
        t_objeto = PIRAMIDE;
        break;
    case 'C':
        t_objeto = CUBO;
        break;
    case 'O':
        t_objeto = OBJETO_PLY;
        break;
    case 'R':
        t_objeto = ROTACION;
        break;
    case 'L':
        t_objeto = CILINDRO;
        break;
    case 'N':
        t_objeto = CONO;
        break;
    case 'E':
        t_objeto = ESFERA;
        break;
    case 'A':
        t_objeto = NINTENDO;
        break;
    case 'X':
        t_objeto = EXTRUSION;
        break;
    case 'I':
        if(luz2_on){
            luz2_on = false;
            printf("\nLuz 2 encendida"); // Está al revés porque la primera vez no sale y 
            // siempre se ejecuta después el refresco de la pantalla
        }
        else{
            luz2_on = true;
            printf("\nLuz 2 apagada");
        }
        break;
    case 'V':
        if(luz2_on)
            alfa += 5;
        break;
    case 'B':
        if(luz2_on)
            alfa -= 5;
        break;
    case 'T':
        if(ortogonal == false)
            ortogonal = true;
        else
            ortogonal = false;
        break;
    case '+':
        escalado += 1.1;
        break;
    case '-':
        escalado -= 1.1;
        break;
    }

    glutPostRedisplay();
}

void orto(void)
{
    //Alzado
    glViewport(Window_width/2,Window_high/2,Window_width/2,Window_high/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5*factor, 5*factor, -5*factor, 5*factor, -100*factor, 100*factor);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw_axis();
    draw_objects();

    //Planta
    glViewport(0,Window_high/2,Window_width/2,Window_high/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5*factor, 5*factor, -5*factor, 5*factor, -100*factor, 100*factor);
    glRotatef(90, 1, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw_axis();
    draw_objects(); 

    //Perfil
    glViewport(0,0,Window_width/2,Window_high/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5*factor, 5*factor, -5*factor, 5*factor, -100*factor, 100*factor);
    glRotatef(90, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw_axis();
    draw_objects(); 
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y)
{

    switch (Tecla1)
    {
    case GLUT_KEY_LEFT:
        Observer_angle_y -= 5;
        break;
    case GLUT_KEY_RIGHT:
        Observer_angle_y += 15;
        break;
    case GLUT_KEY_UP:
        Observer_angle_x--;
        break;
    case GLUT_KEY_DOWN:
        Observer_angle_x++;
        break;
    case GLUT_KEY_PAGE_UP:
        Observer_distance *= 1.2;
        break;
    case GLUT_KEY_PAGE_DOWN:
        Observer_distance /= 1.2;
        break;

    case GLUT_KEY_F1: // Girar joystick
        if (nintendo.mando_izq.giro_joystick < nintendo.mando_izq.max_giro_joystick)
            nintendo.mando_izq.giro_joystick += 5;
        break;

    case GLUT_KEY_F2: // girar joystick abajo
        if (nintendo.mando_izq.giro_joystick > (-nintendo.mando_izq.max_giro_joystick))
            nintendo.mando_izq.giro_joystick -= 5;
        break;

    case GLUT_KEY_F3: // pulsar botón
        /*if (nintendo.mando_izq.pulsacion_boton < -0.05 )
            nintendo.mando_izq.pulsacion_boton += 0.0025;
        else
            nintendo.mando_izq.pulsacion_boton = 0.05;

        break;*/

    case GLUT_KEY_F4: // Sacar mando
        if (nintendo.sacar_mando < 2)
            nintendo.sacar_mando += 0.1;
        break;

    case GLUT_KEY_F5: // Meter mando
        if (nintendo.sacar_mando > 0)
            nintendo.sacar_mando -= 0.1;
        break;
    }
    glutPostRedisplay();

}

void procesar_color(unsigned char color[3]){
    for(int i = 0; i<nintendo.piezas; i++){
        if(color[0] == nintendo.color_select[i].r && 
           color[1] == nintendo.color_select[i].g && 
           color[2] == nintendo.color_select[i].b){
            if(nintendo.activo[i] == 0)
            {
                nintendo.activo[i] = 1;
                printf("\nPieza [%d] desactivada ----> ", i); // Está al revés para que los mensajes se vean bien
            }
            else
            {
                nintendo.activo[i] = 0;
                printf("\nPieza [%d] activada ----> ", i);
            }

            
            glutPostRedisplay();
        }
    }
}

void pick_color(int x, int y){
    unsigned char color[3];
    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadBuffer(GL_BACK);
    glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (GLubyte *) &color[0]);
    printf("valor x [%d], valor y [%d], color [%d, %d, %d]\n", x, y, color[0], color[1], color[2]);
    procesar_color(color);
}

void clickRaton(int boton, int estado, int x, int y)
{
    if(boton == GLUT_RIGHT_BUTTON)
    {
        if(estado == GLUT_DOWN){
            estadoRaton = 1;
            xc = x;
            yc = y;
        }
        else
            estadoRaton = 0;
    }

    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {
        estadoRaton = 2;
        xc = x;
        yc = y;
        pick_color(xc, yc);
    }

    if (boton == 3)
    {
        factor *= 1.1;
        glutPostRedisplay();
    }

    if (boton == 4)
    {
        factor *= 0.9;
        glutPostRedisplay();
    }
}

void RatonMovido(int x, int y){
    if(estadoRaton == 1){
        Observer_angle_y -= (x - xc);
        Observer_angle_x += (y - yc);
        xc = x;
        yc = y;
        glutPostRedisplay();
    }
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
    // se inicalizan la ventana y los planos de corte
    Size_x = 0.5;
    Size_y = 0.5;
    Front_plane = 1;
    Back_plane = 1000;

    // se incia la posicion del observador, en el eje z
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = 0;
    Observer_angle_y = 0;

    // se indica el color para limpiar la ventana	(r,v,a,al)
    // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    glClearColor(1, 1, 1, 1);

    // se habilita el z-bufer
    glEnable(GL_DEPTH_TEST);
    change_projection();
    glViewport(0, 0, Window_width, Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char *argv[])
{

    // perfil

    vector<_vertex3f> perfil, poligono;
    _vertex3f aux;

    /* aux.x=1.0; aux.y=-1.0; aux.z=0.0;
    perfil.push_back(aux);
    aux.x=1.5; aux.y=0.0; aux.z=0.0;
    perfil.push_back(aux);
    aux.x=1.0; aux.y=1.0; aux.z=0.0;
    perfil.push_back(aux);
    aux.x=1.5; aux.y=1.2; aux.z=0.0;
    perfil.push_back(aux);


    rotacion.parametros(perfil,6,0,1,1);
     */

    // Peón por rotación
    vector<_vertex3f> perfil_peon;

    aux.x = 1.0;	aux.y = -1.4;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 1.0;	aux.y = -1.1;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 0.5;	aux.y = -0.7;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 0.4;	aux.y = -0.4;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 0.4;	aux.y = 0.5;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 0.5;	aux.y = 0.6;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 0.3;	aux.y = 0.6;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 0.5;	aux.y = 0.8;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 0.55;	aux.y = 1.0;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 0.5;	aux.y = 1.2;	aux.z = 0.0;
    perfil_peon.push_back(aux);
    aux.x = 0.3;	aux.y = 1.4;	aux.z = 0.0;
    perfil_peon.push_back(aux);

    rotacion.parametros(perfil_peon, 24, 0, true, false);

    // Polígono por extrusión
    aux.x=1.0; aux.y=0.0; aux.z=1.0;
    poligono.push_back(aux);
    aux.x=1.0; aux.y=0.0; aux.z=-1.0;
    poligono.push_back(aux);
    aux.x=-1.2; aux.y=0.0; aux.z=-1.0;
    poligono.push_back(aux);
    aux.x=-0.8; aux.y=0.0; aux.z=0.0;
    poligono.push_back(aux);
    aux.x=-1.2; aux.y=0.0; aux.z=1.0;
    poligono.push_back(aux);

    extrusion = new _extrusion(poligono, 0.25, 1.0, 0.25);

    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(Window_x, Window_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(Window_width, Window_high);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("PRACTICA 5 - Esther García Gallego");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw);
    // asignación de la funcion llamada "change_window_size" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "normal_key" al evento correspondiente
    glutKeyboardFunc(normal_key);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_key);

    // funcion de inicialización
    initialize();

    // creación del objeto ply
    ply.parametros(argv[1]);

    // ply = new _objeto_ply(argv[1]);
    //Eventos ratón
    glutMouseFunc(clickRaton);
    glutMotionFunc(RatonMovido);

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
