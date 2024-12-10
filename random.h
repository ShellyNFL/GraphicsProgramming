//recibe la funcion para trabajar numeros aleatorios
#include <stdlib.h>
//permite que genere dif semillas aleatorias
#include <time.h>

// Semilla fija s
void semilla(int s){
	srand(s);
} 
// Semilla aletoria 
void rnd(){
	srand((unsigned) time(NULL));
} 
// aleatorios entre [0 , 1)
float rnd01(){
	//constante en stdlid
	return (float)rand() / RAND_MAX;
}
// aleatorios entre [0 , fin]
int rnd0F(int fin){
	return rand() % (fin + 1);
}

// aleatorios entre [inicio , fin]
int rndIF(int inicio, int fin){
	return rand() % (fin - inicio + 1) + inicio;
}
// aleatorios  entre [-inicio, -fin]
int rndNINF(int inicio, int fin){
	return - rndIF(-fin, -inicio);
}
// aleatorios entre [-inicio, fin]
int rndNIF(int inicio, int fin){
	//hacemos el cast porque la probabilidad es entre 0 a 1
	float probNEG = (float)(-inicio/ (fin - inicio + 1.0));
	return(probNEG < rnd01()) ? -rnd0F(-inicio) : rnd0F(fin);
	 	
}
