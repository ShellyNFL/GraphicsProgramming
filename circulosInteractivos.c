#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

bool clic = true;
bool dibujando = false;
int tempx,tempy;
int radio_temporal;

float red[] = {1.0, 0.0, 0.0};  
float blue[] = {0.0, 0.0, 1.0};
float green[] = {0.0, 1.0, 0.0};
float purple[] = {0.52, 0.0, 0.92};
int color = 0;

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

struct circulo{
	int xc;
	int yc;
	int r;
	float color[3];
	struct circulo *sig;
};

typedef struct circulo Circulo;

//puntero global inicial 
Circulo *inicio = NULL;

Circulo *creaNodo(int xcentro, int ycentro, int radio, float color[3]){
	Circulo *c;
	c = (Circulo *)malloc(sizeof(Circulo));
	c->xc = xcentro;
	c->yc = ycentro;
	c->r = radio;
	for (int i = 0; i < 3; i++) {
        c->color[i] = color[i];
    }
	c->sig = NULL;
	return c;
}

void insertaNodo(int xcentro, int ycentro, int radio){
	Circulo *aux;
	aux=inicio;
	float *colorSeleccionado;
	
	switch (color) {
        case 0: colorSeleccionado=red; break;
        case 1: colorSeleccionado=blue; break;
        case 2: colorSeleccionado=green; break;
        case 3: colorSeleccionado=purple; break;
        default: colorSeleccionado=red; 
    }
	
	if(inicio == NULL)
		inicio = creaNodo(xcentro,ycentro,radio,colorSeleccionado);
	else{
		while(aux->sig!=NULL)
			aux = aux->sig;
		aux->sig = creaNodo(xcentro,ycentro,radio,colorSeleccionado);
		//printf("Nodo insertado \n");
	}
}

void liberarMemoria(){
    Circulo *aux = inicio;
    Circulo *temp;

    while (aux != NULL) {
        temp = aux->sig;
        free(aux);
        aux = temp;
    }
    inicio = NULL;
    printf("Memoria liberada");
}

void dibuja8(int x, int y, int xc, int yc){
	glBegin(GL_POINTS);
	//estos puntos originalmente se calculan respecto al origen 0,0
		glVertex2i(x+xc ,y+yc);
		glVertex2i(-x+xc,-y+yc);
		glVertex2i(-x+xc,y+yc);
		glVertex2i(x+xc,-y+yc); 
		glVertex2i(y+xc,x+yc);
		glVertex2i(-y+xc,-x+yc);
		glVertex2i(-y+xc,x+yc);
		glVertex2i(y+xc,-x+yc);
		
	glEnd();
}

void dibujaCirculo(int r, int xcentro, int ycentro){
	int x = 0;
	int y = r;
	int d = 3-(2*r);
	while(x<=y){
		dibuja8(x,y,xcentro,ycentro);
		if (d>0){
			d= d+4*(x-y)+10;
			y--;
		}else
			d= d + 4*x + 6;
		x++;
	}
	glutPostRedisplay();	
}

/*void obtenDatos(int boton, int estado, int x, int y){
	glColor3ub(0,0,0);
	//son estáticas para que mantengan el valor obtenido en el primer clic
	static int tempx,tempy;
	int tempr;
    if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN ){
		if(clic) {
			printf("Coordenadas centro con (%d,%d)\n",x,y);
			tempx = x;
			tempy=480 - y; ;
			clic=!clic;
		}else{
			printf("Coordenadas radio con (%d,%d)\n",x,y);
			//obtenemos el radio, sacando la distancia entre dos puntos con pitagoras
			//printf("tempx: %d, tempy: %d\n",tempx,tempy);
			//printf("x: %d,y: %d\n",x,y);
			tempr = sqrt(pow(x - tempx, 2) + pow((480 - y) - tempy, 2));
			//printf("Radio %d\n",tempr);
			insertaNodo(tempx,tempy,tempr);	
/*Cuando llamas a glutPostRedisplay()estás diciendo a GLUT que algo cambió en la escena
y que necesitas actualizar la ventana gráfica.Después de llamar a glutPostRedisplay(),
GLUT ejecutará la función registrada en glutDisplayFunc(), o sea dibuja().
			glutPostRedisplay(); //llama a dibuja
			clic = !clic;			
		}
					
	}
    glFlush();
	
}*/


void obtenDatos(int boton, int estado, int x, int y) {
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        tempx = x;
        tempy = 480 - y; 
        dibujando = true;
        radio_temporal = 0;//hace que cada que se dibuja un nuevo circulo empiece con radio 0
    } else if (boton == GLUT_LEFT_BUTTON && estado == GLUT_UP) {
        insertaNodo(tempx, tempy, radio_temporal);
        dibujando = false;
        glutPostRedisplay();
    }
    glFlush();
}

void actualizaRadio(int x, int y) {
    if (dibujando) {//sólo si está ya el clic del centro
    	//obtiene el radio con pitágoras
        radio_temporal = sqrt(pow(x-tempx,2)+pow((480 - y)-tempy,2));
        glutPostRedisplay();
    }
}

void cambiaColor(int key, int x, int y) {
    if(key == GLUT_KEY_UP) color = 0;//Rojo
    if(key == GLUT_KEY_LEFT) color = 1;//Azul
    if(key == GLUT_KEY_DOWN) color = 2; //Verde
    if(key == GLUT_KEY_RIGHT) color = 3;//Morado
    glutPostRedisplay();
}


void dibuja() {
	glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    Circulo *aux = inicio;
/*NOTA si lo pongo así mi while:  while(aux->sig !=NULL) no dibujaría el último círculo*/
    //El objetivo es dibujar todos los círculos almacenados para eso recorremos la lista
    while(aux!=NULL){
    	glColor3fv(aux->color);
    	dibujaCirculo(aux->r,aux->xc,aux->yc);
    	aux = aux->sig;
	}
	 //Esto es lo que me dibuja el circulo mientras no suelte el clic
    if (dibujando && radio_temporal > 0) {
    	switch (color) {
            case 0: glColor3fv(red); break;
            case 1: glColor3fv(blue); break;
            case 2: glColor3fv(green); break;
            case 3: glColor3fv(purple); break;
        }
        dibujaCirculo(radio_temporal, tempx, tempy);
    }  
    glFlush();

}
void salir(unsigned char key, int x, int y) {
   if (key == 27)
   liberarMemoria();
   exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Circulos interactivos");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
   	glutMouseFunc(obtenDatos);
   	//glutKeyboardFunc(cambiaColor);
   	glutSpecialFunc(cambiaColor);
   	glutMotionFunc(actualizaRadio);
    glutKeyboardFunc(salir);
    glutCloseFunc(liberarMemoria);
    glutMainLoop();
    return 0;
}