//la luz direccional posicion, ambt, esp, dif. NO SE ATENÚA
//la luz posicionales sí se atenúan

//POSICIONAL tiene 7
#include <gl/glut.h>
#include <stdbool.h>

GLfloat  girax = 0, giray= 0, zoom=0;
GLboolean malla = GL_FALSE, 
ejes = GL_TRUE, clic=GL_FALSE;
int gx, gy;

int tiempoRV = 4000;//tiempo para rojo y verde
int tiempoA= 2500; //tiempo para amarillo
int tiempoParpadeo = 250;
int parpadeosRestantes = 10;
bool blink = true;

enum colores {rojo, amarillo, verde,parpadeo};
enum colores estadoActual = rojo;

GLfloat rojoAmb[] = {0.0, 0.0, 0.0};
GLfloat rojoDif[] = {0.5, 0.0, 0.0};
GLfloat rojoEsp[] = {0.7, 0.6, 0.6};

GLfloat amaAmb[] = {0.329412, 0.223529, 0.027451,1};
GLfloat amaDif[] = {0.780392, 0.568627, 0.113725,1};
GLfloat amaEsp[] = {0.992157, 0.941176, 0.807843,1};

GLfloat verdeAmb[] = {0.0215, 0.1745, 0.0215,1};
GLfloat verdeDif[] = {0.07568, 0.61424, 0.07568,1};
GLfloat verdeEsp[] = {0.633, 0.727811, 0.633,1};

GLfloat grisAmb[] = {0.19225, 0.19225, 0.19225,1};
GLfloat grisDif[] = {0.50754, 0.50754, 0.50754,1};
GLfloat grisEsp[] = {0.508273, 0.508273, 0.508273,1};

GLfloat emiRoja[] = {1.0,0.0,0.0,1}; //encendido
GLfloat emiVerde[] = {0.0,1.0,0.0,1}; //encendido
GLfloat emiAma[] = {1.0,1.0,0.0,1}; //encendido
GLfloat noemi[] = {0,0,0,1}; //apagado

//Prototipos
void cambiarEstado();
void parpadear();

void ajusta(int ancho, int alto) {
	glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15,15,-15,15,-30,30);
    zoom=0;
    glEnable(GL_DEPTH_TEST); //habilito el z buffer
}

/*glMaterialfv(cara, reflex, *ptr)
cara -> GL_[FRONT|BACK|FRONT_AND_BACK]
reflex -> GL_[AMBIENT|DIFFUSE|SPECULAR|
			EMISION|SHININESS|
			AMBIENT_AND_DIFFUSE]
*ptr -> ptr a vector RGBA*/

/*En vez de pasar valor por valor, cree arrays
que contuvieran los valores que necesito y los
pasar directamente con un apuntador a ese array
*/
void renderEsfera(GLfloat x, GLfloat y,GLfloat z,
GLfloat* ambiente,GLfloat* difusa,GLfloat* especular,
GLfloat* emission, GLfloat shine){
 	glPushMatrix();
 		glScalef(1.3,1.3,1.3);
 		glTranslatef(x, y, z);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
    	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
		glutSolidSphere(1.5,20,20);
 	glPopMatrix();
 }
 
void renderRectangulo(
GLfloat* ambiente,GLfloat* difusa,GLfloat* especular,
GLfloat* emission,GLfloat shine){
 	glPushMatrix();
 		glScalef(1.5,3,1);
 		glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
    	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);	
	 	glutSolidCube(5);
 	glPopMatrix();
}

 	/*glLightfv(GL_LIGHTn, GL_[AMBIENT|DIFUSSE|SPECULAR],ptr]
	ptr -> ptr a un vector de RGBA
	Define el color ambiental, difuso y especular
 	de la luz.*/
 	
	/*glLightfv(GL_LIGHTn, GL_POSITION, val_ptr);
	 val_ptr -> ptr a un vector flotante(x,y,z,w)
	 si w=0 -> luz direccional
	 si w=1 -> luz posicional 
	 (x,y,z) determina la posición de luz
	Define si la luz es posicional con ubi concreta
	(puntual:emite luz al rededor en todas direccioneso 
	focal:emite luz en una dir concreta en forma de cono)
	o direccional conjunto de haces de luz paralelos
	*/

void myInit(void){
 	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat position[] = {0.0, 3.0, 3.0, 0.0};
 	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glFrontFace(GL_CCW);
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
}

