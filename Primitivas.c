#include <GL/glut.h>

void ajusta(int ancho, int alto){
    glClearColor(0.83,0.71,0.92,0); //rosita el fondo
	//glClearColor(0.97,0.6,0.81,0.0); //rosita el fondo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

//x y y representan la posición de mi polígono
void dibujaPentagono(int x, int y, GLenum modo){
	//es un tipo de variable que contiene las opciones que puedes poner en glBegin
	//fuente https://www.khronos.org/opengl/wiki/OpenGL_Type
	GLenum glModo;
	/*modo = char(modo);
	//char *glModo;
	if (modo == 1)
		glModo = GL_LINE_LOOP;
	if(modo == 2)
		glModo = GL_POLYGON;*/
		
	//le doy las coordenadas de mi 1er pentágono
	int pentagono[][2] = {{75,75}, {195,75}, {195,165},{135,210}, {75,165}};
	glBegin(modo);
		for(int i=0; i<5; i++)
			glVertex2i(pentagono[i][0]+x, pentagono[i][1]+y);
	glEnd();	
}


void dibujaCuadrilatero(){
	//ejemplo sin guardar en vectores
	glBegin(GL_QUADS);
		glVertex2i(60,290);
		glVertex2i(280,320);
		glVertex2i(280,375);
		glVertex2i(75,435);	
	glEnd();
}

void dibujaNombre(void *tipo, char *s ) {
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);//limpia buffer de color, profundidad,acumulativo y stencil. Cambia palabra COLOR por DEPTH, ACCUM, STENCIL.
    
	//Pentágono en wireframe
	glColor3ub(0,133,69);
	dibujaPentagono(0,0,GL_LINE_LOOP);
	
	//Pentágono sólido
	glColor3ub(0,66,255);
	dibujaPentagono(195,0,GL_POLYGON);
	//glColor3ub(92,23,23);   //PORQUE AQUI ME TOMA EL COLOR ARRIBA
	
	//Pentágono con línea punto
	glEnable(GL_LINE_STIPPLE);
		glColor3ub(92,23,23);
		glLineStipple(2,0xBEBE); //BEBE representa 1011111010111110 los 1 pueden ser el punto o la lína dependiendo de que tantos pones
		//La distancia la toma del pentagono incial 
		dibujaPentagono(390,0,GL_LINE_LOOP);
	glDisable(GL_LINE_STIPPLE);
	
	//Cuadrilátero
	glColor3ub(222,0,101);
	dibujaCuadrilatero();
	
	//Pentágono con triángulos
	glBegin(GL_TRIANGLE_FAN);
		glColor3ub(249,255,52);
		glVertex2i(405,300);
		glColor3ub(77,255,52);
		glVertex2i(525,300);
		glColor3ub(52,224,255);
		glVertex2i(525,390);
		glColor3ub(146,52,255);
		glVertex2i(465,435);
		glColor3ub(255,52,136);
		glVertex2i(405,390);	
	glEnd();
	//Mi nombre
	glColor3ub(0,0,0);
	glRasterPos2i(270,15);
	dibujaNombre(GLUT_BITMAP_TIMES_ROMAN_10,"Shelly Naomi Flores Lopez");
    glFlush(); //envía inf del frame buffer al monitor 
}

void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//se indican las características de la tarjeta gráfica a ser utilizadas
    glutInitWindowSize(640,480);//tamaño en pixeles de la ventana
	glutInitWindowPosition(100, 150);//posición de la ventana respecto a esq sup izq de la pantalla
    //crea una ventana con el título especificado como parámetro
    //regresa un identificador único por ventana.
    glutCreateWindow("Practica 1");
    glutReshapeFunc(ajusta);//se invoca al abrir la ventana la 1ra vez y cuando cambia de tamaño 
    glutDisplayFunc(dibuja);//Se invoca al abrir la ventaja la 1ra vez. La función que invoca tiene las primitivas a dibujar
    glutKeyboardFunc(salir);
    glutMainLoop();//proceso que espera por eventos
    return 0;
}