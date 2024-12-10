/*							Instrucciones
 Dibuja tu figura pixel a pixel con cubos, ocupa plantilla3D. 
 TIP: Centra tu figura en el origen.					*/
#include <gl/glut.h>
#include "princess.h"

GLfloat girax = 0, giray= 0, zoom=0;
GLshort grados=10;
//   Rotacion XY y Zoom
void mover (void) {
    glTranslated( 0, 0, zoom);
    glRotated( girax, 1.0, 0.0, 0.0);
    glRotated( giray, 0.0, 1.0, 0.0);
}

void ajusta(int ancho, int alto) {
    glClearColor(1.0,1.0,1.0,0.0);	// color de background blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 320, -240, 240, 200, -200); //el 0,0,0 está  en el centro de la ventana
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT);
		glColor3ub(47, 72, 88);
		glPushMatrix(); 
		mover();
		int size=9;
		/*NOTA IMPORTANTE, para este ejercicio a la princesa*/
		
		for(int i=0; i<ALTO; i++){
			for (int j=0; j<ANCHO ;j++){
				glColor3ubv(paleta1[princess[i][j]]);
				glPushMatrix(); 
					if(princess[i][j] != 0){
						glTranslatef(j*size - (ANCHO/2)*size,-(i*size - (ALTO/2)*size),0);
						glutSolidCube(size);
					}	
				glPopMatrix();	
			}
		}
		glPopMatrix();	
	glutSwapBuffers();
}


void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}
void flechas(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT:  giray-= grados;
         break;
    case GLUT_KEY_RIGHT: giray+= grados;
         break;
    case GLUT_KEY_UP:   girax -= grados;
	     break;
    case GLUT_KEY_DOWN: girax += grados;
    default:break;
  }
  glutPostRedisplay();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(400, 200);
    glutCreateWindow("Peach en cubos");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(salir);
    glutSpecialFunc(flechas);
    glutMainLoop();
    return 0;
}
