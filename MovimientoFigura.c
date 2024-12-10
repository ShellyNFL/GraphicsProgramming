#include <GL/glut.h>
#include <stdbool.h> //datos tipo bool
#include "pez.h"

int pX =240;
int pY =345;
bool colores= true;
bool imagen = true;

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void dibujaImagen(){
	int size = imagen ? 10 : 5;
	int height = imagen ? ALTO : ALTOT;
	int width = imagen ? ANCHO : ANCHOT;
	
	glPointSize(size);
	glBegin(GL_POINTS);
 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (imagen) {
                if (colores)
                    glColor3ubv(paleta1[pez[i][j]]);
                else
                    glColor3ubv(paleta2[pez[i][j]]);
            } else {
                if (colores)
                    glColor3ubv(paleta1t[toad[i][j]]);
                else
                    glColor3ubv(paleta2t[toad[i][j]]);
            }
            glVertex2i(pX+j*size, pY-i*size);
        }
    }

	glEnd();	
}

void mueveImagenes(int tecla, int x, int y){
	switch(tecla){
		case GLUT_KEY_UP:
			pY+=30;
			colores= !colores;
			break;
		case GLUT_KEY_RIGHT:
			pX+=30;
			colores= !colores;
			break;
		case GLUT_KEY_DOWN:
			pY-=30;
			colores= !colores;
			break;
		case GLUT_KEY_LEFT:
			pX-=30;
			colores= !colores;
			!colores;
			break;
		case GLUT_KEY_F1:
			imagen= !imagen;
			glClear(GL_COLOR_BUFFER_BIT);
			break;
					
	}
	glutPostRedisplay(); //importantísimo, sin este no se ven los cambios
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    dibujaImagen();
    glFlush();
}
void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Movimiento de dibujos");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutSpecialFunc(mueveImagenes);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}