//****************************  INSTRUCCIONES  ************************************//
/*Crea una estructura llamada cartesiana que representa un punto con valores (x,y)
y una lista dinámica de cartesiana. Solicita los datos al usuario hasta que la coordenada sea (0,0).
Imprime el contenido de la lista mostrando su equivalente en coordenadas polares.*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Definimos la estructura del nodo

struct cartesiana{
	float datox;
	float datoy;
	//apuntador que apunta a una estructura cartesiana
	struct cartesiana *sig;
}; 
typedef struct cartesiana Cartesiana; 
	
//Crear el puntero global inicial
Cartesiana *inicio = NULL;

//Función que agrega nodos
//La func recibe int y regresa un puntero a
//una estructura cartesiana
Cartesiana *creaNodo(float x, float y){
	//almacena la dir de memoria del nuevo nodo que creemos
	Cartesiana *p;
	//sizeof devuelve en bytes
	//malloc devuelve ptr genérico void * entonces lo convertimos
	//a un ptr struct cartesiana
	p = (Cartesiana *) malloc(sizeof(Cartesiana));
	p->datox = x;
	p->datoy = y; 
	p->sig=NULL;
	return p;
}

void insertaNodo(float x, float y){
	//ptr a inicio
	Cartesiana *aux= inicio;
	//si la lista está vacía
	if(inicio == NULL){	
	//inicio se le asigna ptr al nuevo nodo que creamos
		inicio = creaNodo(x,y); 
	}else{
		//encontramos último nodo
		while(aux->sig != NULL)
			aux = aux->sig;
		//creamos un nodo al final de la lista
		aux->sig = creaNodo(x,y);
	}
} 
					

void transformaPolar(float x, float y){
	float r = sqrt(x*x + y*y);
	float theta = atan2(y,x);
	float theta_grados = theta* (180 / M_PI);
	printf("		  (%.1f , %.1f )\n",r,theta_grados);
}
void imprimeLista(){
	Cartesiana *aux = inicio;
	printf("Cartesiana (x,y)	Polar (r,angulo)\n");
	while(aux != NULL){
		printf("( ");
		printf(" %.1f , %.1f )",aux->datox, aux->datoy);
		transformaPolar(aux->datox, aux->datoy);
		aux = aux->sig; 	
	}
}
void liberaMemoria(){
	Cartesiana *tmp;
	while(inicio !=NULL){
		tmp = inicio;
		inicio = inicio->sig;
		free(tmp);	
	}
	printf("Memoria liberada");	
}
 
int main(){
	float x=0.0, y=0.0;
	do{
		printf("Coordenadas x,y: ");
		scanf("%f,%f",&x,&y);
		if (x !=0 || y!=0)
			insertaNodo(x,y);		
	}while (x != 0 || y != 0);
	imprimeLista();
	liberaMemoria();
	return 0;	
}
