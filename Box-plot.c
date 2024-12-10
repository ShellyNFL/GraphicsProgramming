/*---------------------------------------- INTRUCCIONES -----------------------------------
 Genera 50 números aleatorios con probabilidades: 0.1->[20,150], 0.8->(150, 300) y 0.1->[300, 460].
Dibuja el boxplot correspondiente, muestra: escala numérica, puntos generados, su cantidad, media
y outliers (averigua cómo se obtienen). Al presionar una tecla se generan 25 números aleatorios
más, se ajusta el boxplot y se dibujan los puntos en otra posición. Este proceso se repite hasta llegar
a 500 puntos. Proporciona la opción de correr el proceso automáticamente con una tecla.
 --------------------------------------------------------------------------------------*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "random.h"
#define CELDAS 15
#define MAX_NUMEROS 15
#define N 500 


int muestra[N];
int incrementox = 180; //incremento de la línea de puntos
int incrementoy = 20; //Da incremento para la escala numérica inicial en y
int puntos = 50; //Es el numero de puntos que se está calculando
char cadenaPts[4]; //cadena que guarda los puntos que se imprimen arriba de la pantalla
bool incrementosolo = false; //me sirve cuando hago los cálculos automáticos
int cuartil[3];


void generaRandomNum(int num){
	for(int i=0 ;i<num; i++){
		float proba= rnd01();
		if (proba <= 0.1)
			muestra[i]=rndIF(20,150);
		else if (proba <= 0.9 )
			muestra[i]=rndIF(151,300);
		else
			muestra[i]=rndIF(301,460);
	}	
}


float sacaCuartiles(int p, int numDatos){
    float i = (float)(p*numDatos)/100.0;
    if((p*numDatos)%100==0){
        return i-1;
    }else{
    return i;
    }
}

//ordenamiento con quick sort código obtenido de: Tarea1 repaso de C
void ordenaArreglo(int arreglo[], int bajo, int alto){
    if(bajo<alto){
        int indicePivote = parteArreglo(arreglo, bajo, alto);
        ordenaArreglo(arreglo, bajo, indicePivote-1);
        ordenaArreglo(arreglo, indicePivote+1, alto);
    }
}

int parteArreglo(int arreglo[], int bajo, int alto){
    int pivote = arreglo[alto]; //selecciona como pivote el número en la última celda del arreglo
    int i = bajo - 1; // -1 como índice bajo, para empezar
    for(int j=bajo; j<alto; j++){ //recorre el arreglo
        if(arreglo[j] <= pivote){ //si lo que hay en el índice j es menor o igual al pivote: 
            i++; //aumento el índice de i
            //va a hacer el swap
            int temporal = arreglo[i];
            arreglo[i]=arreglo[j];
            arreglo[j]=temporal; //ahora cambié de lugar esos dos números y aumenté índice de j. 
        }
    }
    int temporal = arreglo[i+1];
    arreglo[i+1]=arreglo[alto];
    arreglo[alto]=temporal;
    return i+1;
}

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}


//Esta función escribe la escala numérica
void escalaNumerica(){
	char cadena[4];
	for (int i=20 ; i<=640; i+=20){
		//sintaxis consultada de chatgpt, referencia 4
		snprintf(cadena, sizeof(cadena), "%d", i); //convierte de entero a cadena de caracteres
		dibujaEscala(GLUT_BITMAP_TIMES_ROMAN_10,cadena);	
	}
}

void dibujaEscala(void *tipo, char *s ) {
	glColor3ub(0,0,0);
	glRasterPos2i(10, incrementoy);
    for (int i = 0; i < strlen(s); i++){
    	glutBitmapCharacter(tipo, s[i]);
	}
	incrementoy+=20;
}

void escribe(void *tipo, char *s ) {
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

void dibuja(void) {
	glColor3ub(0,0,0);
	glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    escalaNumerica();
    /*sin esta renicializacion desaparece la escala con cualquier acción del código
    porque cuando se hace alguna acción se vuelve a llamar a dibuja que vuelva a y 
    llamar a escalaNumerica pero ahora ya empezará en 480*/
    incrementoy = 20; 
    glRasterPos2i(300,470);
    escribe(GLUT_BITMAP_TIMES_ROMAN_10,"PUNTOS: ");
    snprintf(cadenaPts, sizeof(cadenaPts), "%d", puntos);
    escribe(GLUT_BITMAP_TIMES_ROMAN_10,cadenaPts);
    

    //Dibuja cuartil 1 y 3
   	int q1 =muestra[(int)sacaCuartiles(25,puntos)];
	int q3 =muestra[(int)sacaCuartiles(75,puntos)];
    glColor3ub(161, 205, 244);
    glBegin(GL_POLYGON);
	    glVertex2f(60, q1);
	    glVertex2f(120, q1);
	    glVertex2f(120, q3);
	    glVertex2f(60, q3);
	glEnd();
	
	//Dibuja media 
	int q2 =muestra[(int)sacaCuartiles(50,puntos)];
	glColor3ub(255,0,0);
	glBegin(GL_LINE_LOOP);
	    glVertex2f(60, q2);
	    glVertex2f(120, q2);
	glEnd();
	glPointSize(4);
	glBegin(GL_POINTS);
    	glVertex2f(90, q2);
    glEnd();
    
     //Outilers
    int ric = q3 - q1; //saco el rango intercuartílico RIC
	int limiteInferior = q1-1.5*ric;
	int limiteSuperior = q3+1.5*ric;
	
	glColor3ub(255, 0, 0);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (int i=0; i<puntos; i++) {
	    if (muestra[i]<limiteInferior || muestra[i]>limiteSuperior) {
	        glVertex2i(90,muestra[i]);
	    }
	}
	glEnd();
	
	//Bigotes
    int whiskerInferior=muestra[0];
	int whiskerSuperior=muestra[puntos-1];

	for (int i=0; i<puntos;i++) {
	    if (muestra[i]>=limiteInferior) {
	        whiskerInferior=muestra[i];
	        break;
	    }
	}

	for (int i=puntos-1;i>=0;i--) {
	    if (muestra[i]<=limiteSuperior) {
	        whiskerSuperior=muestra[i];
	        break;
	    }
	}

	glColor3ub(148, 0, 211);
	glBegin(GL_LINES);
	    glVertex2i(60, whiskerInferior);
	    glVertex2i(120, whiskerInferior);
	    glVertex2i(60, whiskerSuperior);
	    glVertex2i(120, whiskerSuperior);
	glEnd();

	// Dibuja whisker inferior con q1
	glBegin(GL_LINES);
	    glVertex2i(90,whiskerInferior);
	    glVertex2i(90,q1);
	glEnd();
	
	// Dibuja whisker superior con q3
	glBegin(GL_LINES);
	    glVertex2i(90,whiskerSuperior);
	    glVertex2i(90,q3);
	glEnd();
    
    //Dibuja los puntos
    glColor3ub(0,0,0);
    glPointSize(2);
	for(int i=0;i<puntos;i++){
    	glBegin(GL_POINTS);
    		glVertex2i(incrementox ,muestra[i]);
    	glEnd();
    }  
    glutSwapBuffers();
}


