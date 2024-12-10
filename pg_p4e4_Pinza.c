#include <gl/glut.h>

//declaro un objeto cuadrático llamado cilindro
GLUquadricObj *cilindro;
float aumentoX= 0.0, angulo = 0.0, anguloGiro = 0.0;

void ajusta(int ancho, int alto) {
    glClearColor(1.0,1.0,1.0,0.0);	// color de background blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-10,10,10,-10); //el 0,0,0 está  en el centro de la ventana
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}
void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPointSize(5);
	glColor3ub(0,0,0);
	glPushMatrix();
		glTranslatef(aumentoX,0,0);
		glPushMatrix();
			glRotatef(anguloGiro,0,1,0);
			//hacemos el movimiento de toda la pinza
			cilindro = gluNewQuadric();
			glPushMatrix();
			/*NOTAS cuando ya te dibuja una figura la posiciona en el centro de las coordenadas*/
				//definimos el estilo del cilindro
				gluQuadricDrawStyle(cilindro, GLU_FILL);
				glTranslatef(0, 9, 0);
				glRotatef(90, 1, 0, 0); // Roto para poder ver la figura del cilindro
				glColor3ub(255,0,0);
				/*si los números de radioBase (la primera que vemos) y radioTapa (la de atrás)
				son iguales, será un cilindro con el mismo radio siempre, sino se irá viendo 
				similar a un embudo */
				gluCylinder(cilindro,0.5,0.5,12,20,20);
			glPopMatrix();
			
			glPushMatrix(); //cuadrado izquierdo
				glTranslatef(-0.2,-2.8,0);
				glRotatef(-angulo,0,0,1);
				glTranslatef(0.2,2.8,0);
				glPushMatrix();
					glTranslatef(-0.20,-4.5,0);
					glScalef(0.20,3,0.7);
					glColor3ub(0,0,0);
					glutSolidCube(1);
				glPopMatrix();
			glPopMatrix();
	
			/*glBegin(GL_POINTS);
				glColor3ub(0,0,0);
				glVertex3f(0.2,-2.8,0);
			glEnd();*/
	
			glPushMatrix(); //cuadrado derecho
				glTranslatef(0.2,-2.8,0); //en esta parte se está declarando el pto pivote
				glRotatef(angulo,0,0,1);
				glTranslatef(-0.2,2.8,0);
				glPushMatrix();
					glTranslatef(0.20,-4.5,0);
					glScalef(0.20,3,0.7);
					glColor3ub(0,0,255);
					glutSolidCube(1);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix(); //mover toda la pinza
	gluDeleteQuadric(cilindro);
	
		//segmentos son gajos de la naranja 
		//paralelos pilas son los horizontales
    
	glutSwapBuffers();
}

void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}
void flechas(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT:  aumentoX -= 0.5; break;
    case GLUT_KEY_RIGHT: aumentoX += 0.5; break;
    case GLUT_KEY_F2: //abren las pinzas
	    if (angulo >= 50) angulo = 50;
	    else angulo += 10;
		break;
	case GLUT_KEY_F1: //cierran las pinzas
		if (angulo <= 0) angulo = 0;
    	else angulo -= 10;
		break;
    case GLUT_KEY_F5: //giran
    	if(anguloGiro>=360) anguloGiro = 0;
    	else anguloGiro += 10;
		break;
  }
  glutPostRedisplay();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(480,480);
    glutInitWindowPosition(400, 200);
    glutCreateWindow("Pinzas");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(salir);
    glutSpecialFunc(flechas);
    glutMainLoop();
    return 0;
}