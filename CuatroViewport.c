#include <gl/glut.h>
#include <math.h>
GLfloat aspecto = 1.6;
GLfloat ANCHO = 800;
GLfloat ALTO = 500;
GLshort grados=10;

//tomado del programa anteriormente realizado "pgc_t2_figuras.c" basado en el 
//pseudocodigo del algoritmo de Bresenham de la Dra. Carmen Villar
void dibuja8(int x, int y, int cX, int cY){ 
 glColor3ub(93, 169, 104); 
 glPointSize(2);  
 glBegin(GL_POINTS); 
  glVertex2i(cX+x, cY+y);  
  glVertex2i(cX-x,cY-y); 
  glVertex2i(cX-x,cY+y); 
  glVertex2i(cX+x,cY-y); 
  glVertex2i(cX+y,cY+x);  
  glVertex2i(cX-y,cY-x); 
  glVertex2i(cX-y,cY+x); 
  glVertex2i(cX+y,cY-x); 
 glEnd(); 
} 

//tomado del programa anteriormente realizado "pgc_t2_figuras.c" basado en el 
//pseudocodigo del algoritmo de Bresenham de la Dra. Carmen Villar
void dibujaCirculo(int radio, int centroX, int centroY){ 
 int x = 0; 
 int y = radio; 
 int d = 3-(2*radio); 
 while(x<=y){ 
  dibuja8(x,y, centroX, centroY); 
  if (d>0){ 
   d=d+4*(x-y)+10; 
   y=y-1;  
  }else{ 
   d=d+4*x+6; 
  } 
  x=x+1; 
 } 
} 

void ajusta(int ancho, int alto) {
	glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	/*AJUSTE DE PROPORCION DE ASPECTO
	se van a actualizar los Viewports porque están parametrizados*/
//si el nuevo aspecto > al aspecto actual de la ventana (ancho/alto):
    if (aspecto > (float)ancho/alto){
    	ANCHO = ancho; //actualizo variable global con el ancho actual
    	ALTO = ancho/aspecto; //actualizo variable global con la proporcion que le corresponde
	}else{ //si nuevo aspecto < aspecto actual
		ANCHO = alto*aspecto; //actualizo variable global con el ancho actual
    	ALTO = alto; //actualizo variable global con la proporcion que le corresponde
	}
	//cargo el resto de las configuraciones
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST); //habilito z-buffer	
}

void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3ub(201,152,236);
   	glLineWidth(2);
   	//------VIEWPORT GENERAL---------
   	glViewport(0,0,ANCHO,ALTO);
	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-ANCHO/2, ANCHO/2, -ALTO/2, ALTO/2, -100, 100); //400/250 = 1.6
   	//LINEAS DIVISORIAS
	glBegin(GL_LINES);
		glVertex3f(-ANCHO/2,0,0);//x
		glVertex3f(ANCHO/2,0,0);
		glVertex3f(0,-ALTO/2,0);//y
		glVertex3f(0,ALTO/2,0);
	glEnd();
   	//-------VIEWPORT ARRIBA IZQUIERDA - SENO-------
   	glViewport(0, ALTO/2, ANCHO/2, ALTO/2); //400/250=1.6
	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	gluOrtho2D(-3.5,3.5,-1.2,1.2);
   	glBegin(GL_LINE_STRIP);//Dibuja ejes
   		glColor3ub(0,0,0);
		glVertex3f(-ANCHO,0,0);//x
		glVertex3f(ANCHO,0,0);
		glVertex3f(0,-ALTO,0);//y
		glVertex3f(0,ALTO,0);
	glEnd();
 	glBegin(GL_LINE_STRIP);//dibuja función seno
 		glColor3ub(255,140,0); 
  		for (float x=-M_PI; x<=M_PI ; x+=0.10){ //rango de [-pi,pi]
			glVertex2f(x,sin(x));
  		} 
 	glEnd(); 
	//----VIEWPORT ARRIBA DERECHA - CURVA SENOIDAL------
   	glViewport(ANCHO/2, ALTO/2, ANCHO/2, ALTO/2); //400/250 = 1.6
	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-10,10,-6.25,6.25,-40,40);//20/12.5 = 1.6
   	//DIBUJA CURVA SENOIDAL 3D
   	float sx;
	float sy;
	float sz;
	glColor3ub(83, 129, 194);
	glLineWidth(1);
    glPushMatrix();
		glScalef(0.5,0.5,0.5);
		glRotatef(45,1,1,0);
		//glRotatef(45,0,1,0);
			for(sz = -10.0; sz<=10.0; sz+=0.3){
				glBegin(GL_LINE_STRIP); 
				for(sx = -10.0; sx<=10.0; sx+=0.3){
					sy = 12*((sin(sqrt(sx*sx+sz*sz)))/(sqrt(sx*sx+sz*sz)));
					glVertex3f(sx,sy,sz);
				}	
				glEnd();	
			}	
				
			for(sx = -10.0; sx<=10.0; sx+=0.3){
				glBegin(GL_LINE_STRIP);
				for(sz = -10.0; sz<=10.0; sz+=0.3){
					sy = 12*((sin(sqrt(sx*sx+sz*sz)))/(sqrt(sx*sx+sz*sz)));
					glVertex3f(sx,sy,sz);
				}	
				glEnd();	
			}
    glPopMatrix();

//-------------------------------------------
   	// VIEWPORT ABAJO DERECHA - CIRCULO BRESENHAM
   	//basado en el programa "pgc_t2_figuras.c"
   	glViewport(ANCHO/2, 0, ANCHO/2, ALTO/2); //400/250 = 1.6
	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	gluOrtho2D(-400,400,-250,250); //800/500 = 1.6
	//DIBUJA CIRCULO
   	dibujaCirculo(200,0,0);
//-------------------------------------------
	// VIEWPORT ABAJO IZQUIERDA - CURVA TOROIDAL ESPIRAL
	//basado en el programa "CurvaToroidalEspiral.c"
   	glViewport(0, 0, ANCHO/2, ALTO/2); //400/250 = 1.6
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-10,10,-6.25,6.25,-40,40); //20/12.5 = 1.6
   	//DIBUJA CURVA TOROIDE
   	float tx,ty,tz;
    glColor3ub(241,119,201);
    glLineWidth(1);
    glPushMatrix();
		glRotatef(135,1,0,0);
    	glBegin(GL_LINE_STRIP);
			for(float t=0; t<=(2*M_PI); t+=0.01){
				tx=(2*sin(20*t)+3)*cos(t);
		 		ty = (2*sin(20*t)+3)*sin(t);
		 		tz = 2*cos(20*t);
		 		glVertex3f(tx,ty,tz);
			}	
		glEnd();
	glPopMatrix();
//-------------------------------------------
	glutSwapBuffers();
}
void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(800,500); //800/500 = 1.6
    glutInitWindowPosition(400, 200);
    glutCreateWindow("Viewports y Proporcion de Aspecto");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}
   
