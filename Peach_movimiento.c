/*---------------------------------------- INTRUCCIONES -----------------------------------
Anima y controla con las teclas de la flechas la dirección de movimiento continuo de tu figura pixel
a pixel. Cuando llega a un extremo lateral (izquierdo o derecho) se va ocultando hasta que empieza a
aparecer del otra lado. En el movimiento horizontal (arriba o abajo), no se puede salir de la ventana,
se queda estática cuando llega al borde.
 --------------------------------------------------------------------------------------*/
#include <GL/glut.h>
#include "princess.h"
#include <stdbool.h>

enum direccion{ izq, der, arriba, abajo };
enum direccion direccion= abajo;
//float velX=0.1, velY=0.1; //ajustar la cantidad de píxeles que Peach se mueve cada vez que se ejecuta mueveImg()
int contador = 0;
int x=0, y= 0;
int xd=0, yd= 0;
int xpos,ypos;
int xposd,yposd;
bool doble =false;

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}


void dibujaPrincess(){
	int size= 4;
	glPointSize(size);
	glBegin(GL_POINTS);
		for (int i=0; i<ALTO; i++){
			for(int j=0 ; j<ANCHO; j++){
				glColor3ubv(paleta1[princess[i][j]]);
				xpos= 65+j*size+x;
				ypos= 460-i*size+y;
				glVertex2i(xpos, ypos);
			}
		}
		if (doble == true){
			for (int i=0; i<ALTO; i++){
			for(int j=0 ; j<ANCHO; j++){
				glColor3ubv(paleta1[princess[i][j]]);
				xposd= 65+j*size+xd;
				yposd= 460-i*size+yd;
				glVertex2i(xposd, yposd);	
		}}}
	glEnd();	
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    dibujaPrincess();
    glutSwapBuffers();
}

void mueveImg(){
	if (contador>7){
		/*la y debe ser menos a esa cantidad porque la y que se mueve es la y de la base*/
		if(direccion == arriba && ypos<=284)
			//y+= velY;
			y++;
		if(direccion == abajo && ypos>=0)
			//y-= velY;
			y--;
		if(direccion == der){
			doble= true;
			x++;
			xd= x-640;
			yd= y;
			/*sin esta parte cuando la doble acaba la vuelta, ya no sale nada
			entonces lo que se hace es que se reinicia*/
			if(x>=640){ //cuando main peach sale
				x=xd; //main peach se actualiza a second peach
				xd=x-640;
				//doble=false;
			}	
		}
		
		if(direccion == izq){
			doble= true;
			x--;
			xd=x+640;
			yd= y;
			
			if(x<=-150){
				x=xd;
				xd=x+640;
				//doble=false;
			}		
		}
		contador = 0;	
	}contador ++;
	glutPostRedisplay();
	//glutIdleFunc(mueveImg);	
		
}

void escogeDireccion(int tecla){
	switch(tecla){
		case GLUT_KEY_UP: direccion = arriba; break;
		case GLUT_KEY_DOWN: direccion = abajo; break;
		case GLUT_KEY_LEFT: direccion = izq; break;
		case GLUT_KEY_RIGHT: direccion = der; break;	
	}	
}


void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Peach");
    glutReshapeFunc(ajusta);
    glutSpecialFunc(escogeDireccion);
    glutIdleFunc(mueveImg);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}