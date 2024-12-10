// Tarea 1 - Ejercicio 1: Reina 
//Ariadne Zinser y Shelly Flores
//Programa elaborado con los programas "tablero.c", de la Dra. Carmen Villar y "pgc_t1e1_reina.c" de Ariadne Zinser
#include <stdio.h>
#include <GL/glut.h>
#define RENGLONES 8
#define COLUMNAS 8
#define CXINICIO 120
#define CYINICIO 40
#define ESCAQUE 50


/*
TO DO:
 Actualmente, la reina aparece donde se especifican las coordenadas. 
 Debe aparecer en las coordenadas que clickee el mouse (glutMouseFunc(raton) -> tomar de listaDibuja
 ACTUALIZACION: Ya aparece en el tablero
 
*/
//PALETA DE COLORES PARA REDIBUJAR A LA REINA EN CADA CASO
GLubyte colorReina[4][3] = {{245,222,179}, //beige Claro reina 1
						 {220,220,220}, //gris claro para reina beige
						 {51,51,153}, //azul oscuro para reina 2
                         {204, 204, 255}, //azul claro para reina cafe
						 }; 
int posRx = 4; //posicion global de la reina en x, guarda un numero del 0 al 7
int posRy = 0; //posicion global de la reina en x, guarda un numero del 0 al 7
//se inicializa en 4,0 (posicion en que nace la reina negra)
int anteriorRx=4; //guarda la posicion anterior de la reina para dibujar el turno anterior
int anteriorRy=7; //guarda la posicion anterior de la reina para dibujar el turno anterior
//se inicializa en 4,0 (posicion en que nace la reina negra)
GLboolean cambioTurno = GL_FALSE; //maneja el cambio de turno como interruptor
//FUNCION OPENGL CLICK MOUSE:
void raton(int boton, int estado, int x, int y) {
    int alto_ventana = 480;
    printf("\nCoordenada x: %d", x);
	printf("\nCoordenada y: %d", y); //con este print me di cuenta que la coordenada y esta arriba a la izq, tengo que cambiarlo
	y = alto_ventana - y; //invierte la coordenada y del mouse para ser la coordenada y de la ventana de OpenGL
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
    	//Aqui revisa si cae dentro de las dimensiones del primer cuadro. 
    	/*
       if(x<=170 && x>=120 && y>=40 && y<=90){
       	posRx = 160;
       	posRy = 80;
	   }
	   */
	   cambioTurno = !cambioTurno; //con cada clik se cambia el turno
	   anteriorRx=posRx; //primero se guarda la posicion de la primera reina en pasar, para luego impimirla y mantenerla en su ultima pos.
	   anteriorRy=posRy;
	   posRx = (x-CXINICIO)/ESCAQUE; //ajuste que considera el offset del tablero, y divide entre el ancho de cada escaque
	   posRy = (y-CYINICIO)/ESCAQUE; //para obtener un numero del 0 al 7, en lugar de un rango de coordenadas. Como se guarda en int se trunca
	   printf("Dibuja en el escaque %d,%d", posRx, posRy); //print de control
    }
    glutPostRedisplay();  // hace que se redibuje la pantalla, va despues de la ultima interaccion
}

void dibujaTexto(void *tipo, char *s ) { //funcion tomada del programa "tablero.c" de la Dra. Carmen Villar
   for (int i = 0; i < strlen(s); i++) //imprime los turnos de las reinas 
       glutBitmapCharacter(tipo, s[i]);
}