void generaPuntos(unsigned char key, int x, int y){
	if(key == GLUT_KEY_RIGHT && puntos<500){
		generaRandomNum(puntos+25);
		puntos+=25;
		//y se empieza a ordenar
		ordenaArreglo(muestra,0,puntos-1); 
		 
		//recalculo cuartiles
		int q1=muestra[(int)sacaCuartiles(25,puntos)];
        int q2=muestra[(int)sacaCuartiles(50,puntos)];
        int q3=muestra[(int)sacaCuartiles(75,puntos)];
        
        //recalculo los límites de los bigotes y outilers
        int ric =q3-q1;
        int limiteInferior = q1-1.5*ric;
        int limiteSuperior = q3+1.5*ric;
        
        incrementox+= 22;        
    	glutPostRedisplay();
	}
}

/*no se puede hacer con ciclos for porque va muy rápido para ver los cambios*/
void teclasAscii(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
   if(key == 'a' && puntos<=500){
   		incrementosolo = true;
   		incrementox += 15;
   		autoIncremento();
	}else{
		incrementox = 180;
	}
}

void autoIncremento(){
	if(incrementosolo == true && puntos<500){
		generaRandomNum(puntos+25);
		puntos+=25;
	
		//se repite lo mismo que generaPuntos
		ordenaArreglo(muestra,0,puntos-1); 
		
		int q1=muestra[(int)sacaCuartiles(25,puntos)];
        int q2=muestra[(int)sacaCuartiles(50,puntos)];
        int q3=muestra[(int)sacaCuartiles(75,puntos)];
        
        int ric =q3-q1;
        int limiteInferior = q1-1.5*ric;
        int limiteSuperior = q3+1.5*ric;
        
        incrementox+= 22;        
    	glutPostRedisplay();

		glutTimerFunc(1000, autoIncremento,1);
	}else{
		incrementosolo = false;
		incrementox = 180;
	}	
}

int main(int argc, char** argv) {
	generaRandomNum(50); //comienza generando 50 num aleatorios y los guarda en muestra
    ordenaArreglo(muestra, 0, puntos - 1);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Boxplot");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutSpecialFunc(generaPuntos);
    glutKeyboardFunc(teclasAscii);
    glutMainLoop();
    return 0;
}