//   Rotacion XY y Zoom
void mover (void) {
    glTranslated( 0, 0, zoom);
    glRotated( girax, 1.0, 0.0, 0.0);
    glRotated( giray, 0.0, 1.0, 0.0);
}
void raton(int boton, int estado, int xv, int yv) {
    clic= boton==GLUT_LEFT_BUTTON && estado==GLUT_DOWN;
    if(clic){
        gx = xv;
        gy = yv;
    }
    if (boton==3 || boton==4) // scroll up => 3 scroll down=>4
        zoom+=(boton==3)?0.1:-0.1;
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

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		mover();
		//rectángulo
		renderRectangulo(grisAmb,grisDif,grisEsp,noemi,0.088);
	    //Las esferas van a dibujarse según edo actual
	    switch(estadoActual) {
        case rojo:
            renderEsfera(0.18,4,2,rojoAmb,rojoDif,
			rojoEsp,emiRoja,0.25);
            renderEsfera(0.18,0,2,amaAmb,amaDif, 
			amaEsp, noemi,0.21794872);
            renderEsfera(0.18,-4,2,verdeAmb,verdeDif,
			verdeEsp, noemi,.6);
            break;
        case amarillo:
        	renderEsfera(0.18,4,2, rojoAmb, rojoDif,rojoEsp,noemi,0.25);
            renderEsfera(0.18,0,2,amaAmb, amaDif, amaEsp, emiAma,0.21794872);
            renderEsfera(0.18,-4,2,verdeAmb, verdeDif, verdeEsp, noemi,.6);
            break;
        case verde:
            renderEsfera(0.18,4,2, rojoAmb, rojoDif,rojoEsp,noemi,0.25);
            renderEsfera(0.18,0,2,amaAmb, amaDif, amaEsp, noemi,0.21794872);
            renderEsfera(0.18,-4,2,verdeAmb, verdeDif, verdeEsp, emiVerde,.6);
        case parpadeo:
        	renderEsfera(0.18,4,2, rojoAmb, rojoDif,rojoEsp,noemi,0.25);
            renderEsfera(0.18,0,2,amaAmb, amaDif, amaEsp, noemi,0.21794872);
            renderEsfera(0.18,-4,2,verdeAmb, verdeDif, verdeEsp, noemi,.6);
            break;
        default:
            break;
    }
    glPopMatrix();
    glutSwapBuffers();
}

void cambiarEstado() {
    if (estadoActual == verde && blink) {
        parpadear();
    } else if (estadoActual == rojo) {
        estadoActual = verde;
        glutPostRedisplay();
        glutTimerFunc(tiempoRV, cambiarEstado, 0);
    } else if (estadoActual == verde) {
        estadoActual = amarillo;
        glutPostRedisplay();
        blink = !blink;
        glutTimerFunc(tiempoA, cambiarEstado, 0);
    } else if (estadoActual == amarillo) {
        estadoActual = rojo;
        glutPostRedisplay();
        glutTimerFunc(tiempoRV, cambiarEstado, 0);
    }
}

void parpadear() {
	if(estadoActual == verde)
		estadoActual = parpadeo;
	else	
		estadoActual = verde;
	parpadeosRestantes--;
	if (parpadeosRestantes>0)	
		glutTimerFunc(tiempoParpadeo,parpadear,1);
	else{
		parpadeosRestantes = 8;
		blink = false;
		glutTimerFunc(0,cambiarEstado,0);
	}
	glutPostRedisplay();
}

// Funciones con Teclas
void teclado(unsigned char key, int x, int y) {
  switch(key) {
    case 27:  exit (0);
    case '+': zoom ++; break;
    case '-': zoom --; break;
    case 'p': glMatrixMode(GL_PROJECTION);
              glLoadIdentity();
              gluPerspective(45,1,10,100);
              zoom= -40;
			  break;
    case 'o': glMatrixMode(GL_PROJECTION);
              glLoadIdentity();
              glOrtho(-15,15,-15,15,-30,30);
              zoom=0;
    default: break;
  }
  glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Semaforo Materiales");
    myInit();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutMouseFunc(raton);
    glutMotionFunc(girar);
    glutKeyboardFunc(teclado);
    glutTimerFunc(tiempoRV,cambiarEstado,0);
    glutMainLoop();
    return 0;
}