//FUNCION OPENGL DIBUJA REINA
void dibujaReina(GLubyte r, GLubyte g, GLubyte b, int x, int y){
	glColor3ub(r,g,b);
	glPointSize(1);
	//BASE REINA
    glBegin(GL_POLYGON);
		glVertex2i(x+5, y+5);   
    	glVertex2i(x+45, y+5);
   		glVertex2i(x+35, y+10);
    	glVertex2i(x+15, y+10); 
	glEnd();
	//MEDIO REINA
	glBegin(GL_POLYGON);
		glVertex2i(x+35, y+10);
		glVertex2i(x+35, y+15);
		glVertex2i(x+15, y+15);
		glVertex2i(x+15, y+10);
	glEnd();
	//ALTO REINA
	glBegin(GL_POLYGON);
		glVertex2i(x+35, y+15);
		glVertex2i(x+40, y+20);
		glVertex2i(x+10, y+20);
		glVertex2i(x+15, y+15);
	glEnd();
	//BASE CORONA
	glBegin(GL_POLYGON);
		glVertex2i(x+40, y+20);
		glVertex2i(x+42, y+25);
		glVertex2i(x+7, y+25);
		glVertex2i(x+10, y+20);
	glEnd();
		//CORONA
	glBegin(GL_TRIANGLES);
		glVertex2i(x+42, y+25);
		glVertex2i(x+45, y+32);
		glVertex2i(x+35, y+25);
		//2D0
		glVertex2i(x+35, y+25);
		glVertex2i(x+35, y+37);
		glVertex2i(x+27, y+25);
		//3R0
		glVertex2i(x+27, y+25);
		glVertex2i(x+25, y+40);
		glVertex2i(x+22, y+25);
		//4to
		glVertex2i(x+22, y+25);
		glVertex2i(x+15, y+37);
		glVertex2i(x+15, y+25);
		//6to
		glVertex2i(x+15, y+25);
		glVertex2i(x+5, y+32);
		glVertex2i(x+7, y+25);
	glEnd();
	//PUNTOS DE LA CORONA
	glPointSize(4);
	glBegin(GL_POINTS);
		glVertex2i(x+45, y+32);
		glVertex2i(x+35, y+37);
		glVertex2i(x+25, y+40);
		glVertex2i(x+15, y+37);
		glVertex2i(x+5, y+32);
	glEnd();
	glutSwapBuffers();
}


//FUNCION LOGICA (no actualizada para estar sincronizada con la version grafica)
void rellenaTablero (char matriz[RENGLONES][COLUMNAS], int reinaX, int reinaY){
    for(int y1 = 0; y1<RENGLONES;y1++){
        int x1;
        for(int x1 = 0; x1<COLUMNAS;x1++){
            matriz[x1][y1]='-';
            matriz[x1][reinaY] = '*';
        }
        matriz[reinaX][y1] = '*';
    }
    //diagonal inferior izquierda
    int x1 = reinaX-1,y1 = reinaY-1;
    while ( y1 > -1 && x1 > -1){ 
        if(x1<8 && y1<8 && x1>-1 && y1>-1) {matriz [x1][y1]= '*';}
        x1--;
        y1--;
    }
    //diagonal inferior derecha
    x1 = reinaX+1,y1 = reinaY-1;
    while (x1 < 8 && y1 > -1){
        if(x1<8 && y1<8 && x1>-1 && y1>-1) {matriz [x1][y1]='*';}
        x1++;
        y1--;
    }
    //diagonal superior inzquierda
    x1 = reinaX-1,y1 = reinaY+1;
    while (x1 > -1 && y1 < 8){
        if(x1<8 && y1<8 && x1>-1 && y1>-1) {matriz [x1][y1]='*';}
        x1--;
        y1++;
    }
       //diagonal superior derecha
    x1 = reinaX+1,y1 = reinaY+1;
    while (x1 < 8 && y1 < 8){
        if(x1<8 && y1<8 && x1>-1 && y1>-1) {matriz [x1][y1]='*';}
        x1++;
        y1++;
    }
    matriz[reinaX][reinaY] = 'R';
}

//FUNCION LOGICA (no actualizada para estar sincronizada con la version grafica)
void imprimeTablero (char matriz[RENGLONES][COLUMNAS], int labelEjeX[], int labelEjeY[]){
    for (int y1 = RENGLONES-1; y1>-1; y1--){
        for(int x1 = 0; x1<COLUMNAS;x1++){
            if (x1 == 0){
             printf ("\n%d",labelEjeY[y1]);
            }
            printf("\t\t%c", matriz[x1][y1]);        
            
        }
        printf("\n");
    }
    printf("\n");
    for(int x1=0; x1<COLUMNAS; x1++){
        printf("\t\t%d", labelEjeX[x1]);
    }
}

