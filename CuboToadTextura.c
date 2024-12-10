//Ariadne Zinser Trigos y Shelly Flores Lopez - 00282331 y 00372578 - Cubo Textura Toad
//Base de codigo (proyeccion y perspectiva, con funcion para mover) tomada del programa "proyecciones.c" de la Dra. Carmen Villar
//funciones de raton y conceptos de rotacion tomadas del programa anterior "pgc_p4e4_Pinza.c"
//conceptos de jerarquia tomados de "jerarquia.c" de la Dra. Carmen Villar y del programa anterior "pgc_p4e4_Pinza.c"
////Base de codigo: tomada de "ejTextura.c" y del codigo 19 "TexProcedural.c" de la Dra. Carmen Villar.

#include <GL/glut.h>
#include "toad_paleta.h"
#define  anchoTextura 32
#define  altoTextura 32

float anguloRot =0; //angulo de rotacion para cerrar los cuadrados (debe llegar a 90 grados)
GLfloat  girax = 0, giray= 0, zoom=0;
GLubyte imagen[altoTextura][anchoTextura][3]; //almacena a mi textura

void myinit(void){
	float luzPF_posicion [] = {3,1,10,1}; //posicion 3 a la derecha, 1 hacia arriba y 10 hacia adelante, se indica con w=1 que son posicionales)
	float luzF_direccion[]={2,-1,0}; //hacia abajo y hacia la derecha
	float luces_ambiente [] = {1.0,1.0,1.0,0}; //luz blanca (se ignora alfa porque es luz)
	float luces_difusa [] = {1,1,1,0}; //blanca
	glLightfv(GL_LIGHT0,GL_AMBIENT,luces_ambiente); //su ambiente es luces_ambiente, misma para las 3 luces
	glLightfv(GL_LIGHT0,GL_DIFFUSE,luces_difusa); //su ambiente es luces_difusa
	glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,.8); //usa 0.8 (solo un valor, por lo que se usa glLightf no fv, linear y quadratic son por default 0
	glLightfv(GL_LIGHT0,GL_POSITION,luzPF_posicion); //w=1
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,luzF_direccion); //reseteo esta propiedad a sus valores default
 	glFrontFace(GL_CW);
 	glEnable(GL_LIGHTING);
 	glEnable(GL_LIGHT0);
 	glEnable(GL_NORMALIZE);
}

void creaTexturas(void){ 
  for (int i=0; i<altoTextura; i++) //funcion para convertir dims de matriz en potencias de 2 (32) tomada de la Dra. Carmen Villar
     for (int j=0; j<anchoTextura; j++){ //columnas
       imagen[i][j][0]=(i<ALTOT && j<ANCHOT)?paleta1t[toad[i][j]][0]:paleta1t[0][0]; //agrega el color, si no, agrega un fondo
       imagen[i][j][1]=paleta1t[(i<ALTOT && j<ANCHOT)?toad[i][j]:0][1]; //ternario metido adentro de los corchetes
       imagen[i][j][2]=paleta1t[(i<ALTOT && j<ANCHOT)?toad[i][j]:0][2];
     }
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST); //cuando lo tenga que magnificar usa nearest
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST); //cuando lo tenga que minimizar usa linear
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoTextura,altoTextura, //textura en 2d, maximo nivel de detalle 0, gl_rgb, ancho 32, alto 32, 0 borde,
  																	// formato rgb, tipo de dato matriz, nombre matriz que es apuntador
                              0, GL_RGB, GL_UNSIGNED_BYTE, imagen); //puntero_text es imagen, el nombre de la matriz que contiene la textura
}


