//****************************  INSTRUCCIONES  ************************************
/*Crea una biblioteca (.h) con funciones de matrices cuadradas float de dimensión máxima
8x8 y prueba su funcionamiento correcto replicando la salida mostrada. La matriz 2 se llena
con valores float [0.0, 7.0) generados aleatoriamente con semilla 98. La matriz 1 y los valores
de la diagonal se asignan en código.
 a) suma(ma,mb,mr,dim): recibe las matrices a sumar, la matriz donde guarda el resultado y
la dimensión.
 b) multiplica(ma,mb,mr,dim): recibe las matrices a multiplicar, la matriz para el resultado y
la dimensión. Se puede buscar cómo realizar la multiplicación.
 c) creaS(v,m,dim,): recibe un vector, una matriz para el resultado y la dimensión. Coloca en
la diagonal de la matriz los valores del vector, los demás valen 0.
 d) imprimeM(m,dim,dig): recibe la matriz con su dimensión y número de dígitos decimales a
mostrar(mínimo 0, máximo 3).*/

#include <stdio.h>
#include "funcionesMatrices.h"
#define DIM 3

int main(){
		
	float ma[DIM][DIM] = {{4,5,8},{9,3,1},{2,6,4}};
	float mb[DIM][DIM] = {0};
	float mr[DIM][DIM] = {0};
	float v[DIM] = {9,7.5,2};
	float m[DIM][DIM] = {0};
	llenaMatrices(mb,DIM);
	printf("Matriz 1\n");
	imprimeM(ma,DIM,0);
	printf("\nMatriz 2\n");
	imprimeM(mb,DIM,3);
	suma(ma,mb, mr,DIM);
	imprimeM(mr,DIM,3);
	multiplica(ma,mb, mr,DIM);
	imprimeM(mr,DIM,3);
	creaS(v,m,DIM);
	imprimeM(m,DIM,1);
	return 0;
}