#include <gl/glut.h>
#include <stdio.h>
#include <malloc.h>

GLfloat  girax = 0, giray= 0;
GLboolean clic=GL_FALSE;
int gx, gy;
GLUquadricObj *cilindro;

//int ancho = 600, alto = 385; //fondo
int ancho = 736, alto = 1413; //fon8
//int ancho = 1400, alto = 700; //prueba de mario

unsigned char * datos;

//   Rotacion XY
void mover (void) {
    glRotated( girax, 1.0, 0.0, 0.0);
    glRotated( giray, 0.0, 1.0, 0.0);
}
void raton(int boton, int estado, int xv, int yv) {
    clic= boton==GLUT_LEFT_BUTTON && estado==GLUT_DOWN;
    if(clic){
        gx = xv;
        gy = yv;
    }
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

void leeImagen(){
   FILE * imagen;
   //imagen = fopen("../MarioBros/assets/cortinilla.data", "rb" );
   imagen = fopen("fon8.data", "rb" ); //aqui le indicamos que lee bytes
   if ( imagen == NULL ){ printf("archivo no encontrado"); exit(-1);}
   datos = (unsigned char *)malloc(ancho*alto*3);//reservo la memoria de mi estructura de datos 
   fread( datos, ancho * alto * 3, 1, imagen );//se guarda la img en datos
   fclose(imagen);
}

void cargaTextura(){
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos);
}

