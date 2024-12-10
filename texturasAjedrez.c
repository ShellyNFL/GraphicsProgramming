//Ariadne Zinser Trigos y Shelly Flores Lopez - 00282331 y 00372578 -  Tablero Ajedrez(Texturas): 
//Base de codigo: tomada de "ejTextura.c" y del codigo 19 "TexProcedural.c" de la Dra. Carmen Villar.

#include <GL/glut.h>

int c1[] = {160,194,151};
int c2[] = {57,112,60};
//el unico requisito para texturas procedurales es que sean potencias de 2
//8 de alto (row), 8 de ancho (col), 3 componentes RGB 
GLubyte texTablero[8][8][3];

//funcion que rellena matrix de cada color: 
void rellenaMatriz(){
GLboolean cambiaColor;
	for(int i=0; i<8; i++){//para 8 renglones
	//intercalado de renglones (para que se vea como ajedrez
		if (i%2 == 0)
			cambiaColor = GL_FALSE; //si es par, empieza con bandera apagada
		else
			cambiaColor = GL_TRUE; //si es impar, bandera prendida
		for(int j=0;j<8;j++){ //para 8 columnas
			for(int k=0;k<3;k++){ //para R,G,B
				if(cambiaColor){ //intercalado entre colores para las celdas
					texTablero[i][j][k]=c1[k];//pone en la matriz los componentes RGB para verde claro
				}else{
					texTablero[i][j][k]=c2[k];//pone en la matriz los componentes RGB para verde oscuro
				}
			}
			cambiaColor = !cambiaColor; //cuando termina los componentes de una celda, invierte la bandera para cambiar de color
		}
	}
}

void creaTextura(void){
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST); //cuando lo tenga que magnificar usa nearest
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); //cuando lo tenga que minimizar usa linear
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, //textura en 2d, maximo nivel de detalle 0, gl_rgb, ancho 8, alto 8, 0 borde, 
												//formato rgb, tipo de dato matriz, nombre matriz que es apuntador
	0, GL_RGB, GL_UNSIGNED_BYTE, texTablero); //puntero_text es texTablero, el nombre de la matriz que contiene la textura
}

void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT);
	//ARRIBA A LA IZQUIERDA: sin repetir (original)
	//todo con factor de repeticion 1
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); 
		glVertex2f(-4.0, 1.0);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-4.0, 4.0);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(-1.0, 4.0);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(-1.0, 1.0); 
	glEnd();
	//ABAJO IZQ: repetida 4 veces (2 en s y 2 en t)
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); 
		glVertex2f(1.0, 1.0);
		glTexCoord2f(0.0, 2.0); //factor 2 en t
		glVertex2f(1.0, 4.0);
		glTexCoord2f(2.0, 2.0); //factores 2 en s y 2 en t
		glVertex2f(4.0, 4.0);
		glTexCoord2f(2.0, 0.0); //factor 2 en s
		glVertex2f(4.0, 1.0);
	glEnd();
	//con estos parametros, indico que la repeticion sera recorrer/embarrar el ultimo pixel
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);//en s
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);//en t
	//ABAJO: Rectangulo que se repite 6 veces en los bordes (3 en s y 2 en t)
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); 
		glVertex2f(-4.0, -4.0);
		glTexCoord2f(0.0, 2.0); // factor 2 en t
		glVertex2f(-4.0, -1.0);
		glTexCoord2f(3.0, 2.0); //lo repito 3 veces en la direccion s y 2 en la direccion t para que sean 6
		glVertex2f(4.0, -1.0);
		glTexCoord2f(3.0, 0.0);//factor 3 en s
		glVertex2f(4.0, -4.0);
	glEnd();
	glFlush();
}
void ajusta(int w, int h){
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5,5,-5,5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D); //habilito el pegado de texturas bidimensional
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Texturas Tablero");
	rellenaMatriz(); //rellena la matriz automaticamente
	creaTextura(); //invoco crea textura
	glutReshapeFunc(ajusta);
	glutDisplayFunc(dibuja);
	glutMainLoop();
	return 0;
}