void mover(void) {
    glTranslated( 0, 0, zoom);
    glRotated( giray, 0.0, 1.0, 0.0);
    glRotated( girax, 1.0, 0.0, 0.0);
}
void raton(int boton, int estado, int x, int y){
		if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
   			//AQUI VA LOGICA PARA CERRAR (armar) CON CLIC IZQUIERDO
   			if(anguloRot>-90){ //90 grados dado que las caras son ortogonales/perpendiculares entre si
     				anguloRot = anguloRot - 10; //en decrementos de 10 grados
     				//printf("\nAngulo rotacion: %f", anguloRot);
		 	}
   		}
   		
   		if(boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN){
   			//AQUI VA LOGICA PARA ABRIR (desarmar) CON CLIC DERECHO
   			if(anguloRot<0){ 
     				anguloRot = anguloRot + 10;
     				//printf("\nAngulo rotacion: %f", anguloRot);
		 	}
   		}
   glutPostRedisplay();
}
void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();//PUSH TOTAL
        mover();
    	//---------------------------------------------------------------
    	//PARTE SUPERIOR
    	//primer cuadrado (vertical primero)
    	glRotatef(45,1,0,0); //roto toda la figura para que nazca de frente, y se note que hay perspectiva (por eso 45 y no 90)
    	glPushMatrix(); //PUSH rota cuadrado 1
    		glTranslatef(0.0,0.0,0.0);
    		glRotatef(-anguloRot,1,0,0); //roto respecto de x
    		glTranslatef(0.0,0.0,0.0);
    		
    		glPushMatrix(); //PUSH dibuja cuadrado 1
				glBegin(GL_QUADS);
        			glTexCoord2f(0.0, 0.0); glVertex3f (0.0,0.0,0.0); 
					glTexCoord2f(1.0, 0.0); glVertex3f (5.0,0.0,0.0);
        			glTexCoord2f(1.0, 1.0); glVertex3f (5.0,0.0,-5.0); 
					glTexCoord2f(0.0, 1.0); glVertex3f (0.0,0.0,-5.0);
				glEnd();
			glPopMatrix();//POP dibuja cuadrado 1
		glPopMatrix();//POP rota cuadrado 1
		
		//---------------------------------------------------------------
		//segundo cuadrado (vertical segundo, CENTRAL PIVOTE en el origen), NO ROTA
    	glPushMatrix(); //PUSH dibuja cuadrado 2
			glBegin(GL_QUADS); //amarillo pastel
        		glTexCoord2f(2.0, 0.0); glVertex3f (0.0,0.0,0.0); //repite textura 2 veces en s
				glTexCoord2f(2.0, 1.0); glVertex3f (0.0,0.0,5.0); 
        		glTexCoord2f(0.0, 1.0); glVertex3f (5.0,0.0,5.0); 
				glTexCoord2f(0.0, 0.0); glVertex3f (5.0,0.0,0.0); 
				
			glEnd();
		glPopMatrix(); //POP dibuja cuadrado 2
		
		//---------------------------------------------------------------
		//LATERAL IZQ
		//tercer cuadrado (lateral izquierdo)
    	glPushMatrix(); //PUSH rota cuadrado izq
    		glTranslatef(0.0,0.0,0.0);
    		glRotatef(anguloRot,0,0,1); //roto respecto de z
    		glTranslatef(0.0,0.0,0.0);
    		
    		glPushMatrix();
				glBegin(GL_QUADS); //PUSH dibuja cuadrado izq
					glTexCoord2f(0.0, 0.0); glVertex3f (-5.0,0.0,0.0); 
					glTexCoord2f(3.0, 0.0); glVertex3f (-5.0,0.0,5.0); //repite textura 3 veces en s
        			glTexCoord2f(3.0, 1.0); glVertex3f (0.0,0.0,5.0); 
					glTexCoord2f(0.0, 1.0); glVertex3f (0.0,0.0,0.0);
				glEnd();
			glPopMatrix();//POP dibuja cuadrado izq
		glPopMatrix();//POP rota cuadrado izq
		
		//---------------------------------------------------------------
		//LATERAL DER
		//cuarto cuadrado (lateral derecho)
		glPushMatrix(); //PUSH rota cuadrado der
    		glTranslatef(5.0,0.0,0.0);
    		glRotatef(-anguloRot,0,0,1);//roto respecto de z, direccion opuesta
    		glTranslatef(-5.0,0.0,0.0);
    		
    		glPushMatrix(); //PUSH dibuja cuadrado der
				glBegin(GL_QUADS);			
					glTexCoord2f(2.0, 2.0); glVertex3f (5.0,0.0,0.0); //repite textura 2 veces en s y 2 en t
					glTexCoord2f(0.0, 2.0); glVertex3f (5.0,0.0,5.0);
        			glTexCoord2f(0.0, 0.0); glVertex3f (10.0,0.0,5.0); 
					glTexCoord2f(2.0, 0.0); glVertex3f (10.0,0.0,0.0);
					glEnd();
			glPopMatrix();//POP dibuja cuadrado der
		glPopMatrix();//POP rota cuadrado der
		
		//---------------------------------------------------------------
		//PARTE INFERIOR
		//quinto cuadrado (vertical penultimo)
			glPushMatrix(); //PUSH rota parte inferior
    			glTranslatef(0.0,0.0,5.0);
    			glRotatef(anguloRot,1,0,0); //rota respecto del eje x
    			glTranslatef(0.0,0.0,-5.0);
    		
    			glPushMatrix(); //PUSH dibuja cuadrado 5
					glBegin(GL_QUADS);		
						glTexCoord2f(0.0, 0.0); glVertex3f (0.0,0.0,5.0);
						glTexCoord2f(4.0, 0.0); glVertex3f (0.0,0.0,10.0); //repite textura 4 veces en s y 4 veces en t
						glTexCoord2f(4.0, 4.0); glVertex3f (5.0,0.0,10.0);
						glTexCoord2f(0.0, 4.0); glVertex3f (5.0,0.0,5.0);
					glEnd();
				glPopMatrix(); //POP dibuja cuadrado 5
				
				//sexto cuadrado (vertical ultimo)
				glPushMatrix(); //PUSH rota cuadrado 6 (depende del giro del 5, se mueve con el)
						glTranslatef(0.0,0.0,10.0);
    					glRotatef(anguloRot,1,0,0); //rota respecto del eje x
    					glTranslatef(0.0,0.0,-10.0);	
							
						glPushMatrix(); //PUSH dibuja cuadrado 6
							glBegin(GL_QUADS);
								//glColor3f(0.99, 0.85, 0.70);
								glTexCoord2f(3.0, 0.0); glVertex3f (0.0,0.0,10.0); //repite 3 veces en s y 3 veces en t
								glTexCoord2f(3.0, 3.0); glVertex3f (0.0,0.0,15.0);
        						glTexCoord2f(0.0, 3.0); glVertex3f (5.0,0.0,15.0); 
								glTexCoord2f(0.0, 0.0); glVertex3f (5.0,0.0,10.0);	
    						glEnd();
						glPopMatrix(); //POP dibuja cuadrado 6
				glPopMatrix(); //POP rota cuadrado 6 (depende del giro del 5, se mueve con el)
		glPopMatrix();//POP rota parte inferior
    glPopMatrix();//POP TOTAL
    glutSwapBuffers();
}

void rotar(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT: giray-= 15; break;
    case GLUT_KEY_RIGHT:giray+= 15; break;
    case GLUT_KEY_UP:   girax -= 15; break;
    case GLUT_KEY_DOWN: girax += 15; break;
  }
  glutPostRedisplay();
}
void ajusta(int ancho, int alto) {
	//declaro la pila de matrices de modelo
	glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,10,100); //45 grados de apertura, 1 proporcion de aspecto, va de -10 a -100 pero los valores se esciben positivos 
    zoom= -40;
 	glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST); //habilito z-buffer
}
int main(int argc, char** argv) {
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH); //le aviso a la tarjeta grafica que voy a usar z-buffer
    //no puse proyeccion, entonces esta en ortho por default de -1 a 1 en los 3 ejes
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500); //USAR EL TAMANO DE VENTANA QUE QUIERA, EN FUNCION DE LA PROPORCION DEL ASPECTO. 
    glutInit(&argc, argv);
    glutCreateWindow("Cubo de papel con Textura");
    creaTexturas(); //carga la textura
    myinit(); //inicializa iluminacion
    glutMouseFunc(raton);
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutSpecialFunc(rotar);
    glutMainLoop();
    return 0;
}
