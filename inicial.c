#include <GL/glut.h>

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void dibujaInicial(int x, int y,GLenum modo){
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
	//van en orden contrario a las manecillas del reloj
	int inicialMarco[][2] = {
		{165, 285}, {165, 300}, {150, 315}, {120, 315},{105, 300},  {105, 285}, 		
	    {105, 270}, {120, 255}, {141, 255}, {145, 250}, {145, 227}, {141, 217},	    
	    {121, 217}, {114, 221}, {114, 237}, {95, 237}, {95, 210}, {105, 195}, 
	    {156, 195}, {170, 210}, {170, 260}, {156, 270}, {134, 270}, {130, 275},	    
	    {130, 285},{131, 294},  {130, 294}, {137, 294}, {142, 293}, {145, 285}  
	}; 
	 	    
	glBegin(modo);
		if(modo == GL_QUAD_STRIP){
			for(int i=0;i<30;i++)
				glVertex2i(inicialSolida[i][0]+x,inicialSolida[i][1]+y);
		}
		if(modo == GL_LINE_LOOP){
			for(int i=0;i<30;i++)
				glVertex2i(inicialMarco[i][0]+x,inicialMarco[i][1]+y);
		}
	glEnd();
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    //dibuja mi inicial rellena
    glColor3ub(169,0,51);
    dibujaInicial(110,0, GL_QUAD_STRIP);
    //dibujaInicial(-90,-190, GL_QUAD_STRIP);
    
    //dibuja el contorno de mi inicial
    glLineWidth(2);
    dibujaInicial(260,0, GL_LINE_LOOP);
    glFlush();
}

void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Mi letra inicial");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}