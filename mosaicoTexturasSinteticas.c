#include <gl/glut.h>
#include <stdio.h>


void ajusta(int ancho, int alto) {
    glClearColor(0.8,0.8,0.8,0.0);	// color de background blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,11,0,11,1, 10); //-1 es el más cerca, -10 más lejos  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D); //habilito el pegado de textura
}

GLuint texturas[3]; 
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
	cargaTextura_raw(368,460,"./imagenes/hongo.data",&texturas[0],0,GL_FALSE);
	cargaTextura_raw(368,552,"./imagenes/honey.data",&texturas[1],1,GL_FALSE);
	cargaTextura_raw(339,509,"./imagenes/planta.data",&texturas[2],2,GL_FALSE);
}

void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_ADD);
	glBindTexture(GL_TEXTURE_2D,texturas[0]);	
	glBegin(GL_QUADS);
		glColor3ub(255,0,0);
		glTexCoord2f(0.0, 1.0); glVertex3i(1,1,-2);//rabi
		glTexCoord2f(0.0, 0.0); glVertex3i(4,1,-2);
		glTexCoord2f(1.0, 0.0); glVertex3i(4,4,-2);
		glTexCoord2f(1.0, 1.0); glVertex3i(1,4,-2);
		glColor3ub(237, 211, 130);
		glTexCoord2f(0.0, 0.0); glVertex3i(7,4,-2);//rcd
		glTexCoord2f(1.0, 0.0); glVertex3i(10,4,-2);
		glTexCoord2f(1.0, 1.0); glVertex3i(10,7,-2);
		glTexCoord2f(0.0, 1.0); glVertex3i(7,7,-2);
		glColor3ub(27, 27, 58);
		glTexCoord2f(0.0, 1.0); glVertex3i(4,7,-2);//rac
		glTexCoord2f(1.0, 1.0); glVertex3i(7,7,-2);
		glTexCoord2f(1.0, 0.0); glVertex3i(7,10,-2);
		glTexCoord2f(0.0, 0.0); glVertex3i(4,10,-2);
	glEnd();
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texturas[1]);
	glBegin(GL_QUADS);
		glColor3ub(206, 204, 204);
		glTexCoord2f(0.0, 0.0); glVertex3i(4,1,-2);//rabc
		glTexCoord2f(1.0, 0.0); glVertex3i(7,1,-2);
		glTexCoord2f(1.0, 1.0); glVertex3i(7,4,-2);
		glTexCoord2f(0.0, 1.0); glVertex3i(4,4,-2);
		glColor3ub(105, 54, 104);
		glTexCoord2f(1.0, 0.0); glVertex3i(1,4,-2);//rci
		glTexCoord2f(1.0, 1.0); glVertex3i(4,4,-2);
		glTexCoord2f(0.0, 1.0); glVertex3i(4,7,-2);
		glTexCoord2f(0.0, 0.0); glVertex3i(1,7,-2);
		glColor3ub(255, 53, 98);
		glTexCoord2f(1.0, 1.0); glVertex3i(7,7,-2);//rad
		glTexCoord2f(0.0, 1.0); glVertex3i(10,7,-2);
		glTexCoord2f(0.0, 0.0); glVertex3i(10,10,-2);
		glTexCoord2f(1.0, 0.0); glVertex3i(7,10,-2);
	glEnd();
	//Establece condiciones de aplicación
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_BLEND);	
	glBindTexture(GL_TEXTURE_2D,texturas[2]);
	glBegin(GL_QUADS);
		glColor3ub(58, 125, 68);
		glTexCoord2f(1.0, 0.0); glVertex3i(7,1,-2);//rabd
		glTexCoord2f(1.0, 1.0); glVertex3i(10,1,-2);
		glTexCoord2f(0.0, 1.0); glVertex3i(10,4,-2);
		glTexCoord2f(0.0, 0.0); glVertex3i(7,4,-2);		
		glColor3ub(83, 77, 65);
		glTexCoord2f(0.0, 0.0); glVertex3i(4,4,-2);//rcc
		glTexCoord2f(1.0, 0.0); glVertex3i(7,4,-2);
		glTexCoord2f(1.0, 1.0); glVertex3i(7,7,-2);
		glTexCoord2f(0.0, 1.0); glVertex3i(4,7,-2);
		glColor3ub(255, 255, 255);	
		glTexCoord2f(0.0, 1.0); glVertex3i(1,7,-2);//rai
		glTexCoord2f(0.0, 0.0); glVertex3i(4,7,-2);
		glTexCoord2f(1.0, 0.0); glVertex3i(4,10,-2);
		glTexCoord2f(1.0, 1.0); glVertex3i(1,10,-2);					
	glEnd();

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