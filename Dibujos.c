#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include "princess.h"
#include "toad.h"
#define num_puntos 15
#define radio1 91
#ifndef pi
#define pi 3.141592
#endif


void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

struct punto{
	float x;
	float y;
};

typedef struct punto Punto;
//Almacenamos los puntos en un arreglo
Punto puntos[num_puntos];

void dibujaNombre(void *tipo, char *s ) {
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

void dibujaIlusionCurvas(int high, int low, int interval, int CoordX, int CoordY) {
    glLineWidth(1);
    
    glColor3ub(255, 0, 125); //// Cuadrante superior derecho
    glBegin(GL_LINES);
    for (int i = high; i > (low + 1); i -= interval) {
        glVertex2i(CoordX, i + CoordY);
        glVertex2i((high + interval + CoordX) - i, low + CoordY);
    }
    glEnd();
    glColor3ub(255, 125, 0); //Cuadrante superior izquierdo
    glBegin(GL_LINES);
    for (int i = high; i > (low + 1); i -= interval) {
        glVertex2i(CoordX, i + CoordY);
        glVertex2i(i - (high - interval - CoordX), low + CoordY);
    }
    glEnd();
    glColor3ub(255, 125, 0); //Cuadrante inferior derecho
    glBegin(GL_LINES);
    for (int i = 0; i < (low + 1); i += interval) {
        glVertex2i(CoordX, i + CoordY);
        glVertex2i(CoordX + i, low + CoordY);
    }
    glEnd();
    glColor3ub(255, 0, 125); // Cuadrante inferior izquierdo
    glBegin(GL_LINES);
    for (int i = 0; i < (low + 1); i += interval) {
        glVertex2i(CoordX, i + CoordY);
        glVertex2i(((0-i)+CoordX), low + CoordY);
    }
    glEnd();
}

void dibuja8(int x, int y, int cX, int cY){
	glColor3ub(0,255,0);
	glPointSize(3); 
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
		x++;
	}
	/*if(x==y){
		dibuja8(x,y,centroX, centroY);
	}*/
}

void dibujaCuadricula(){
	glLineWidth(2);
	glColor3ub(0,0,0);
	glBegin(GL_LINES);
		//primera linea vertical larga
		glVertex2i(213,0);
		glVertex2i(213,480);
		//segunda vertical larga
		glVertex2i(426,0);
		glVertex2i(426,480);
		//linea horizontal larga
		glVertex2i(0,240);
		glVertex2i(640,240);
		//eje x para seno
		glVertex2i(430,360);
		glVertex2i(636,360);
		//eje y para seno
		glVertex2i(533,250);
		glVertex2i(533,470);		
	glEnd();
}


void dibujaPrincess(){
	int size= 4;
	glPointSize(size);
	glBegin(GL_POINTS);
		for (int i=0; i<ALTO; i++){
			for(int j=0 ; j<ANCHO; j++){
				glColor3ubv(paleta1[princess[i][j]]);
				glVertex2i(65+j*size, 460-i*size);
			}
		}
	glEnd();	
}

void dibujaToad(){
	int tam=5;
	glPointSize(tam);
	glBegin(GL_POINTS);
   for (int i=0 ; i< ALTOT; i++)
       for (int j=0 ; j< ANCHOT; j++){
           glColor3ubv(paleta1t[toad[i][j]]);
           glVertex2i(60+j*tam,190-i*tam);
   }
   glEnd();
}

void calculaPuntosCircunferencia(){
	glPointSize(4);
	//Se transforma coordenadas polares a coordenadas cartesianas
	for (int i=0; i<=14; i++){
		//circulo =360 grados= 2pi radianes
		//float anguloRad= ((24*(i+1))*pi)/180; //otra opción
		float anguloRad= 2*pi*i/15;
		//obteniendo coordenadas cartesianas
		puntos[i].x	= radio1*cos(anguloRad);
		puntos[i].y = radio1*sin(anguloRad);
		/*glBegin(GL_POINTS);
			glVertex2i(puntos[i].x + 318, puntos[i].y+ 365);
		glEnd();*/
	}
}

void dibujaLineas(){		
	for(int i=0; i< num_puntos; i++){
		for(int j= i+1; j<num_puntos ; j++){
		    glBegin(GL_LINES);        
				glVertex2i( puntos[i].x+318, puntos[i].y+365 );
				glVertex2i( puntos[j].x+318, puntos[j].y+365);
			glEnd();	
		}
	}	
}

void Seno(int px, int py){
	glBegin(GL_LINE_STRIP);
	glColor3ub(255,140,0);
		for (float i=-pi; i<=pi ; i+=0.10){
			//y = sen(x)
			float y = sin(i);
			//escalamos y posicionamos
			float xe = (i/pi)*100 + px ;
			float ye = y * 100 + py;
			glVertex2i(xe,ye);
			
		}
	glEnd();
}


void dibuja(void) {
	int R = 80;
	int Xcentro = 530;
	int Ycentro = 130;
	int alto = 200;
	int bajo = 100;
	int intervalo = 5;
	int cXilusion = 318;
	int cYilusion = 30;
    glClear(GL_COLOR_BUFFER_BIT);
    //dibujaPez();
    dibujaPrincess();
    dibujaCuadricula();
    Seno(533, 360);
    glColor3ub(0,65,192);
	glRasterPos2i(90,250);
    dibujaNombre(GLUT_BITMAP_TIMES_ROMAN_10,"Flores");
    glColor3ub(0,192,6);
	glRasterPos2i(90,15);
    dibujaNombre(GLUT_BITMAP_TIMES_ROMAN_10,"Zinser");
    glColor3ub(255,0,112);
    glLineWidth(1);
    calculaPuntosCircunferencia();
    dibujaLineas();
	dibujaCirculo(R,Xcentro,Ycentro);
	dibujaIlusionCurvas(alto, bajo, intervalo, cXilusion, cYilusion);
	dibujaToad();
    glFlush();
}
void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Tarea 2 Flores_Zinser");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}