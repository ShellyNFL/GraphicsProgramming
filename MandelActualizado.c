#include <GL/glut.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_COLORES 15
#define AsignarColor(i) ( (i)%MAX_COLORES )

float x0,y0,x1,y1; 
int nIter;
bool usarDifcolor = false;

GLubyte difcolor[15][3] = {{255, 87, 51}, {51, 153, 255}, {255, 204, 0}, {34, 139, 34},
							{153, 102, 255},{255, 105, 180},{0, 191, 255}, {255, 165, 0}, 
							{46, 139, 87}, {75, 0, 130},{255, 99, 71}, {102, 205, 170}, 
							{255, 20, 147}, {100, 149, 237}, {240, 128, 128}};
							

//tonalidades de azul			
GLubyte samecolor[15][3] = {{0, 0, 139}, {0, 0, 128}, {0, 0, 255}, {25, 25, 112},
							{0, 0, 205}, {0, 0, 180}, {0, 0, 170}, {0, 34, 102},
							{0, 51, 153}, {0, 65, 160}, {0, 70, 175}, {0, 76, 204},
							{0, 90, 230}, {10, 100, 255}, {15, 110, 255}
							};

							

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

float CalcularFactoresEscala(float x0,float y0,float x1,float y1,int *x,int *y){
 	float s,sx,sy;
	sx=(x1-x0) / *x; //valor de x que tomará cada pixel en el plano complejo
	sy=(y1-y0) / *y; //valor de y que tomará cada pixel en el plano complejo
 	if (sx>sy){
 		s=sx;
    	*y=(int)( (y1-y0)/s );	
	 } else{
	 	s=sy;
    	*x=(int)( (x1-x0)/s );	
	 }
 	return s;
}

int Mandel(int iter,float x0,float y0,float x1,float y1){
 	int xMax=640,yMax=480;       // valores máximos de la pantalla
 	float x,y;       	// (x,y) -> punto del plano complejo que se va obteniendo
 	float x2,y2;     	// punto del plano candidato a ser del conjunto de Mandelbrot (C)
 	float xx,yy;     	// complejo auxiliar
 	int px; register int py; // punto de pantalla que se corresponde al (x,y)
 	float s;         	// factor de escala para convertir de (px,py) a (x,y)
 	register int iaux; 	// entero auxiliar

 	s=CalcularFactoresEscala(x0,y0,x1,y1,&xMax,&yMax);
 	glBegin(GL_POINTS);
 	glPointSize(1);
 	glColor3ub(0,0,0);
 	for (px=0;px<xMax;px++){   			// para cada columna de pantalla
 		for(py=0;py<yMax;py++){			// para cada fila de pantalla
      // Conversion del pixel (px,py) al punto complejo (x2,y2) (C)
	      	x2=x0+px*s;
	      	y2=y0+py*s;
	      	xx=yy=0.; // estudiamos la órbita de cero
	      	for(iaux=0; iaux<iter; iaux++){// comprobar si tiende a infinito 
				// Iterar: (x,y)=(xx,yy)ý+(x2,y2)
				x=xx*xx-yy*yy+x2;
				y=2*xx*yy+y2;
				// hacer que (x,y) sea el próximo punto iterado
				xx=x;
				yy=y;
				if (x*x+y*y>10000){ 	// si el módulo es mayor que 100,tiende a infinito
				// Si diverge, colorear con la paleta difcolor
					if(usarDifcolor)
						glColor3ubv(difcolor[AsignarColor(iaux)]);
					else
						glColor3ubv(samecolor[AsignarColor(iaux)]);
					glVertex2i(px,yMax-1-py);
				    //putpixel(px,yMax-1-py,AsignarColor(iaux));
				    break; // fin del bucle iaux, no hace falta seguir
				} else{
					glColor3ub(0,0,0);
					glVertex2i(px,yMax-1-py);
				}
       		}
    	}	
  	}
  	glEnd();
   return 0;
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    Mandel(nIter,x0,y0,x1,y1);
    glutSwapBuffers();
}

void teclasEspeciales(int key){
	switch(key){
		case GLUT_KEY_UP: nIter+=5; break;
		case GLUT_KEY_DOWN: nIter-=5; break;	
	}
	glutPostRedisplay();
}

void teclasAscii(unsigned char key, int x, int y) {

	switch(key){
		case 27: exit(0); break;
		case 's': usarDifcolor = !usarDifcolor; break;
		case '+': //para zoom in  
			if(x0<-0.01 && y0< -0.01){
			x0+=0.15; y0+=0.12; 
			x1-=0.10; y1-=0.10;	
		}else{
			x0 =-2;
			y0= -1.5;
			x1=2;
			y1=1.5;
		}break;
		case '-': //para zoom out
			if(x0<=-2.25 || y0<=-1.8){
				x0 =-2;
				y0= -1.5;
				x1=2;
				y1=1.5;
			}else{
				x0-=0.15; y0-=0.12;
				x1+=0.15; y1+=0.12;	
			}break;
 		case 'l':x0 += 0.1;  x1 += 0.1; break;
        case 'r': x0 -= 0.1; x1 -= 0.1; break;
        case 'u': y0 += 0.1; y1 += 0.1; break;
        case 'd': y0 -= 0.1; y1 -= 0.1; break;
		default: break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	printf("\n Conjunto de Mandelbrot \n");
   	printf("\n  Introduzca el numero de iteraciones: ");
   	scanf("%d",&nIter);
   	printf("\n  Introduzca la region del plano complejo:\n");
   	printf("     esquina inferior izquierda  x0 (-2.25): ");
	scanf("%f",&x0);
	printf("     esquina inferior izquierda  y0 (-1.8): ");
	scanf("%f",&y0);
	printf("     esquina superior derecha    x1 (+0.75): ");
	scanf("%f",&x1);
	printf("     esquina superior derecha    y1 (+1.5): ");
	scanf("%f",&y1);
	
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("MandelBrot");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(teclasAscii); 
	glutSpecialFunc(teclasEspeciales);  
    glutMainLoop();
    return 0;
}