//Practica 8 - Ejercicio 3: curvas Bezier interactivas con valores equidistantes. 
//Ariadne Zinser y Shelly Flores
//Programa elaborado con base en el programa "ejerBezier.c", de la Dra. Carmen Villar y el programa pgc_t3e2_convexo.c
//referencia principal: Presentacion "Interaccion, algoritmos y animacion" -"Algoritmo poligono convexo"

#include <stdbool.h>
#include <GL/glut.h>
#include <math.h>
int n = 21;
GLfloat arreglo_t [21];
GLfloat x_t [21];
GLfloat y_t[21];
GLfloat distEuclidiana[21];
GLfloat distAcum[21];
GLfloat norm[21];
GLfloat tn[21];
GLfloat tn_x[21];
GLfloat tn_y[21];
GLboolean t_param = GL_FALSE;
GLboolean t_equiDist = GL_FALSE;
GLfloat array_prueba[4][3]={{-4.0,-4.0,0.0},{-2.0,4.0,0.0},{2.0,-4.0,0.0},{4.0,4.0,0.0}};
GLfloat ptosctl[20][3]; //arreglo que permite 20 pts de control
int puntos = 0; //contador de ptos de control
GLboolean fin=GL_FALSE; //bandera para marcar fin de dibujar/borrar

void dibujaT_equidistantes(){
	
	//llena arreglo t: 
		arreglo_t[0] = 0.0;
	for (int i = 1; i<21; i++){
		arreglo_t[i]= arreglo_t[i-1]+0.05;
	}
	for (int i = 0; i<21; i++){
		//llena arreglo x(t): 
		x_t[i]= pow((1-arreglo_t[i]), 3)*ptosctl[0][0] + 3*pow((1-arreglo_t[i]), 2)*arreglo_t[i]*ptosctl[1][0]+3*(1-arreglo_t[i])*pow(arreglo_t[i],2)*ptosctl[2][0]+pow(arreglo_t[i],3)*ptosctl[3][0];
		//llena arreglo y(t)
		y_t[i]= pow((1-arreglo_t[i]), 3)*ptosctl[0][1] + 3*pow((1-arreglo_t[i]), 2)*arreglo_t[i]*ptosctl[1][1]+3*(1-arreglo_t[i])*pow(arreglo_t[i],2)*ptosctl[2][1]+pow(arreglo_t[i],3)*ptosctl[3][1];
	}
	//calcula distancia euclidiana
	distEuclidiana[0]=0.0;
	for (int i = 1; i<21; i++){
		//llena arreglo t: 
		distEuclidiana[i]= sqrt(pow((x_t[i]-x_t[i-1]),2) + pow((y_t[i]-y_t[i-1]),2));	
	}
	//calcula la distancia acumulada
	distAcum[0]=0.0;
	for (int i = 1; i<21; i++){
		//llena arreglo t: 
		distAcum[i]= distAcum[i-1]+distEuclidiana[i];	
	}
	//normaliza
	for (int i = 0; i<21; i++){
		//llena arreglo t: 
		norm[i]= distAcum[i]/distAcum[20];	
	}
	//tn
	tn[0]=0.0;
	for (int i = 1; i<21; i++){
		//llena arreglo t: 
		tn[i]= arreglo_t[i-1]+(arreglo_t[i]-norm[i-1])/(norm[i]-norm[i-1])*(arreglo_t[i]-arreglo_t[i-1]);	
	}
	for (int i = 0; i<21; i++){
		//llena arreglo x(t): 
		tn_x[i]= pow((1-tn[i]), 3)*ptosctl[0][0] + 3*pow((1-tn[i]), 2)*tn[i]*ptosctl[1][0]+3*(1-tn[i])*pow(tn[i],2)*ptosctl[2][0]+pow(tn[i],3)*ptosctl[3][0];
		//llena arreglo y(t)
		tn_y[i]= pow((1-tn[i]), 3)*ptosctl[0][1] + 3*pow((1-tn[i]), 2)*tn[i]*ptosctl[1][1]+3*(1-tn[i])*pow(tn[i],2)*ptosctl[2][1]+pow(tn[i],3)*ptosctl[3][1];
	}
	//prueba impresiones
	for (int i = 0; i < n; i++) {
        printf("%.2f ", arreglo_t[i]);
    }
    printf("\n arreglo de x(t)\n");
    	for (int i = 0; i < n; i++) {
        printf("%.2f ", x_t[i]);
    }
    printf("\n");
    printf("\n arreglo de y(t)\n");
    	for (int i = 0; i < n; i++) {
        printf("%.2f ", y_t[i]);
    }
    printf("\n");
     printf("\n arreglo de distancia euclidiana: \n");
    	for (int i = 0; i < n; i++) {
        printf("%.2f ", distEuclidiana[i]);    
    }
    printf("\n");
    printf("\n arreglo de distancia acumulada: \n");
    	for (int i = 0; i < n; i++) {
        printf("%.2f ", distAcum[i]); 
    }
    printf("\n");
     printf("\n arreglo de normalizacion: \n");
    	for (int i = 0; i < n; i++) {
        printf("%.2f ", norm[i]); 
    }
    printf("\n");
       printf("\n arreglo de tn: \n");
    	for (int i = 0; i < n; i++) {
        printf("%.2f ", tn[i]);
    }
    printf("\n");
    printf("\n arreglo de x(tn)\n");
    	for (int i = 0; i < n; i++) {
        printf("%.2f ", tn_x[i]);  
    }
    printf("\n");
    printf("\n arreglo de y(tn)\n");
    	for (int i = 0; i < n; i++) {
        printf("%.2f ", tn_y[i]);     
    }
	//DIBUJA LOS PUNTOS USANDO Tn: 
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i <= 21; i++)
		glVertex3f(tn_x[i], tn_y[i],0.0);
	glEnd();
}

