#include <stdlib.h>
#include <GL/glut.h>

void ajusta(int ancho, int alto){
   glClearColor(1.0, 1.0, 1.0, 1);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-5, 5.0, -5.0, 5.0,1.1, -1.1); //-1 es el más cerca
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glEnable(GL_BLEND);//habilita mezcla de colores
   glEnable(GL_DEPTH_TEST); 
}

void dibujaCuadrado(float x, float y){
	glBegin(GL_QUADS);
		glVertex3f(0+x,0+y,0);
		glVertex3f(2.5+x,0+y,0);
		glVertex3f(2.5+x,2.5+y,0);
		glVertex3f(0+x,2.5+y,0);
	glEnd();	
}

void dibujaNombre(void *tipo, char *s ) {
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

void escribeValores(){
	glColor4ub(0,0,0,1);
	glRasterPos3f(-.3,0,-1);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.5");
	glRasterPos3f(-2.5,2.7,-1);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.1");
    glRasterPos3f(2,2.7,-1);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.3");
	glRasterPos3f(-2.5,-2.8,-1);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.9");
	glRasterPos3f(2,-2.8,-1);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.7");
}

void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	escribeValores();	
	glColor4f(1.0, 0.0, 0.0, 0.1);
	dibujaCuadrado(-3.5,1.5);
	glColor4f(0.0, 1.0, 0.0, 0.3);
	dibujaCuadrado(1,1.5);
	glColor4f(0.0, 0.0, 1.0, 0.9);
	dibujaCuadrado(-3.5,-4);	
	glColor4f(1.0, 0.0, 1.0, 0.7);
	dibujaCuadrado(1,-4);
		glPushMatrix();
			glColor4f(1.0, 1.0, 0.0, 0.5);
			glScalef(1.6,1.6,1);
			glBegin(GL_QUADS);
				glVertex3f(-1.3,-1.25,-.5);
				glVertex3f(1.2,-1.25,-.5);
				glVertex3f(1.2,1.25,-.5);
				glVertex3f(-1.3,1.25,-.5);
			glEnd();
		glPopMatrix();
	glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y){
	switch (tecla) {
    	case 27: exit(0);
		case 49: // Equivale a glDisable(GL_BLEND)
            glBlendFunc(GL_ONE,GL_ZERO); 
    		break;
      	case 50:
			glBlendFunc(GL_SRC_ALPHA,GL_SRC_ALPHA);
			break;
		case 51:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case 52:
			glBlendFunc(GL_SRC_ALPHA,GL_SRC_COLOR);
			break;
		case 53:
			glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR);
			break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Cuadros transparencia Zbuffer");
	glutDisplayFunc(dibuja);
	glutReshapeFunc(ajusta);
	glutKeyboardFunc (teclado);
	glutMainLoop();
   return 0;
}