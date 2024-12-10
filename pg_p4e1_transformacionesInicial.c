/*							Instrucciones
Toma tu letra y con un clic del ratón define y dibuja un punto pivote. 
Después con la tecla R realiza 2 rotaciones de 360° y con la tecla S 
escala de .2 a 5 y regresa al tamaño original. 						*/

#include <GL/glut.h>
#include "inicial.h"
#include <stdbool.h>

int xpt,ypt;
bool rotar= false,
	 escalar = false,
	 crece = false,
	 pivote= false;
int angulo = 0;
float escala = 0.0;


void ajusta(int ancho, int alto) {
    glClearColor(1.0,1.0,1.0,0.0);	// color de background blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 320, -240, 240, 200, -200); //el 0,0,0 está  en el centro de la ventana
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    if(rotar == false && escalar == false){
    	glColor3ub(23, 190, 187);
    	dibujaInicial(-140,-240, GL_QUAD_STRIP);	
	} else{	
	/*Para que observar todo el proceso de rotación o escalación, se tiene que ir
	 girando la inicial o modificando su tamaño poco a poco, porque en otro caso,por un lado 
	 realizará el giro completo y sólo mostrará la posición final después de rotar 
	 (no el giro en sí). Por otro lado, crecerá la inicial pero no se verá cómo va creciendo*/
		glPushMatrix();
	/*La matriz de transformaciones sigue la estructura FILO, 
    es decir, la primera acción será la última que se implementa.*/
			glTranslatef(xpt, ypt, 0); //se regresa a la posición original
			if(rotar)
					glRotatef(angulo, 0, 0, 1);//se rota
			if(escalar)
				glScalef(escala,escala,1); //se escala
			glTranslatef(-xpt, -ypt, 0); //se mueve a la coordenada 0,0
			dibujaInicial(-140, -240, GL_QUAD_STRIP);
    	glPopMatrix();		
	}

    //glColor3ub(214, 34, 70);
	glPointSize(5);
	if(pivote){
		glBegin(GL_POINTS);
			glVertex3i(xpt,ypt,0);
		glEnd();
	}

    glutSwapBuffers();
}

void dibujaPivote(int boton, int estado, int x, int y){
	if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
		//printf("EN GLUT X: %d Y:%d \n",x,y);
		pivote = true;
		//se ajustan las coordenadas a las que configuramos en opengl con glOrtho
		xpt = x - 320;      
        ypt = 240 - y; 
        //printf("MODIFICADAS X: %d Y:%d \n",xpt,ypt);
	}
	glutPostRedisplay();	
}

void giroAutomatico(int valor){
	if (rotar){
		angulo+=5;
		if(angulo>720){
			angulo = 0;
			rotar = false;
		}
		glutPostRedisplay();
		glutTimerFunc(20,giroAutomatico,1);	
	}		
}

void escalamientoAutomatico(int valor){
	if (escalar) {
        if (crece) {
            escala += 0.2;
            if (escala >= 5.0){
            	escala = 5;
            	crece = false;
			} 
        }else {
            escala -= 0.2;
            if (escala <= 0.2){
            	escala = 0.2;
            	crece = true;
			} 
        }
        if ((escala>0.9 && escala<1.1) && !crece) {
        	escala = 1;
            escalar = false;
        }

        glutPostRedisplay();
        glutTimerFunc(500, escalamientoAutomatico, 1);
    }
}


void teclasAscii(unsigned char key, int x, int y) {
	switch(key){
		case 27: exit(0); break;
		case 'r': rotar = true; giroAutomatico(1); break;
		case 's': escalar = true; escalamientoAutomatico(1); break;
	}
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Transformaciones a mi Inicial");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(teclasAscii);
    glutMouseFunc(dibujaPivote);
    glutMainLoop();
    return 0;
}