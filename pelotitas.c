/*-------------------------INSTRUCCIONES--------------------------
Toma el programa de fuerza, para que en lugar de una “pelotita” sean 7,
debes crear una estructura para “modelar” las propiedades físicas de las
“pelotas” y colocarlas en un arreglo. */

#include <GL/glut.h>
#include "random.h"
#define GRAVEDAD -9.81
#define MASA 200 // masa de la pelota
//si queremos que sea más lentos necesitamos un h más pequeño
double h= 0.015;     // h incrementos de tiempo
double fzaX=.02;
double fzaZ=-.05;
GLboolean bx=GL_FALSE;
GLboolean by=GL_FALSE;
GLboolean bz=GL_FALSE;
//ocupo arreglos dentro de la escrutura para poder tener valores diferentes de x,y,z
struct pelota{
	float fuerza[3]; 
	float posicion[3];
	float velocidad[3];
	int color[3];
};

struct pelota p[7];

void integraEuler() {
    for (int i=0; i<7; i++) {
    	//  v(t+h)=v(t)+F(t)/m*h
   		//cambia la velocidad dependiendo de las fuerzas
        if (bx) p[i].velocidad[0] += p[i].fuerza[0]*h;
        if (by) p[i].velocidad[1] += GRAVEDAD/MASA*h; //en y es donde se considera la gravedad
        if (bz) p[i].velocidad[2] += p[i].fuerza[2]*h;
		// x(t+h)=x(t) + v(t+h)*h
        //cambia las posiciones
        p[i].posicion[0] += p[i].velocidad[0] * h;
        p[i].posicion[1] += p[i].velocidad[1] * h;
        p[i].posicion[2] += p[i].velocidad[2] * h;
    }
}
void ajusta(int alto, int ancho){
    glClearColor(0.5,0.5,0.5,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)alto/ancho, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0,0,0);
    glLineWidth(2);
    glPushMatrix();
       glTranslatef(0,0,-16);
       glutWireCube(11);
   		for (int i=0; i<7 ; i++){
   			glColor3ub(p[i].color[0], p[i].color[1], p[i].color[2]);
   			glPushMatrix();
       			glTranslated(p[i].posicion[0],p[i].posicion[1],p[i].posicion[2]);
       			glutSolidSphere(.4,20,20);
   			glPopMatrix();
		}
    glPopMatrix();
    glutSwapBuffers();
}
void mueve(void){
    integraEuler(); //nos da la nueva posición
    //COLISIONES
    //posicion en x
    for (int i=0; i<7; i++){
    	if(p[i].posicion[0]>=5 || p[i].posicion[0]<=-5){ //X
	      p[i].fuerza[0]=-1*p[i].fuerza[0]; //invierte para cambiar el sentido de la fuerza y por lo tanto el mov
	      p[i].velocidad[0]=0;
	      p[i].posicion[0]=(p[i].posicion[0]>=5)?4.8-i*0.2:-4.8+i*.2;
	    }  if(p[i].posicion[1]>=5){ //Y Arriba
	         p[i].velocidad[1]= 0;
	         p[i].posicion[1]= 4.2;
	    }
	    if(p[i].posicion[1]<=-5){  //Y Abajo
	        p[i].velocidad[1]= 0.9; //bouncing
	        p[i].posicion[1]= -4.8;
	    }
	    if(p[i].posicion[2]>=5 || p[i].posicion[2]<=-5){  //Z
	      p[i].fuerza[2]=-1*p[i].fuerza[2];
	      p[i].velocidad[2]=0;
	      p[i].posicion[2]=(p[i].posicion[2]>=5)?4.8:-4.8;
	    }	
	}
    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
      case 27:  exit(0);
      case 'x': bx = !bx; break;
      case 'y': by = !by; break;
      case 'z': bz = !bz; 
    }
}
void init() {
	srand(29);
    for (int i=0; i<7; i++) {
        p[i].fuerza[0]=fzaX;
        p[i].fuerza[2]=fzaZ;
        p[i].posicion[0]=-5+i*1.5;//aquí se desplazan las pelotas
        p[i].posicion[1]=0;
        p[i].posicion[2]=0;
         p[i].velocidad[0]=0;
        p[i].velocidad[1]=0;
        p[i].velocidad[2]=0;
        p[i].color[0]=rnd0F(225);
        p[i].color[1]=rnd0F(225);
        p[i].color[2]=rnd0F(225);
    }
}
int main(int argc, char** argv){
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Pelotitas");
    init();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
	glutIdleFunc(mueve);
    glutMainLoop();
    return 0;
}