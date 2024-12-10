#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

//Prototipo
void parpadeo();

GLubyte paleta[4][3]={ {202,202,202},{255,0,0},{255,251,0},{0,255,0} };
enum colores{gris, rojo, amarillo, verde};

int tiempoRV = 4000;//tiempo para rojo y verde
int tiempoA= 2500; //tiempo para amarillo
int tiempoParpadeo = 250;
int parpadeosRestantes = 10;
bool blink = true;

//se crea directamente el alias para la estructura
typedef struct{
	enum colores color;
}Esfera;

//defino 3 esferas
Esfera esfera[3];


void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);//aqui es como se va a ver, la pila de proyeccion
    glLoadIdentity();
    glOrtho(0,640,0,480,200,-200);
    glMatrixMode(GL_MODELVIEW); //esta es la de las transformaciones, la pila de transformaciones
    glLoadIdentity();
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    /*NOTA: Cuando nosotros estamos trasladando al cubo el punto que especificamos en glTranslated, 
	se toma como el punto central del cubo, en otras palabras, el cubo se dibuja tomando
	su centro como referencia lo que nos permite que desde el programa ya esté centrada la primitiva*/
    glPushMatrix();
    	glTranslated(320,240,0); //rectángulo
    	glScalef(1,3,1);
    	glColor3ub(175,175,175);
    	glutSolidCube(140);
    glPopMatrix();
    
	for (int i=0 ; i<3; i++){
		glColor3ubv(paleta[esfera[i].color]);
		glPushMatrix();
			glTranslated(320,370-130*i,0);
			glutSolidSphere(53,50,50);
		glPopMatrix();
	}
	//glutPostRedisplay();
  	glutSwapBuffers();
}


void cambiarEstado(){
	if(esfera[2].color == verde && blink){
		parpadeo();
	}
	if(esfera[0].color == rojo){
		esfera[0].color = gris;
		esfera[1].color = gris;
		esfera[2].color = verde;
		glutPostRedisplay();
		glutTimerFunc(tiempoRV,cambiarEstado,0);
	}else if(esfera [2].color == verde){
		esfera[0].color = gris;
		esfera[1].color = amarillo;
		esfera[2].color = gris;
		blink = !blink;
		glutPostRedisplay();
		glutTimerFunc(tiempoA, cambiarEstado,0);	
	}else if(esfera[1].color == amarillo){
		esfera[0].color = rojo;
		esfera[1].color = gris;
		esfera[2].color = gris;
		glutPostRedisplay();
		glutTimerFunc(tiempoRV, cambiarEstado,0);
	}	
}

void parpadeo(){ 
	if(esfera[2].color == verde)
		esfera[2].color = gris;
	else	
		esfera[2].color = verde;
	parpadeosRestantes--;
	if (parpadeosRestantes>0)	
		glutTimerFunc(tiempoParpadeo,parpadeo,1);
	else{
		parpadeosRestantes = 8;
		blink = false;
		glutTimerFunc(0,cambiarEstado,0);
	}
	glutPostRedisplay();			
}

void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}
int main(int argc, char** argv) {
	esfera[0].color = rojo;
	esfera[1].color = gris;
	esfera[2].color = gris;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Semaforo");
    glutReshapeFunc(ajusta);
    glutTimerFunc(tiempoRV,cambiarEstado,0);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}
