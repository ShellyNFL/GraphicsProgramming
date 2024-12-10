#include <stdbool.h>
#include <GL/glut.h>

//recorro los vertices de la figura y checo si hay vuelta a la derecha
int pos_x[60], pos_y[60];
int puntos = 0;
int coordsPuntoMouse[2];
GLboolean fin=GL_FALSE;

void ajusta(int ancho, int alto){
   glClearColor(1.0,1.0,1.0,0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void raton(int boton, int estado, int x, int y){
   int alto_ventana=480;
   if (!fin){
       if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
           pos_x[puntos] = x;
           pos_y[puntos] = alto_ventana - y;
           puntos++;
       }
       glutPostRedisplay();
   }else{ //si ya termino de dibujar el poligono convexo (si se prende la bandera de fin)
		if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
   			coordsPuntoMouse[0]=x;
   			coordsPuntoMouse[1]= alto_ventana - y;
   		}
   }
   glutPostRedisplay();
}

void termina(int tecla, int x, int y){
   switch(tecla) {
     case GLUT_KEY_UP: fin=GL_TRUE; 
                        break;
     case GLUT_KEY_DOWN: puntos=0; fin=GL_FALSE;
     					break;
   }glutPostRedisplay(); 
}
void teclado(unsigned char tecla, int x, int y){
   if(tecla==27) exit(0);
	if(tecla==8){
		puntos --;
		glutPostRedisplay();
	}
}

//funcion que revisa
bool ccw(int a, int b, int c){
   double area2 = (pos_x[b]-pos_x[a])*(pos_y[c]-pos_y[a]) 
                - (pos_y[b]-pos_y[a])*(pos_x[c]-pos_x[a]);//determinante
/*si su area2>=0 -> true (vuelta a la izquierda),
si no, false (vuelta a la derecha)*/
   return area2>=0; 
}


//calcula el area entre 2 vertices y el punto del mouse
bool puntoDentro(int a, int b){
   double area = (pos_x[b]-pos_x[a])*(coordsPuntoMouse[1]-pos_y[a])
- (pos_y[b]-pos_y[a])*(coordsPuntoMouse[0]-pos_x[a]);//determinante
/*si area>=0 -> true(vuelta a la izquierda), 
si no, false ( vuelta a la derecha)*/
   return area>=0; 
}

void dibuja(void){
   glClear(GL_COLOR_BUFFER_BIT); 
   glColor3f(0,0,0);  
   glPointSize(4);           
   int i;
   GLboolean esVerde = GL_FALSE;
   if(puntos>2){
       i=0; //cantidad de chequeos que tiene que hacer es en cojunto de 3 cerrados
       //es una lista circular, el while incrementa i para recorrer de vuelta circular
       //si se salio antes, es porque una dio vuelta a la derecha
       //con el modulo de numero de puntos es con lo que doy la vuelta
       while(ccw(i%puntos,(i+1)%puntos,(i+2)%puntos) && i<puntos+2 ){
	    i++;
		} //ccw regresa true or false, checa que no salga de la dim del arreglo (cada conjunto de 3 cerrado)
       //(i==puntos+2)?glColor3f(0,1,0):glColor3f(1,0,0); 
       if (i==puntos+2){
       	glColor3f(0,1,0); //convexo
       	esVerde = GL_TRUE;
	   }else{
	   	glColor3f(1,0,0); //cóncavo
	   }
   }
   glBegin(GL_POINTS);
     for (i=0; i<puntos; i++)
         glVertex2i(pos_x[i], pos_y[i]);
   glEnd();
   glBegin(fin?GL_LINE_LOOP:GL_LINE_STRIP);
     for (i=0; i<puntos; i++)
         glVertex2i(pos_x[i], pos_y[i]);
   glEnd();
   glFlush(); 	
   if(fin){ //si ya termino...
   		i=0; //si no, no detecta bien en ciertos lados del poligono
   		while(puntoDentro(i%puntos,(i+1)%puntos) && i<puntos+2 ) i++;
   		if (i==puntos+2){
       	glColor3f(0,1,0);
	   }else{
	   	glColor3f(1,0,0);
	   }
   		//aqui va logica:
   		glBegin(GL_POINTS);
   			glVertex2i(coordsPuntoMouse[0], coordsPuntoMouse[1]);
   			for (i=0; i<puntos; i++)
         		glVertex2i(pos_x[i], pos_y[i]);
   		glEnd();
   		glBegin(GL_LINE_LOOP);
     		for (i=0; i<puntos; i++)
         		glVertex2i(pos_x[i], pos_y[i]);
   		glEnd();
   		glFlush();
   }
   
   
}
int main(int argc, char** argv){
	//se registran en main pero no se llaman
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Poligono convexo");
  // Registro de funciones
  glutDisplayFunc(dibuja);
  glutMouseFunc(raton);
  glutKeyboardFunc(teclado);
  glutSpecialFunc(termina);
  glutReshapeFunc(ajusta);
  glutMainLoop(); //hasta este punto se llaman
  return 0;
}
