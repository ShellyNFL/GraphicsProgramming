/*-----------------------------------INTRUCCIONES------------------------------
 Dibuja tres dodecágonos grises que cambien de color emulando a un semáforo.
 El verde y rojo duran lo mismo, el amarillo menos y el verde antes de cambiar
 a amarillo “parpada” un par de veces.
 ------------------------------------------------------------------------------*/
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>


//Prototipos de las funciones
void estadoInicial();
void estadoIntermedio();
void estadoFinal();
void temporizador();
void parpadeo();


int radio=45; 
GLubyte paleta[4][3]={ {202,202,202},{255,0,0},{255,251,0},{0,255,0} };
enum colores{gris, rojo, amarillo, verde};
//bool final = true;

int tiempoRV = 3000;//tiempo para rojo y verde
int tiempoA= 1800; //tiempo para amarillo
int tiempoParpadeo = 250;
int parpadeosRestantes = 8;

//se crea directamente el alias para la estructura
typedef struct{
	int x, y;
	int tiempo;	
	enum colores color;
}Dodecaedro;

//3 dodecaedros
Dodecaedro dodecaedro[3];


void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void figura(float x, float y, int seg){
   glBegin(GL_POLYGON);
   	//grados a grad = angulo * (pi/180)
     for(int i=0; i<=360; i+=360/seg)
        glVertex2i(x+radio*cos(i*M_PI/180),y+radio*sin(i*M_PI/180));
   glEnd();
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i=0 ; i<3; i++){
    	glColor3ubv(paleta[dodecaedro[i].color]);
    	figura(dodecaedro[i].x, dodecaedro[i].y ,12); //aquí se le indica que quiero la fig de 12 lados
	}
	glutPostRedisplay();
  	glutSwapBuffers();
}


//si no se inicializa, dibuja algo raro antes de empezar la función de semáforo
void inicializaDodecagonos() {
    for (int i = 0; i < 3; i++) {
        dodecaedro[i].x = 330;
        dodecaedro[i].y = 360 - i * 100;
        dodecaedro[i].color = gris;
    }
    dodecaedro[0].color = rojo;
}

void estadoInicial(){
	/*Aunque los literales compuestos permiten inicializar estructuras en cualquier lugar del código
	 necesitan estar precedidos por un cast al tipo de la estructura.*/
	dodecaedro[0] = (Dodecaedro){320, 360, 3000, rojo};
	dodecaedro[1] = (Dodecaedro){320, 260, 3000, gris};
	dodecaedro[2] = (Dodecaedro){320, 160, 3000, gris};
	glutPostRedisplay();
	glutTimerFunc(tiempoRV,estadoFinal,1);
}

void estadoIntermedio(){
	dodecaedro[0] = (Dodecaedro){320, 360, 2000, gris};
	dodecaedro[1] = (Dodecaedro){320, 260, 2000, amarillo};
	dodecaedro[2] = (Dodecaedro){320, 160, 2000, gris};
	//glutPostRedisplay();
	/*if(final){
		glutTimerFunc(tiempoA,estadoFinal,1);
		final = !final;
	}
	else */
		glutTimerFunc(tiempoA,estadoInicial,1);
		//final = !final;
}

void estadoFinal(){
	dodecaedro[0] = (Dodecaedro){320, 360, 3000, gris};
	dodecaedro[1] = (Dodecaedro){320, 260, 3000, gris};
	dodecaedro[2] = (Dodecaedro){320, 160, 3000, verde};
	//glutPostRedisplay();
	glutTimerFunc(tiempoRV,parpadeo,1);
}

void parpadeo(){
	if(dodecaedro[2].color == verde)
		dodecaedro[2].color = gris;
	else	
		dodecaedro[2].color = verde;
	parpadeosRestantes--;
	//glutPostRedisplay();
	
	if (parpadeosRestantes>0)	
		glutTimerFunc(tiempoParpadeo,parpadeo,1);
	else{
		parpadeosRestantes = 8;
		glutTimerFunc(0,estadoIntermedio,1);
		//final = false;
	} //si ya no quedan parpadeos pasa al rojo
			
}

void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}
int main(int argc, char** argv) {
	inicializaDodecagonos();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Semaforo");
    glutReshapeFunc(ajusta);
    glutTimerFunc(100,estadoInicial,1);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}