void myInit(){
	leeImagen();
	cargaTextura();
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    //-----------------FONDO----------------------
    glColor3ub(244, 205, 200);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0); glVertex3f(-26, -26, -45);
        glTexCoord2f(1.0, 1.0); glVertex3f( 26, -26, -45);
        glTexCoord2f(1.0, 0.0); glVertex3f( 26,  26, -45);
        glTexCoord2f(0.0, 0.0); glVertex3f(-26,  26, -45); 
    glEnd();
    glDisable(GL_TEXTURE_2D);

	GLUquadricObj *qobj;
	cilindro = gluNewQuadric();
    glPushMatrix();
        glTranslatef(0,-1,-10);
        glRotatef(90,0,1,0);
		mover();
	
		//-----------------CABEZA---------------------- 
		//----CABELLO--- 
		glPushMatrix();
        	glColor3ub(0,0,0);
        	glScalef(1.1,0.9,1.2);
        	glutSolidSphere(2,20,20);
        glPopMatrix();
        //----CARA---
        glPushMatrix();
	        glColor3ub(255, 226, 198);
	        glTranslatef(-1.4,-0.2,0);
	        glScalef(1,1.3,1.7);
	        glutSolidSphere(1,20,20);
        glPopMatrix();
		glColor3ub(179, 16, 42);
		//----LIGA IZQ---
        glPushMatrix();
	        glTranslatef(0,0.8,-2.3);
	        glRotatef(35,1,0,0);
	        glScalef(0.15,0.15,0.1);
	        glTranslatef(0,-0.8,2.3);//original
	        glutSolidTorus(1.3,3,20,20);
        glPopMatrix();
        //----LIGA DER---
        glPushMatrix();
	        glTranslatef(0,0.8,2.3);
	        glRotatef(-35,1,0,0);
	        glScalef(0.15,0.15,0.1);
	        glTranslatef(0,-0.8,-2.3);//original
	        glutSolidTorus(1.5,3,20,20);
        glPopMatrix();
        //----CHONGO IZQ---
        glColor3ub(0,0,0);
        glPushMatrix();
        	glTranslatef(0,3,-9);
        	glScalef(.7,.7,.7);
        	glTranslatef(0,-3,9);
	        glutSolidSphere(1.2,20,20);
        glPopMatrix();
        //----CHONGO DER---
        glPushMatrix();
        	glTranslatef(0,3,9); //posicion inical
        	glScalef(.7,.7,.7);
        	glTranslatef(0,-3,-9);//translado origen
	        glutSolidSphere(1.2,20,20);
        glPopMatrix();
	    
	    //-----------------CARA----------------------
	    //----OJO IZQ---
	    glPushMatrix(); 
	    	glTranslatef(-2.35,-0.4,0.4);
	    	glRotatef(-15,1,0,0);
	    	glScalef(1,1,1.8);
	    	cilindro = gluNewQuadric();
	    	gluQuadricDrawStyle(cilindro,GLU_FILL);
			gluCylinder(cilindro,0.05,0.05,0.5,20,20);
	    glPopMatrix();
	    //----OJO IZQ---	
	    glPushMatrix();
		    glScalef(1,1,-1);
		    glPushMatrix(); 
		    	glTranslatef(-2.35,-0.4,0.4);
		    	glRotatef(-15,1,0,0);
		    	glScalef(1,1,1.8);
		    	gluQuadricDrawStyle(cilindro,GLU_FILL);
				gluCylinder(cilindro,0.05,0.05,0.5,20,20);
		    glPopMatrix();
	    glPopMatrix();
	    //----MEJILLA DER---
	    glPushMatrix();
	    	glColor3ub(253, 111, 113);
	    	glTranslatef(-2,-0.8,0.85);
	    	glutSolidSphere(0.2,30,30);
	    glPopMatrix();
	    //----MEJILLA IZQ---
	    glPushMatrix();
	    glScalef(1,1,-1);
		    glPushMatrix();
		    	glColor3ub(253, 111, 113);
		    	glTranslatef(-2,-0.8,0.85);
		    	glutSolidSphere(0.2,30,30);
		    glPopMatrix();
	    glPopMatrix();
	    //----BOCA---
	    glColor3ub(0, 0, 0);
		glPushMatrix();
			glTranslatef(-2.25,-0.9,0);
			glRotatef(-90,0,1,0);//verlo de frente
			glRotatef(-25,1,0,0);//ver sólo una parte
		    gluQuadricDrawStyle(cilindro,GLU_FILL);
		    gluCylinder(cilindro,0.1,0.21,0.1,20,20);
	    glPopMatrix();
	    //----CEJA IZQ---
		glPushMatrix();
			glTranslatef(-2,0.2,-1.1);
			glRotatef(90,0,1,0);//verlo de frente
			glRotatef(-35,1,0,0);//ver sólo una parte
		    gluQuadricDrawStyle(cilindro,GLU_FILL);
		    gluCylinder(cilindro,0.45,0.5,0.1,20,20);
	    glPopMatrix();
	    //----CEJA DER---
	    glPushMatrix();
	    	glScalef(1,1,-1);
			glPushMatrix();
				glTranslatef(-2,0.2,-1.1);
				glRotatef(90,0,1,0);//verlo de frente
				glRotatef(-35,1,0,0);//ver sólo una parte
			    gluQuadricDrawStyle(cilindro,GLU_FILL);
			    gluCylinder(cilindro,0.45,0.5,0.1,20,20);
		    glPopMatrix();
	    glPopMatrix();

		//-----------------CUERPO----------------------
		//----VESTIDO--- 
		glColor3ub(248, 0, 0);
	    glPushMatrix();
	       	glTranslatef(0,-1.7,0); 
	       	glRotatef(90,1,0,0);
	       	glRotatef(-2,0,1,0);
		    gluQuadricDrawStyle(cilindro,GLU_FILL);
		    gluCylinder(cilindro,1,1.45,1.25,20,20);  	        
	    glPopMatrix();
	    
	    //----BRAZO Y MANO IZQUIERDA--
	    glPushMatrix();//mano izq
		    glTranslatef(0,-2.9,-1.9);
		    glPushMatrix();
		   		glColor3ub(255, 226, 198);
		   		glutSolidSphere(0.35,30,30);
			glPopMatrix();
	    glPopMatrix();
	    glPushMatrix();//brazo izq
	      	glColor3ub(248, 0, 0);
	       	glTranslatef(0,-2.8,-1.8);
	       	glRotatef(-52,1,0,0);
	       	glutSolidCone(0.4,1.5,20,20);
	    glPopMatrix();
		//----BRAZO Y MANO DERECHA--
	    glPushMatrix();
		    glScalef(1,1,-1);
		    glPushMatrix();//mano der
			    glTranslatef(0,-2.9,-1.9);
		        glPushMatrix();
		        	glColor3ub(255, 226, 198);
		        	glutSolidSphere(0.35,30,30);
		        glPopMatrix();
		    glPopMatrix();
		    glPushMatrix();//brazo der
		       	glColor3ub(248, 0, 0);
		       	glTranslatef(0,-2.8,-1.8);
		       	glRotatef(-52,1,0,0);
		       	glutSolidCone(0.4,1.5,20,20);
		    glPopMatrix();
	    glPopMatrix();
	    //----PIE IZQUIERDO--- 
	    glColor3ub(0,0,0);
	    glPushMatrix();
	       	glRotatef(-90,1,0,0);
	       	glTranslatef(0,0.4,-3.9);
	       	gluQuadricDrawStyle(cilindro,GLU_FILL);
		    gluCylinder(cilindro,0.3,0.3,0.6,20,20);
	    glPopMatrix();
	    glPushMatrix();
	       	glTranslatef(0,-4,-0.4);
	       	glutSolidSphere(0.3,30,30);
	    glPopMatrix();
		//----PIE DERECHO--- 
	    glPushMatrix();
		    glScalef(1,1,-1);
		    glPushMatrix();
			   	glRotatef(-90,1,0,0);
			   	glTranslatef(0,0.4,-3.9);
			   	gluQuadricDrawStyle(cilindro,GLU_FILL);
			    gluCylinder(cilindro,0.3,0.3,0.6,20,20);
			glPopMatrix();
			glPushMatrix();
			   	glTranslatef(0,-4,-0.4);
			   	glutSolidSphere(0.3,30,30);
			glPopMatrix();
	    glPopMatrix();	    
    glPopMatrix();    
    glutSwapBuffers();
}
void teclado(unsigned char key, int x, int y) {
   if(key==27) exit (0);
}

void ajusta(int ancho, int alto) {
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,1,50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHT0); //se enciende
	glEnable(GL_LIGHTING); //se conecta
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
       
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowPosition(500, 70);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Shelly Flores Lopez");
    myInit();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMouseFunc(raton);
    glutMotionFunc(girar);
    glutMainLoop();
    return 0;
}