//FUNCIONES OPENGL
void ajusta(int ancho, int alto) {
   glClearColor(0.53, 0.81, 0.92, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, 640, 0, 480);
}
//FUNCION GRAFICA
void dibuja(void) {
	//EMPIEZA A DIBUJAR TABLERO (Tomado de "tablero.c" (Dra. Carmen Villar)
	GLboolean colorBlanco = GL_TRUE;
	float blanco[]={1.,1.,1.};
	float negro[]={0.,0.,0.};
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = CXINICIO; i<(CXINICIO+8*ESCAQUE); i+=ESCAQUE){ //Desde el inicio 
		colorBlanco = !colorBlanco;
		for (int j = CYINICIO; j<(CYINICIO+8*ESCAQUE); j+=ESCAQUE){
			glColor3fv(colorBlanco?blanco:negro);
			glRecti(i,j,i+ESCAQUE,j+ESCAQUE);
			colorBlanco = !colorBlanco;
		}
	}
	//si las coordenadas de los cliks para ambas reinas son dentro de los margenes del tablero:
	if ( anteriorRx<8 && anteriorRx>-1 && anteriorRy<8 && anteriorRy>-1 && posRx<8 && posRx>-1 && posRy<8 && posRy>-1){
		if(cambioTurno){ //si es el turno de la reina negra:
			glColor3ub(51,51,153); //color negro para indicar que el siguiente mov afecta a la reina negra
			glRasterPos2i(120,20);
			dibujaTexto(GLUT_BITMAP_HELVETICA_18,"Fue turno de la reina blanca, sigue la negra:");
				//PINTA HORIZONTALES Y VERTICALES
				//revisa en un ciclo anidado donde fue el click, y pinta en x y en y varias reinas de un gris oscuro
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					//se llama a la funcion dibuja Reina que recibe como parametros los valores r,g,b de la paleta que corresponde
					//y manda la posicion en donde tiene que dibujar a las reinas de proyeccion del turno de la reina que se movio en el anterior
					dibujaReina(colorReina[3][0],colorReina[3][1],colorReina[3][2],CXINICIO+(i*ESCAQUE),CYINICIO+(anteriorRy*ESCAQUE));
				}
				dibujaReina(colorReina[3][0],colorReina[3][1],colorReina[3][2],CXINICIO+(anteriorRx*ESCAQUE),CYINICIO+(i*ESCAQUE));
			}
			//----------------------------------------------------------------
			//PINTA DIAGONALES (con la misma logica que las funciones de "pgc_t1e1_reina.c")
			//diagonal inferior izquierda (se pintan las proyecciones de la reina negra)
    		int i = anteriorRx-1,j = anteriorRy-1;
    		while ( i > -1 && j > -1){ 
        		if(j<8 && i<8 && j>-1 && i>-1) {
					dibujaReina(colorReina[3][0],colorReina[3][1],colorReina[3][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
				}
        		j--;
        		i--;
    		}
    
    		//diagonal inferior derecha
    		i = anteriorRx+1;
			j = anteriorRy-1;
    		while ( i < 8 && j > -1){ 
        		if(j<8 && i<8 && j>-1 && i>-1) {
					dibujaReina(colorReina[3][0],colorReina[3][1],colorReina[3][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
				}
       		 	j--;
        		i++;
    		}
    	
    		//diagonal inferior derecha
    		i = anteriorRx-1;
			j = anteriorRy+1;
    		while ( i >-1 && j < 8){ 
        		if(j<8 && i<8 && j>-1 && i>-1) {
					dibujaReina(colorReina[3][0],colorReina[3][1],colorReina[3][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
				}
        		j++;
        		i--;
    		}
    
    		//diagonal superior derecha
    		i = anteriorRx+1;
    		j = anteriorRy+1;
    		while ( i < 8 && j < 8){ 
        		if(j<8 && i<8 && j>-1 && i>-1) {
					dibujaReina(colorReina[3][0],colorReina[3][1],colorReina[3][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
				}
        		j++;
        		i++;
    		}
			//-----------------------------------------------------------
			//DIBUJA REINA:
			for (int i = 0; i<8; i++){
				for(int j=0; j<8;j++){
					if(posRx==i && posRy==j){
						dibujaReina(colorReina[0][0],colorReina[0][1],colorReina[0][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
					}		
				}
			}
				//DIBUJA A LA OTRA REINA (para que se mantenga en posicion de su turno anterior aunque se mueva la otra)
			dibujaReina(colorReina[2][0],colorReina[2][1],colorReina[2][2],CXINICIO+(anteriorRx*ESCAQUE),CYINICIO+(anteriorRy*ESCAQUE));
		}else{ //SE INVIERTE LA BANDERA Y AHORA ES TURNO DE LA OTRA (misma logica)
			glColor3ub(255,255,255);
			glRasterPos2i(120,450);
			dibujaTexto(GLUT_BITMAP_HELVETICA_18,"Fue turno de la reina negra, sigue la blanca:");
				//PINTA HORIZONTALES Y VERTICALES
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					dibujaReina(colorReina[1][0],colorReina[1][1],colorReina[1][2],CXINICIO+(i*ESCAQUE),CYINICIO+(anteriorRy*ESCAQUE));
				}
				dibujaReina(colorReina[1][0],colorReina[1][1],colorReina[1][2],CXINICIO+(anteriorRx*ESCAQUE),CYINICIO+(i*ESCAQUE));
			}
		//-----------------------------------------------
		//PINTA DIAGONALES
		//diagonal inferior izquierda
    		int i = anteriorRx-1,j = anteriorRy-1;
    		while ( i > -1 && j > -1){ 
        		if(j<8 && i<8 && j>-1 && i>-1) {
					dibujaReina(colorReina[1][0],colorReina[1][1],colorReina[1][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
				}
        		j--;
        		i--;
    		}
    
    		//diagonal inferior derecha
    		i = anteriorRx+1;
			j = anteriorRy-1;
    		while ( i < 8 && j > -1){ 
        		if(j<8 && i<8 && j>-1 && i>-1) {
					dibujaReina(colorReina[1][0],colorReina[1][1],colorReina[1][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
				}
        		j--;
        		i++;
    		}
    
    		//diagonal inferior derecha
    		i = anteriorRx-1;
			j = anteriorRy+1;
    		while ( i >-1 && j < 8){ 
        		if(j<8 && i<8 && j>-1 && i>-1) {
					dibujaReina(colorReina[1][0],colorReina[1][1],colorReina[1][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
				}
        		j++;
        		i--;
    		}
    
    		//diagonal superior derecha
    		i = anteriorRx+1;
    		j = anteriorRy+1;
    		while ( i < 8 && j < 8){ 
        		if(j<8 && i<8 && j>-1 && i>-1) {
					dibujaReina(colorReina[1][0],colorReina[1][1],colorReina[1][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
				}
        		j++;
        		i++;
    		}
		//-----------------------------------------------------
		//DIBUJA REINA:
			for (int i = 0; i<8; i++){
				for(int j=0; j<8;j++){
					if(posRx==i && posRy==j){
						dibujaReina(colorReina[2][0],colorReina[2][1],colorReina[2][2],CXINICIO+(i*ESCAQUE),CYINICIO+(j*ESCAQUE));
					}		
				}
	//dibuja a las reinas en las verticales y horizonales
			}
			//DIBUJA A LA OTRA REINA:
			dibujaReina(colorReina[0][0],colorReina[0][1],colorReina[0][2],CXINICIO+(anteriorRx*ESCAQUE),CYINICIO+(anteriorRy*ESCAQUE));
		
		}
	}else{ //Si el click cae fuera del tablero, no dibuja nada
		glColor3ub(51,51,153);
		glRasterPos2i(120,20);
		dibujaTexto(GLUT_BITMAP_HELVETICA_12,"Click fuera del tablero, hacer click dos veces en el tablero para continuar:"); //2 clicks porque necesita tener nuevas coordenadas para anteriorRxRy y posRxRy
	}
	
	//----------------------------------------------------------------

	//TO DO: pasar esto a ciclo. 
	/*
	if (posRx==0 && posRy==0){
		dibujaReina(120, 40);
	}else if(posRx==1 && posRy==0){
		dibujaReina(170, 40);
	}else if(posRx==2 && posRy==0){
		dibujaReina(220, 40);
	}
	*/
	glutSwapBuffers();
}


int main(int argc, char** argv) {
    int etiquetaEjeY[]={0,1,2,3,4,5,6,7};
    int etiquetaEjeX[]={0,1,2,3,4,5,6,7};
    int reinaX=-1,reinaY=-1;
    char tablero[RENGLONES][COLUMNAS];
    reinaX = posRx;
    reinaY = posRy;
    /*printf("Posición de reina:");
    printf("\n Coordenada x: %d", reinaX);
    printf("\n Coordenada y: %d", reinaY);
    printf("\n");*/
    rellenaTablero(tablero, reinaX, reinaY);
    imprimeTablero(tablero, etiquetaEjeX, etiquetaEjeY);
    //printf("\nreina en x: %d",reinaX);
    //printf("\nreina en y: %d",reinaY);
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Tablero Ajedrez");
	glutReshapeFunc(ajusta);
	glutDisplayFunc(dibuja);
	glutMouseFunc(raton);
	glutMainLoop();

    return 0;
}

