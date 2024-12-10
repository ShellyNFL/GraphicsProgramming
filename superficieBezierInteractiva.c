/*-------------------------INSTRUCCIONES--------------------------
Parte de una malla de puntos de control de 4x4 y dibuja tanto los puntos como la superficie de
Bezier, con una proyección en 3D que puedas girar.
 . Con las flechas vas “saltando” de punto de control a punto de control
 . Una vez elegido un punto de control lo mueves con teclas en la dirección X, Y o Z
 . La superficie se va modificando según mueves los puntos
 . Los puntos de control aparecen y desaparecen con alguna tecla */
 
#include <GL/glut.h>
GLfloat  girax = 0, giray= 0, x=0, y=0;
GLboolean ejes = GL_TRUE, clic=GL_FALSE, puntosctrl= GL_TRUE;
int gx, gy, coordx=-6 , coordy = 6, coordz=0;
int columnaSeleccionada = 0;
int renglonSeleccionado = 0;

/*Los números representan:
filas, columnas dentro de cada fila, cantidad de componentes de cada punto en cada fila y columna
o sea cada fila tiene 4 puntos que a su vez tiene 3 puntos*/
GLfloat ptosctl[4][4][3] = {
    {{-6, 6, 0}, {-2, 6, 0}, {2, 6, 0}, {6, 6, 0}},//cada renglon hace la dirección horizontal direccion u
    {{-6, 2, 0}, {-2, 2, 0}, {2, 2, 0}, {6, 2, 0}},//cada columna es en dirección v (vertical)
    {{-6, -2, 0}, {-2, -2, 0}, {2, -2, 0}, {6, -2, 0}},
    {{-6, -6, 0}, {-2, -6, 0}, {2, -6, 0}, {6, -6, 0}}};
    
void mover (void) {
    glRotated( girax, 1.0, 0.0, 0.0);
    glRotated( giray, 0.0, 1.0, 0.0);
}
void raton(int boton, int estado, int xv, int yv) {
    clic= boton==GLUT_LEFT_BUTTON && estado==GLUT_DOWN;
    if(clic){
        gx = xv;
        gy = yv;
    }
    glutPostRedisplay();
}
void girar(int xv, int yv) {
    if (clic){  // inicia circulos con centro
        girax -= (gy - yv);  //alrededor eje y (alturas)
        giray -= (gx - xv);  //alrededor eje x (izq der)
        gx = xv;
        gy = yv;
    }
    glutPostRedisplay();
}
    
void inicializa(void){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ptosctl[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
}
void ajusta(int ancho, int alto) {
    glViewport(0, 0, ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-12.0, 12.0, -12.0, 12.0, -12.0, 12.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void creaEjes(float largo) {
    glColor3f(0.0,0.0,0.0);
    //aquí se dibujan las líneas de los ejes
    glBegin( GL_LINES );
        glVertex3f (0.0,0.0,0.0); glVertex3f (largo,0.0,0.0);
        glVertex3f (0.0,0.0,0.0); glVertex3f (0.0,largo,0.0);
        glVertex3f (0.0,0.0,0.0); glVertex3f (0.0,0.0,largo);
    glEnd();
    float base=largo*.025, alto=largo*.06;
    glColor3f(1,0,0);
    glPushMatrix();  //eje x
        glRotatef(90,0,1,0);
        glTranslatef(0,0,largo);
        glutSolidCone(base,alto,10,10);
    glPopMatrix();
    glColor3f(0,1,0);
    glPushMatrix();  //eje y
        glRotatef(-90,1,0,0);
        glTranslatef(0,0,largo);
        glutSolidCone(base,alto,10,10);
    glPopMatrix();
    glColor3f(0,0,1);
    glPushMatrix();  //eje z
        glTranslatef(0,0,largo);
        glutSolidCone(base,alto,20,10);
    glPopMatrix();
    glColor3f(0.0,0.0,0.0);
}

void dibujaPuntosControl(){
    glPointSize(7.0);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) {
            (i == renglonSeleccionado && j == columnaSeleccionada) ?
			 glColor3ub(114, 9, 183): glColor3ub(138, 201, 38);
            glBegin(GL_POINTS);
            	glVertex3fv(&ptosctl[i][j][0]);
            glEnd();
        }
}
void dibuja(void){
    int i,j;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        mover();
	    if (ejes) creaEjes(9);
	    // Superficie de Bezier
	    glLineWidth(2); 
	    //20 segmentos para dir u de 0 a 1 (vertical); luego 10 segmentos de 0 a 1 (horizontal)
	    glColor3ub(39, 154, 241);
	    glMapGrid2f(20,0,1,10,0,1);
	    glEvalMesh2(GL_LINE,0,20,0,10);
	    // Puntos de control
	    if (puntosctrl) dibujaPuntosControl();
	    glPopMatrix();
	    glColor3ub(0, 0, 0);
    glutSwapBuffers();
}
void teclado(unsigned char key, int x, int y) {
    switch(key) {
        case 27: exit(0); break;
        case 'p': puntosctrl = !puntosctrl; break;
        case 'X': ptosctl[renglonSeleccionado][columnaSeleccionada][0] += 0.5; break;
        case 'x': ptosctl[renglonSeleccionado][columnaSeleccionada][0] -= 0.5; break;
        case 'Y': ptosctl[renglonSeleccionado][columnaSeleccionada][1] += 0.5; break;
        case 'y': ptosctl[renglonSeleccionado][columnaSeleccionada][1] -= 0.5; break;
        case 'Z': ptosctl[renglonSeleccionado][columnaSeleccionada][2] += 0.5; break;
        case 'z': ptosctl[renglonSeleccionado][columnaSeleccionada][2] -= 0.5; break;
    }
    /*Se tuvo que volver a hacer aquí porque sino lo único que se movía era el punto,
	la superficie no reflejaba ningún cambio porque seguía mapeando los datos originales
	cargados en inicializa*/
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ptosctl[0][0][0]);
    glutPostRedisplay();
}

//función que me ayuda a poder mover los puntos individuales
void flechas(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_RIGHT:
            if (columnaSeleccionada < 3)
                columnaSeleccionada++;
            break;
        case GLUT_KEY_LEFT:
            if (columnaSeleccionada > 0)
                columnaSeleccionada--;
            break;

        case GLUT_KEY_UP:
            if (renglonSeleccionado > 0)
                renglonSeleccionado--;
            break;

        case GLUT_KEY_DOWN:
            if (renglonSeleccionado < 3)
                renglonSeleccionado++;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(10,10);
    glutCreateWindow ("Superficie de Bezier interactiva");
    inicializa();
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutSpecialFunc(flechas);
    glutKeyboardFunc(teclado);
    glutMouseFunc(raton);
    glutMotionFunc(girar);
    glutMainLoop();
    return 0;             
}
