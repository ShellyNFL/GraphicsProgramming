
/*Para este programa se ocupó parte del código de 'camara.c'
para lograr el movimiento de nuestra figura mientras
se tiene presionado un boton del mouse. Así mismo se tomó parte del código
de 'proecciones.c' para dibujar los ejes, la malla y cambiar la
matriz de proyección*/

#include <gl/glut.h>
#include <stdbool.h>

GLfloat  girax = 0, giray= 0, zoom=0;
GLboolean malla = GL_FALSE, ejes = GL_TRUE, clic=GL_FALSE;
int gx, gy;

GLubyte paleta[4][3]={ {204, 219, 220},{255,0,0},{255,251,0},{0,255,0} };
enum colores{gris, rojo, amarillo, verde};

int tiempoRV = 4000;//tiempo para rojo y verde
int tiempoA= 2500; //tiempo para amarillo
int tiempoParpadeo = 250;
int parpadeosRestantes = 10;
bool blink = true;

//Prototipo
void parpadeo();


struct esfera{
	enum colores color;
}; 
typedef struct esfera Esfera;

//defino 3 esferas
Esfera esfera[3];
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

//  Malla y Ejes
void creaMalla(int long_eje) {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    int i;
      for(i= -long_eje; i<=long_eje; i++) {
          glVertex3f (i,0,-long_eje);
          glVertex3f (i,0,long_eje);
          glVertex3f (-long_eje,0,i);
          glVertex3f (long_eje,0,i);
      }
    glEnd();
}

void creaEjes(void) {
    glColor3f(0.0,0.0,0.0);
    glBegin( GL_LINES );
        glVertex3f (0.0,0.0,0.0); glVertex3f (11.0,0.0,0.0);
        glVertex3f (0.0,0.0,0.0); glVertex3f (0.0,11.0,0.0);
        glVertex3f (0.0,0.0,0.0); glVertex3f (0.0,0.0,11.0);
    glEnd();
    glBegin( GL_TRIANGLES );
        glVertex3f (11.0,0.0,0.0); /* eje x */
        glVertex3f (10.5,0.0,-.50);
        glVertex3f (10.5,0.0,.50);
        glColor3f(0.25,1,0.25);  	/* eje y */
        glVertex3f (0.0,11.0,0.0);
        glVertex3f (-.50,10.5,0.0);
        glVertex3f (.50,10.5,0.0);
        glColor3f(0.25,0.25,1.0);  	/* eje z */
        glVertex3f (0.0,0.0,11.0);
        glVertex3f (-.50,0.0,10.5);
        glVertex3f (.50,0.0,10.5);
    glEnd();
}
void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		mover();
		if (malla) creaMalla(10);
		if (ejes) creaEjes();
		glPushMatrix();
	    	//glTranslated(0,0,); 
	    	glScalef(1.5,3,1);
	    	glColor3ub(41, 110, 180);
	    	glutSolidCube(5);//rectángulo
	    glPopMatrix();
	    
		for (int i=0 ; i<3; i++){
			glColor3ubv(paleta[esfera[i].color]);
			glPushMatrix();
				glTranslated(.18,5-5*i,2.5);
				glScalef(1.3,1.3,1.3);
				glutSolidSphere(1.5,20,20);
			glPopMatrix();
		}
	glPopMatrix();
    glutSwapBuffers();
}
// Funciones con Teclas
void teclado(unsigned char key, int x, int y) {
  switch(key) {
    case 27:  exit (0);
    case '+': zoom ++; break;
    case '-': zoom --; break;
    case 'm': malla = !malla; break;
    case 'e': ejes = !ejes;  break;
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

void ajusta(int ancho, int alto) {
	glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*se agrego para que desde que inicie
    se pueda ver el semáforo*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15,15,-15,15,-30,30);
    zoom=0;
    //habilito el z buffer
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_LIGHT0); //se enciende
	glEnable(GL_LIGHTING); //se conecta
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
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

int main(int argc, char** argv) {
	esfera[0].color = rojo;
	esfera[1].color = gris;
	esfera[2].color = gris;
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInit(&argc, argv);
    glutCreateWindow("Semaforo");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutMouseFunc(raton);
    glutMotionFunc(girar);
    glutKeyboardFunc(teclado);
    glutTimerFunc(tiempoRV,cambiarEstado,0);
    glutMainLoop();
    return 0;
}