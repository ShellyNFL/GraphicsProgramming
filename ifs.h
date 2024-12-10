#define X 0
#define Y 1

//ITERATED FUNCTION SYSTEM
//Triangulo Sierpinsky
void fs1(float x, float y, float* p ){ //Coordenadas 1 sierpinsky
	p[X] = 0.5 * x;
	p[Y] = 0.5 * y;
}
void fs2(float x, float y, float* p){//fCoordenadas 2 sierpinsky
	p[X] = 0.5 * x + 0.5;
	p[Y] = 0.5 * y;	
}
void fs3(float x, float y, float* p){//Coordenadas 3 sierpinsky
	p[X] = 0.5 * x  + 0.25;
	p[Y] = 0.5 * y + 0.433;
}
//Helecho de Barnsley
void fb1(float x, float y, float* p){//Coordenadas 1 barnsley
	p[X] = 0.5;
	p[Y] = 0.16 * y;
}
void fb2(float x, float y, float* p){//Coordenadas 2 barnsley
	p[X] = 0.85 * x + 0.04 * y + 0.075;
	p[Y] = -0.04 * x + 0.85 * y + 0.18;
}
void fb3(float x, float y, float* p){//Coordenadas 3 barnsley
	p[X] = 0.2 * x - 0.26 * y + 0.4;
	p[Y] = 0.23 * x + 0.22 * y + 0.045;
}
void fb4(float x, float y, float* p){//Coordenadas 4 barnsley
	p[X] = -0.15 * x + 0.28 * y + 0.575;
	p[Y] = 0.26 * x + 0.24 * y - 0.086;
}
//Dragon
void fd1(float x, float y, float* p){//Coordenadas 3 barnsley
	p[X] = 0.824074 * x + 0.281482 * y + 0.1002660;
	p[Y] = -0.212346 * x + 0.864198 * y + 0.0951123;
}
void fd2(float x, float y, float* p){//Coordenadas 4 barnsley
	p[X] = 0.088272 * x + 0.520988 * y + 0.5344;
	p[Y] = -0.463889 * x - 0.377778 * y + 1.0415240;
}
//Sierpinsky
void sierpi(float r, float* p){
	if( r <= 0.33) fs1(p[X],p[Y],p);
	else if( r <= 0.66) fs2(p[X],p[Y],p);
	else fs3(p[X],p[Y],p);
}
//Barnsley
void barnsley(float r, float*p){
	if(r<=0.01) fb1(p[X],p[Y],p);
	else if( r <= 0.86) fb2(p[X],p[Y],p);
	else if( r <= 0.93)fb3(p[X],p[Y],p);
	else if(r <= 1.00)fb4(p[X],p[Y],p);
}
//Dragon
void dragon(float r, float* p){
	if( r <= 0.79) fd1(p[X],p[Y],p);
	else fd2(p[X],p[Y],p);
}

// para el helecho las 4 funciones, y el equivalente a sier con los ifs (probabilidades correspondientes)
//