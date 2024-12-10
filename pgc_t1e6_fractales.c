#include <stdio.h>
#include "random.h"
#include "ifs.h"
#define DIM 8
#define ITERA 7

void fractal(void (*f)(float, float*)){
	float punto[2]={0.5, 0.5};
	for(int i=0; i<ITERA; i++){
		//con una probabilidad de 0.33 llamo a una funcion
		float prob = rnd01();
		(*f)(prob, punto);
		printf( "(%.2f, %.2f)", punto[X], punto[Y]);
	}
}

int main(){
	semilla(5);
    printf("\nTriangulo Sierpinski\n");
	fractal(sierpi);
    printf("\nHelecho de Barnsley\n");
	fractal(barnsley);
	printf("\nDragon\n");
	fractal(dragon);
    return 0;
}