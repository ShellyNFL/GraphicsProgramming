#include <stdlib.h>
#include <GL/glut.h>

void ajusta(int ancho, int alto){
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-5, 5.0, -5.0, 5.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glEnable(GL_BLEND);//habilita mezcla de colores
}

void dibujaCuadrado(float x, float y){
	glBegin(GL_QUADS);
		glVertex2f(0+x,0+y);
		glVertex2f(2.5+x,0+y);
		glVertex2f(2.5+x,2.5+y);
		glVertex2f(0+x,2.5+y);
	glEnd();	
}

void dibujaNombre(void *tipo, char *s ) {
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

void escribeValores(){
	glColor3ub(0,0,0);
	glRasterPos2f(-.3,0);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.5");
	glRasterPos2f(-2.5,2.7);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.1");
    glRasterPos2f(2,2.7);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.3");
	glRasterPos2f(-2.5,-2.8);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.9");
	glRasterPos2f(2,-2.8);
    dibujaNombre(GLUT_BITMAP_HELVETICA_18,"0.7");
}

void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT);	
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
		dibujaCuadrado(-1.3,-1.25);
	glPopMatrix();
	escribeValores();
	glFlush();
}

void teclado(unsigned char tecla, int x, int y){
	switch (tecla) {
    	case 27: exit(0);
		case 49: // Equivale a glDisable(GL_BLEND)
            glBlendFunc(GL_ONE,GL_ZERO); 
    		break;
      	case 50:
			glBlendFunc(GL_SRC_ALPHA,GL_SRC_ALPHA);
			//escribeValores();//gl disable y gl_blend
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
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Cuadros transparencia");
	glutDisplayFunc(dibuja);
	glutReshapeFunc(ajusta);
	glutKeyboardFunc (teclado);
	glutMainLoop();
   return 0;
}