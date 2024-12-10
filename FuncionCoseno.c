#include <GL/glut.h>
#include <math.h>
#ifndef MPI //si no está def PI 
#define MPI 3.141592
#endif

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION); //Selecciona la matriz de proyección
    glLoadIdentity();
    //permite definir un rango de coordenadas en el que se dibujaran los objetos 2d
    gluOrtho2D(0,640,0,480); //define una proyeccion en 2D
	 
}

/*Por la configuración de pixeles y cordenadas podemos decir que
1 pixel corresponde a un espacio de cordenadas, entonces si se quiere dejar 
un espacio de 16 pixeles se tiene que hacer un salto de 16 unidades. */
void convierteCuadriculado(){
	//lineas verticales
	//DUDA Por qué si glLineWidth está dentro de la función afecta a todo
	glLineWidth(2);
	for(int i=0; i<=640 ; i+=16 ){
			glBegin(GL_LINES);
				glVertex2i(i,0);
				glVertex2i(i,480);
			glEnd();
			
	}
	//lineas horizontales
	for(int j=0; j<=480 ; j+=16 ){
			glBegin(GL_LINES);
				glVertex2i(0,j);
				glVertex2i(640,j);
			glEnd();
	}
				
}

void coseno(){
	//podemos graficarlo en 0 y después moverlo
	glBegin(GL_LINE_STRIP);
	for(float i= -MPI; i<=MPI; i+=0.10){
		float y=cos(i);
		/*hay que escalar
		originalmente x va de -pi a pi entonces divido entre pi
		para que el dominio sea de -1 a 1 */
		float xe= (i/MPI)*320+320;
		float ye=y*180+240;
		glVertex2f(xe,ye);
	}
	glEnd();
	
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
	glEnable(GL_LINE_STIPPLE);
	glColor3ub(0,95,255);
	glLineStipple(1,0x1F1F);
    convierteCuadriculado();
    glDisable(GL_LINE_STIPPLE);
    
    //eje y
    glColor3ub(0,0,0);
    glBegin(GL_LINES);
    	glVertex2i(320,0);
    	glVertex2i(320,480);
    glEnd();
    
    //eje x
    glColor3ub(0,0,0);
    glBegin(GL_LINES);
    	glVertex2i(0,240);
    	glVertex2i(640,240);
    glEnd();
    
    //graficamos coseno
    glColor3ub(255,0,0);
    glLineWidth(3);
	coseno();	 
    glFlush();
}


void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480); //este es el número de pixéles de nuestra ventana
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Funcion Coseno");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}