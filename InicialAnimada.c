/*------------------------INTRUCCIONES--------------------------
 Toma la letra de tu nombre, dibujar varias veces en diferentes
 lugares de la pantalla y utilizando menús elegir entre 5 opciones,
 la velocidad en milisegundos de cambio entre 2 colores (parpadeo).
 ---------------------------------------------------------------*/

#include <GL/glut.h>
#include <stdbool.h>

bool color = true;
/*para la primera iteración será el tiempo que tarde en 
mostrar la animación la primera vez*/
int time = 500; 

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void dibujaInicial(int x, int y){
	int inicialSolida[][2] = {
    {165, 285}, {145, 285}, {165, 300}, {142, 293},
    {150, 315}, {137, 294}, {120, 315}, {130, 294},
    {131, 294}, {105, 300}, {130, 285}, {105, 285}, 
    {130, 275}, {105, 270}, {134, 270}, {120, 255},
    {156, 270}, {141, 255}, {170, 260}, {145, 250},
    {170, 210}, {145, 227}, {156, 195}, {141, 217},
    {105, 195}, {121, 217}, {95, 210}, {114, 221},
    {95, 237}, {114, 237}
	};
	    
	glBegin(GL_QUAD_STRIP);
		for(int i=0;i<30;i++)
			glVertex2i(inicialSolida[i][0]+x,inicialSolida[i][1]+y);
	glEnd();
}

void dibuja(void) {
	//int x,y;
    glClear(GL_COLOR_BUFFER_BIT);
    //dibujaInicial(-90,-190, GL_QUAD_STRIP);
    for (int i=0; i<8; i++){  			
    		dibujaInicial(-80 + 75*i, -195 + 52*i);
	}
	//glFlush();
    glutSwapBuffers();
}

void tiempo(unsigned int msecs, void dibuja(), int valor){
	if(color){
		glColor3ub(255,0,124);
	}else{
		glColor3ub(0,61,155);	
	}
	color = !color;		
	glutTimerFunc(time,tiempo,1);
	glutPostRedisplay();	
}

int cambiaTiempo(opcion){
	switch (opcion){
		case 1: time= 500; break;
		case 2: time= 750; break;
		case 3: time= 1000; break;
		case 4: time= 1250; break;
		case 5: time= 1500; break;
		case 6: exit(0);
	}
}


void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Inicial Parpadeando");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutTimerFunc(time,tiempo,1);
    glutCreateMenu(cambiaTiempo); //acciones que tomará el menú
    	glutAddMenuEntry("500",1);
    	glutAddMenuEntry("750",2);
    	glutAddMenuEntry("1000",3);
    	glutAddMenuEntry("1250",4);
    	glutAddMenuEntry("1500",5);
    	glutAddMenuEntry("Salir",6);
    glutAttachMenu(GLUT_RIGHT_BUTTON); //que botón para que salga el menú
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}