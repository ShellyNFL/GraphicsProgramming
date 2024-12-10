#include <GL/glut.h>
#include <stdio.h>
#include "random.h"
#include "ifs.h"
#define DIM 8
#define ITERA 50000
GLboolean s=GL_TRUE;
GLboolean b=GL_FALSE;
GLboolean d=GL_FALSE;  
//con 3 casos, modificar a 2 boolenanas

void teclado(unsigned char tecla, int x, int y){
   switch(tecla) {
     case 27:
		exit(0);
// Esc =>Salir del programa
     case 's':
		s=GL_TRUE;  //sierpinsky
   		break;
     case 'b':
		b=GL_TRUE;  //barnsley
   		break;
     case 'd':
		d=GL_TRUE; //muestra y deja de mostrar
    default:break;
   }
   glutPostRedisplay();
}


void fractal(void (*f)(float, float*)){
	float punto[2]={0.5, 0.5};
	for(int i=0; i<ITERA; i++){
		//con una probabilidad de 0.33 llamo a una funcion
		float prob = rnd01();
		(*f)(prob, punto);
		glPointSize(1);
		glBegin(GL_POINTS);
			//se necesita escalar y eso lo hace la multiplicacion por 300
			//y después se necesita recorrer
			glVertex2i(140+(300*punto[X]),140+(300*punto[Y]));
		//printf( "(%.2f, %.2f)", punto[X], punto[Y]);
		glEnd();
	}
}

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}
void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    if(s){
    	glColor3ub(255,0,125);
    	fractal(sierpi);
    	s=GL_FALSE;
    	b=GL_FALSE;
    	d=GL_FALSE;
	}else if(b){
		glColor3ub(6,80,43);
    	fractal(barnsley);
    	s=GL_FALSE;
    	b=GL_FALSE;
    	d=GL_FALSE;
	}else if(d){
		glColor3ub(0,125,255);
    	fractal(dragon);
    	s=GL_FALSE;
    	b=GL_FALSE;
    	d=GL_FALSE;
	}
	//DESCOMENTAR PARA VOLVER A LO ORIGINAL

    //fractal(sierpi);
    glFlush();
}
void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}
int main(int argc, char** argv) {
	semilla(10);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("ZinserFlores_FractalesInteractivos");
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutDisplayFunc(dibuja);
    //glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}