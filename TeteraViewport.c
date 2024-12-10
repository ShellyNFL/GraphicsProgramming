/*-----------------------------INTRUCCIONES---------------------
5. En una ventana de 800x600, crea 4 viewports para
dibujar la tetera en 3 vistas ortogonales y una perspectiva,
como se muestra. No rotes la tetera, maneja la cámara con
gluLookAt.*/
//Debemos mantener la perspectiva proyeccion, viewport y tamaño de la ventana
#include <gl/glut.h>
#include <math.h>
void dibuja(void) {
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
    //cuadrante izq abajo
    glColor3ub(92, 83, 70);
	glViewport(0,0,400,300); //inicio el viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1,30); //-1, -30 regla mano izq
	//glyLookAt(eyex,eyey,eyez,  viewx,viewy,viewz,  upx,upy,upz)
	gluLookAt(0,0,1,  0,0,0,  0,1,0);
	glutWireTeapot(0.6);	
	//cuadrante der abajo
	glColor3ub(224, 54, 22);
	glViewport(400,0,400,300); //inicio el viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1,30);
	gluLookAt(1,0,0,  0,0,0,  0,1,0);
	glutWireTeapot(0.6);
	//cuadrante izq arriba
	glColor3ub(185, 19, 114);
	glViewport(0,300,400,300); //inicio el viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1,30);
	gluLookAt(0,-1.5,0.01,  0,1,0,  0,1,0);
	glutWireTeapot(0.6);
	//cuadrante der arriba
	glColor3ub(17, 181, 228);
	glViewport(400,300,400,300);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 30);
	gluLookAt(1,1,1.8,  0,0,0,  0,1,0);
	glutWireTeapot(0.5);
    glFlush();
}
int main(int argc, char** argv) {
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutInit(&argc, argv);
    glutCreateWindow("Teteras Viewport");
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}
