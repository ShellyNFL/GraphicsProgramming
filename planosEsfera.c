#include <gl/glut.h>
#include <stdio.h>
#define ALTOIMG	315
#define ANCHOIMG 640
//rana 364, 400
//mar 315 640
void ajusta(int ancho, int alto) {
    glClearColor(0.8,0.8,0.8,0.0);	// color de background blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55,1,0.1,10); //-10 más lejano
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D); //habilito el pegado de textura
}

GLuint texturas[2]; 
//REMINDER para procedural potencias de dos
//2 de alto (renglones),2 de ancho (columnas) y 3 rbg
GLubyte tablero[2][4][3] = {  {  {0,0,0}, {255,255,255},{0,0,0},{255,255,255} },        
							{  {255,255,255},{0,0,0},{255,255,255},{0,0,0} } };


//Carga imagen de archivo raw a textura OpenGL
void cargaTextura_raw(int ancho, int alto, const char *archivo,
                      GLuint *text, int id_textura, GLboolean esfera){
    unsigned char * datos;
    FILE * file = fopen( archivo, "rb" );
    if ( file == NULL ){ printf("archivo no encontrado"); exit(-1);}
    datos = (unsigned char *)malloc(ancho*alto*3);
    fread( datos, ancho * alto * 3, 1, file );
    fclose( file );
    
    glGenTextures(id_textura, text);
    glBindTexture(GL_TEXTURE_2D,*text);
    
    if (esfera){
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,ancho,alto,0,GL_RGB,GL_UNSIGNED_BYTE,datos);
}

							
void creaTextura(void){
	glGenTextures(1, &texturas[0]);
    /*A partir de aquí se  maneja para textura 1*/
    glBindTexture(GL_TEXTURE_2D,texturas[0]);
	//Aplicas propiedades de la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//Almacena textura en memoria OpenGL   ANCHO, ALTO
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 2,
	0, GL_RGB, GL_UNSIGNED_BYTE, tablero);
	
	cargaTextura_raw(ANCHOIMG,ALTOIMG,"./imagenes/mar.data",&texturas[1],1,GL_TRUE);
}

void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D,texturas[0]);
		glBegin(GL_QUADS);//rect arriba
			glTexCoord2f(0.0, 0.0); glVertex3i(-1,0,-5);
			glTexCoord2f(0.0, 4.0); glVertex3i(1,0,-5);
			glTexCoord2f(2.0, 4.0); glVertex3i(1,1,-2);
			glTexCoord2f(2.0, 0.0); glVertex3i(-1,1,-2);
		glEnd();
				
		glBegin(GL_QUADS);//rect abajo
			glTexCoord2f(0.0, 0.0); glVertex3i(-1,-0.5,-5);
			glTexCoord2f(0.0, 4.0); glVertex3i(1,-0.5,-5);
			glTexCoord2f(2.0, 4.0); glVertex3i(1,-1,-2);
			glTexCoord2f(2.0, 0.0); glVertex3i(-1,-1,-2);
		glEnd();
		
		glBindTexture(GL_TEXTURE_2D,texturas[1]);//esfera
		glEnable(GL_TEXTURE_GEN_S);
    	glEnable(GL_TEXTURE_GEN_T);
		glPushMatrix(); 
			glTranslatef(0,0,-2);
			glutSolidSphere(0.25,30,30);
		glPopMatrix();
		glDisable(GL_TEXTURE_GEN_S);
    	glDisable(GL_TEXTURE_GEN_T);
	glutSwapBuffers();
}
void salir(unsigned char key, int x, int y) {
   if (key == 27) exit(0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Esferas y Planos");
    creaTextura();
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}
