#include <stdio.h> //aquí están funciones como fopen
#include <stdlib.h>
#include "random2.h"
#include <GL/glut.h>

/*DUDA POR QUE CON CADA CLIC CAMBIA DE COLOR*/

//Guardo el contenido de dibujo en el arreglo dibujo
char dibujo[1117]; //obtuve el tamaño con mi programa anterior viendo el número de special char
void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void dibujaAsciiArt(void *tipo, char *s ) {
	int color[3];
	//posición inicial del dibujo, que vaya imprimiendo de arriba hacia abajo
	int x=130, y=390;
    for (int i = 0; i < strlen(s); i++){
    	if(s[i] == '\n'){ //si hay un salto de línea
    		x=150;
    		y-=10; //nos ayudará a bajar las líneas y que no se encime
    		continue; //si es salto de línea no me interesa ponerle color entonces me voy a la siguiente iteración
		}
    	//Genero los colores aleatorios
    	for(int j=0; j<3 ; j++)
			color[j]= rnd0F(255);
		glColor3ub(color[0],color[1],color[2]);
		
		glRasterPos2i(x,y); //define la posición
        glutBitmapCharacter(tipo, s[i]);
        x+=6; //sin esto te imprime todo en una línea vertical
	}
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    dibujaAsciiArt(GLUT_BITMAP_HELVETICA_10, dibujo);
    glFlush();
}

void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}
int main(int argc, char** argv) {
    FILE *dibujo_ascii;
	char elemento;
	//abrimos nuestro dibujo en modo lectura
	dibujo_ascii = fopen("dibujo1.txt","r");
	
	if (dibujo_ascii == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
    int incremento=0;
	//mientras que no sea el final del archivo vamos a: 
	//obtener caracteres por caracter de nuestro file
	while(( elemento = fgetc(dibujo_ascii)) != EOF){
		printf("%c",elemento);
		dibujo[incremento++]=elemento; //guardo cada caracter en dibujo	
	}

	fclose(dibujo_ascii);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ascii Art");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(salir);
    glutMainLoop();
	return 0;
}