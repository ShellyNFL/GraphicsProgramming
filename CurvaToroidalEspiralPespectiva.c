/*-----------------------------INTRUCCIONES---------------------
2. Grafica una curva toroidal espiral (la figura mostrada está
rotada) con las ecuaciones paramétricas y valores de: radios: a=2,
b=3, vueltas: c=20 y t=[0,2p]

 x = (a*sin(c*t)+b)*cos(t)
 y = (a*sin(c*t)+b)*sin(t)
 z = a*cos(c*t)*/
 
#include <gl/glut.h>
#include <math.h>
GLfloat  girax = 0, giray= 0, zoom=0;
GLboolean clic=GL_FALSE;
int gx, gy;

void ajusta(int ancho, int alto) {
	glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1.33,10,100);
    zoom=-40;
    glEnable(GL_DEPTH_TEST); //habilito el z buffer
}

void mover (void) {
    glTranslated( 0, 0, zoom);
    glRotated( girax, 1.0, 0.0, 0.0);
    glRotated( giray, 0.0, 1.0, 0.0);
}
void raton(int boton, int estado, int xv, int yv) {
    clic= boton==GLUT_LEFT_BUTTON && estado==GLUT_DOWN;
    if(clic){
        gx = xv;
        gy = yv;
    }
    if (boton==3 || boton==4) // scroll up => 3 scroll down=>4
        zoom+=(boton==3)?0.1:-0.1;
    glutPostRedisplay();
}
void girar(int xv, int yv) {
    if (clic){  // inicia circulos con centro
        girax -= (gy - yv);  //alrededor eje y (alturas)
        giray -= (gx - xv);  //alrededor eje x (izq der)
        gx = xv;
        gy = yv;
    }
    glutPostRedisplay();
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    float x,y,z;
    glColor3ub(7, 42, 200);
    glPushMatrix();
    	mover();
		glScalef(2,2,2);
    	glBegin(GL_LINE_LOOP);
			for(float t=0; t<=(2*M_PI); t+=0.01){
				x=(2*sin(20*t)+3)*cos(t);
		 		y = (2*sin(20*t)+3)*sin(t);
		 		z = 2*cos(20*t);
		 		glVertex3f(x,y,z);
			}	
		glEnd();
	glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutInit(&argc, argv);
    glutCreateWindow("Curva toroidal espiral");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutMouseFunc(raton);
    glutMotionFunc(girar);
    glutMainLoop();
    return 0;
}