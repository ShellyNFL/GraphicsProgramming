#include <GL/glut.h>
#include <stdbool.h>

//Propiedades luz
float luz_ambiente [] = {0.5,0.7,0,0};
float luz_difusa [] = {1,1,1,0};
float luz_posicion [] = {0,3,0,1}; //para posicional
float luz_posicion_dir [] = {0,3,0,0}; //para direccional
//Propiedades material tetera y esfera
//esto le da el color que tiene la tetera y la esfera
float mat_ambiente [] = {.3,0,0,1};
float mat_difuso [] = {.5,0,0,1};
float mat_especular [] = {.8,.8,0,1};
float mat_emision [] = {0,0,0,1};
float mat_brillo = 64;
//Propiedades material esfera-foco
float foco_ambiente_difusa [] = {1,1,.1,0};
float foco_emision [] = {0.5,0.5,0,0};


int caso=3;

void dibujaNombre(void *tipo, char *s ) {
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

void luzPosicionalPuntual(){
	float dir_foco[]= {0,0,-1};
	glLightfv(GL_LIGHT0,GL_POSITION,luz_posicion);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,dir_foco);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,180);//cuenta como la luz direccional (sin foco)
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,0);	
	
	/*glPushMatrix();  //foco
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,foco_ambiente_difusa);
		glMaterialfv(GL_FRONT,GL_EMISSION,foco_emision);
		glTranslatef(0,3,0);
		glutSolidSphere(.35,15,15);
	glPopMatrix();*/
}


void luzPosicionalFocal(){
	float dir_foco[]= {0,-3,0};
	glLightfv(GL_LIGHT0,GL_POSITION,luz_posicion);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,dir_foco);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,90);
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,1);     
}

void luzDireccional(){
	glLightfv(GL_LIGHT0,GL_POSITION,luz_posicion_dir);	
}

void ajusta(int ancho, int alto) {
	 //valor de atenuación
	glClearColor(0.9,0.9,0.9,0.0);
	glLightfv(GL_LIGHT0,GL_AMBIENT,luz_ambiente);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,luz_difusa);
	glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,.8);//constant y cuadratic toma el default
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3,3,-1.5,3.5,-3,3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void dibuja(void)  {
	glClear(GL_COLOR_BUFFER_BIT);
	switch(caso){
	case 1:
		glRasterPos3f(-1, 1.5, 0);
    	dibujaNombre(GLUT_BITMAP_HELVETICA_18, "Direccional");
		for (int i=0; i<3 ;i++){
			glPushMatrix();
				glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,foco_ambiente_difusa);
				glMaterialfv(GL_FRONT,GL_EMISSION,foco_emision);
				glTranslatef(0,2.5,0);
				glTranslatef(i-1,0.5,0); 
				glScalef(.1,1,1);
				glutSolidCube(1);
			glPopMatrix();
		}
		break;
	case 2:
		glRasterPos3f(-1.5, 1.5, 0);
    	dibujaNombre(GLUT_BITMAP_HELVETICA_18, "Posicional Focal");
    	glPushMatrix();  //foco
			glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,foco_ambiente_difusa);
			glMaterialfv(GL_FRONT,GL_EMISSION,foco_emision);
			glTranslatef(0,2.5,0);
			glRotatef(-90,1,0,0);
			glutSolidCone(1,1.5,15,15);
		glPopMatrix();
		break;
	case 3:
		luzPosicionalPuntual();
		glRasterPos3f(-1.5, 1.5, 0);
    	dibujaNombre(GLUT_BITMAP_HELVETICA_18, "Posicional Puntual");
		glPushMatrix();  //foco
			glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,foco_ambiente_difusa);
			glMaterialfv(GL_FRONT,GL_EMISSION,foco_emision);
			glTranslatef(0,3,0);
			glutSolidSphere(.45,15,15);
		glPopMatrix();
		break;
	}
	glPushMatrix();  //esfera
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambiente);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_difuso);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_especular);
		glMaterialfv(GL_FRONT,GL_EMISSION,mat_emision);
		glMaterialf(GL_FRONT,GL_SHININESS,mat_brillo);
		glTranslatef(2.4,2,0);
		glutSolidSphere(.4,20,20);
	glPopMatrix();
	glutSolidTeapot(1.3);  //tetera
	glFlush();
}

void teclado(unsigned char tecla, int x, int y){
	switch (tecla) {
    	case 27: exit(0);
		case 49:
            luzDireccional();
            caso = 1;
    		break;
      	case 50:
      		luzPosicionalFocal();
			caso = 2;
			break;
		case 51:
			luzPosicionalPuntual();
			caso =3;
			break;
		default: break;
   }
   glutPostRedisplay();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(20,20);
	glutInitWindowSize(300,250);
	glutCreateWindow("Tipo de luces");
	glutDisplayFunc(dibuja);
	glutReshapeFunc(ajusta);
	glutKeyboardFunc (teclado);
	glutMainLoop();
	return 0;
}