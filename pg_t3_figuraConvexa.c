// Tarea 3 - Ejercicio 2: Reina 
//Ariadne Zinser y Shelly Flores
//Programa elaborado con base en el programa "convexo.c", de la Dra. Carmen Villar.
//referencia principal: Presentacion "Interaccion, algoritmos y animacion" -"Algoritmo poligono convexo"

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
   if (!fin){ //si aun no es el fin del poligono, guardo las coordenadas x y y en sus respectivos arreglos
       if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
           pos_x[puntos] = x;
           pos_y[puntos] = alto_ventana - y;
// voltea la coordenada y
           puntos++; //aqui incrementa los puntos
       }
       glutPostRedisplay();
   }else{ //si ya termino de dibujar el poligono convexo (si se prende la bandera de fin)
		if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
   			coordsPuntoMouse[0]=x;
   			coordsPuntoMouse[1]= alto_ventana - y; //guardo las coordenadas del mouse en el arreglo del mouse
   		}
   }
   glutPostRedisplay();
}
void termina(int tecla, int x, int y){
   switch(tecla) {
     case GLUT_KEY_UP: fin=GL_TRUE; //lo cambio por GLUT_KEY_UP y DOWN porque no tengo las otras en mi teclado
                        break;
     case GLUT_KEY_DOWN: puntos=0;
               fin=GL_FALSE;
   }
   glutPostRedisplay();
}
void teclado(unsigned char tecla, int x, int y){
   if(tecla==27) exit(0);
// Esc =>Salir del programa
	if(tecla==8){
		puntos --;
		glutPostRedisplay();
	}
}
//funcion que revisa el area caluclada con cada 3 vertices a,b,c.
bool ccw(int a, int b, int c){
   double area2 = (pos_x[b]-pos_x[a])*(pos_y[c]-pos_y[a]) //
                - (pos_y[b]-pos_y[a])*(pos_x[c]-pos_x[a]);//es el determinante
   return area2>=0; //si su area es mayor o igual que cero regresa true (fue vuelta a la izquierda), si no, regresa false (fue vuelta a la derecha)
}

//funcion inspirada en la funcion de la Dra. Carmen Villar, pero calcula el area entre 2 vertices y el punto del mouse
bool puntoDentro(int a, int b){ //solo se envian 2 vertices, porque las coordenadas del punto estan en un arreglo global (coordsPuntoMouse)
   double area = (pos_x[b]-pos_x[a])*(coordsPuntoMouse[1]-pos_y[a]) //
                - (pos_y[b]-pos_y[a])*(coordsPuntoMouse[0]-pos_x[a]);//es el determinante
   return area>=0; //si su area es mayor o igual que cero regresa true (esta dentro), si no, regresa false (esta fuera)
}

void dibuja(void){
   glClear(GL_COLOR_BUFFER_BIT); 
   glColor3f(0,0,0);  
   glPointSize(4);           
   int i;
   if(puntos>2){
       i=0; //cantidad de chequeos que tiene que hacer en cojunto de 3 cerrados
       //es una lista circular, el while incrementa i para recorrer de vuelta circular
       //si se salio antes, es porque una dio vuelta a la derecha
       //con el modulo de numero de puntos es con lo que doy la vuelta
       while( ccw(i%puntos,(i+1)%puntos,(i+2)%puntos) && i<puntos+2 ) i++; //ccw regresa true or false, checa que no salga de la dim del arreglo (cada conjunto de 3 cerrado)
       //hace las  veces de un arreglo circular, Gracias al modulo, si i ya esta en el ultimo vertice, el siguiente es nuevamente el primero
       if (i==puntos+2){ //si ya reviso el ultimo punto con los dos primeros vertices...
       	glColor3f(0,1,0); //decide que es convexo y lo pinta verde
	   }else{
	   	glColor3f(1,0,0); //decide que es concavo y lo pinta rojo
	   }
	   //vas a elegir entre verde o rojo mientras se cumpla lo de arriba
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
   //al terminar de dibujarlo, ya me permite hacer click con el mouse.
   	
   if(fin){ //si ya termino...
   		i=0; //reinicializo esto porque si no, no detecta bien en ciertos lados del poligono
   		while(puntoDentro(i%puntos,(i+1)%puntos) && i<puntos+2 ) i++; //misma logica que la funcion de la Dra. Carmen Villar (revisando area de cada 2 vertices con el punto).
   		if (i==puntos+2){
       	glColor3f(0,1,0); //si esta dentro, lo pinta verde (porque el area es positiva)
	   }else{
	   	glColor3f(1,0,0); //si esta fuera, lo pinta rojo (porque el area es negativa)
	   }
   		//aqui va logica:
   		glBegin(GL_POINTS);
   			glVertex2i(coordsPuntoMouse[0], coordsPuntoMouse[1]); //pinto el punto con su color correspondiente
   			for (i=0; i<puntos; i++)
         		glVertex2i(pos_x[i], pos_y[i]); //redibujo los puntos del poligono del color del punto
   		glEnd();
   		glBegin(GL_LINE_LOOP);
     		for (i=0; i<puntos; i++)
         		glVertex2i(pos_x[i], pos_y[i]); //redibujo las lineas del poligono del color del punto
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
