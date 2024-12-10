#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define dim 3 

void llenaMatrices(float mb[][dim], int d){
	srand(98);
	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			mb[i][j] = (float)rand()/(RAND_MAX) * 7;	
		}
	}
}


void suma(float ma[][dim], float mb[][dim], float mr[][dim], int d){
	printf("\nSuma\n");
	for (int i=0; i<d;i++){
		for(int j=0; j<d ;j++){
			mr[i][j]= ma[i][j] + mb[i][j];
		} 
	}
}

void multiplica(float ma[][dim], float mb[][dim], float mr[][dim], int d){
	printf("\nMultiplica\n");
	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			mr[i][j] = 0;
			for(int k=0; k<d; k++){
				mr[i][j] += ma[i][j] * mb[j][i];
			}
				
		}
	}
}

void creaS(float v[],float m[][dim],int d){
	printf("\nDiagonal\n");
	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			if(i == j)
				m[i][j] = v[i];
			else			
				m[i][j] = 0;
		}
	}	
}

void imprimeM(float m[][dim],int d,int dig){
	for(int i=0; i<d; i++){
		for(int j=0; j<d; j++){
			printf("%.*f ",dig,m[i][j]);
		}
		printf("\n");	
	}
}