void dibujaT_parametricos(){
	//T_PARAM
	glEnable(GL_MAP1_VERTEX_3);
	glLineWidth(6);
	glColor3f(0.0, 1.0, 0.0);
	glMapGrid1f(15,0,1);
	glEvalMesh1(GL_POINT, 0, 15); 
	//glFlush();
	//T EQUIDISTANTES
}

void dibujaTexto(void *tipo, char *s ) { //funcion tomada del programa "tablero.c" de la Dra. Carmen Villar
   for (int i = 0; i < strlen(s); i++) 
       glutBitmapCharacter(tipo, s[i]);
}

//FUNCION PARA PINTAR PUNTOS DE CONTROL CON CLICK
void raton(int boton, int estado, int x, int y){
   int alto_ventana=480;
   if (!fin && puntos<4){ //si aun no es el fin de los puntos de control, 
              //guardo las coordenadas x y z en sus respectivos arreglos
       if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
           ptosctl[puntos][0] = x; //guarda las coordenada x
           ptosctl[puntos][1] = alto_ventana - y; //guarda la coordenada y
           ptosctl[puntos][2] = 0.0; //z es 0.0
           puntos++; //incrementa el contador de puntos de control
       }
       glutPostRedisplay();
   }
}

//FUNCION PARA TERMINAR DE PINTAR PUNTOS DE CONTROL
void termina(int tecla, int x, int y){
   switch(tecla) {
     case GLUT_KEY_UP: 
	 			fin=GL_TRUE; //lo cambio por GLUT_KEY_UP y DOWN porque no tengo las otras en mi teclado
                break;
     case GLUT_KEY_DOWN: //puntos=0;
               fin=GL_FALSE; //apaga la bandera fin para revertir
               break;
   }
   glutPostRedisplay();
}

//FUNCION PARA BORRAR PUNTO DE CONTROL
void teclado(unsigned char tecla, int x, int y){
   if(tecla==27) exit(0);
// Esc =>Salir del programa
	if(tecla==8 && fin==GL_FALSE){ //si aun no se ha presionado la tecla de abajo, permite borrar
		//aqui va codigo para borrar puntos y vertices
		puntos --; //baja el contador 1 para dibujar un punto menos en el arreglo
		//pensaba borrar tambien las coordenadas del arreglo, 
		//pero realmente no es necesario porque solo no las va a leer en el ciclo
		glutPostRedisplay();
	}
	if (tecla == 'p'){
		t_param = !t_param;
		//printf("El valor de t_param es: %s\n", t_param ? "true" : "false");
		glutPostRedisplay();
	}
	if (tecla == 'e'&& puntos == 4){
		t_equiDist = !t_equiDist;
		glutPostRedisplay();
	}
}
void inicializa(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
void dibuja(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	//glRasterPos3f(100,450,1.);
	//dibujaTexto(GLUT_BITMAP_HELVETICA_12,"Presiona la flecha hacia arriba para bloquear dibujar/borrar.");
	//glRasterPos3f(100,425,1.);
	//dibujaTexto(GLUT_BITMAP_HELVETICA_12,"Presiona la flecha hacia abajo para desbloquear dibujar/borrar.");
	if (puntos>1){
		glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, puntos, &ptosctl[0][0]);
		//t empieza en 0 y termina en 1, distancia 3 entre cada punto de control, 
		//tantos puntos de control como marque el contador puntos, 
		//direccion del primer elemento del arreglo de puntos de control
		glEnable(GL_MAP1_VERTEX_3); //habilitar solo si hay mas de un punto (tal vez esta de mas)
	}else{
		glDisable(GL_MAP1_VERTEX_3); //deshabilitar si hay uno o ningun punto
	}
	
	//DIBUJAR PUNTOS DE CONTROL
	glPointSize(6.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		for (int i = 0; i < puntos; i++)
			glVertex3fv(&ptosctl[i][0]);
	glEnd();
	//DIBUJAR CURVA DE BEZIER
	glLineWidth(4);
	glColor3f(0.0, 0.0, 1.0);
	glMapGrid1f(20,0,1);
	glEvalMesh1(GL_LINE, 0, 20); //con linea que une los puntos
	
	if (t_param){
		//printf("El valor de t_param es: %s\n", t_param ? "true" : "false");
		dibujaT_parametricos();
	}
	if (t_equiDist){
		//printf("El valor de t_equiDist es: %s\n", t_equiDist ? "true" : "false");
		dibujaT_equidistantes();
	}
	glFlush();
}
void ajusta(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,500, 0,500, -10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void salir(unsigned char key, int x, int y) {
	if(key == 27) exit (0); 
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Curva de Bezier interactiva");
	inicializa();
	glutDisplayFunc(dibuja);
	glutMouseFunc(raton);
  	glutKeyboardFunc(teclado);
  	glutSpecialFunc(termina);
	glutReshapeFunc(ajusta);
	glutMainLoop();
	return 0;
}




