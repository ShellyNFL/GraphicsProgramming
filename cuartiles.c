// Tarea 1 - Ejercicio 2: Lee archivo y hace operaciones 
//Ariadne Zinser y Shelly Flores
//Referencia Algoritmo de Ordenamiento Quicksort de: (W3Schools, s.f.)
//Referencia Lectura de Archivos de: (W3Schools, s.f.)
//Referencia Concepto EOF de: (W3Schools, s.f.)
#include <stdio.h>
#include <stdlib.h>
#define CELDAS 15
#define MAX_NUMEROS 15
float sacaCuartiles(int p, int numDatos){
    float i = (float)(p*numDatos)/100.0;
    if((p*numDatos)%100==0){
        return i-1;
    }else{
    return i;
    }
}
float calculaMedia(int arreglo[], int elementos){
    int suma = 0;
    float media = 0;
    for(int i=0; i<elementos; i++){
        suma = suma + arreglo[i];
    }
    media = (float)(suma)/elementos;
    return media;
}
int parteArreglo(int arreglo[], int bajo, int alto){
    int pivote = arreglo[alto]; //selecciona como pivote el número en la última celda del arreglo
    int i = bajo - 1; // -1 como índice bajo, para empezar
    for(int j=bajo; j<alto; j++){ //recorre el arreglo
        if(arreglo[j] <= pivote){ //si lo que hay en el índice j es menor o igual al pivote: 
            i++; //aumento el índice de i
            //va a hacer el swap
            int temporal = arreglo[i];
            arreglo[i]=arreglo[j];
            arreglo[j]=temporal; //ahora cambié de lugar esos dos números y aumenté índice de j. 
        }
    }
    int temporal = arreglo[i+1];
    arreglo[i+1]=arreglo[alto];
    arreglo[alto]=temporal;
    return i+1;
}
//QuickSort
void ordenaArreglo(int arreglo[], int bajo, int alto){
    if(bajo<alto){
        int indicePivote = parteArreglo(arreglo, bajo, alto);
        ordenaArreglo(arreglo, bajo, indicePivote-1);
        ordenaArreglo(arreglo, indicePivote+1, alto);
    }
}
void imprimeArreglo(int arreglo[CELDAS]){
    for(int i=0;i<CELDAS;i++){
        printf(" %d", arreglo[i]);
    }
}
int main() {
	//declaracion de arreglos
	//int archivo[MAX_NUMEROS];
	int i = 0;
	int numero;
	//PRUEBAS SIN LECTURA
    //int archivo[]={10,6,2,8,12,7,21,9,3,5,17,11,4,25,32};
    int archivo[]={15,3,2,9,12,14,5,1,6,22,4,45,2,5,8,45};
    int datos;
    int valoresP[]={25,50,75};
    float cuartil[3];
    /*lectura de archivo
    FILE *fptr;
	fptr = fopen("pgc_t1e2_numeros.txt", "r"); //abre archivo en modo lectura
    if(fptr == NULL) { //imprime mensaje de error si no logra abrir archivo
  		printf("\nProblema al abrir el archivo.");
	}
	while (fscanf(fptr, "%d", &numero) != EOF) { //lee cada numero en el archivo mientras este no se acabe (End of file)
        archivo[i++] = numero; //lo guarda en el arreglo
    }
    fclose(fptr);*/
    printf("\nNumeros leidos del archivo:\n");
    for (int j = 0; j < i; j++) {
        printf("%d ", archivo[j]);
    }
    printf("\n");
    datos=sizeof(archivo)/(sizeof(archivo[0]));
    printf("\nArreglo sin ordenar:\n");
    imprimeArreglo(archivo);
    ordenaArreglo(archivo, 0, datos-1);
    printf("\nArreglo ordenado:\n" );
    imprimeArreglo(archivo);
    printf("\nCantidad de datos: %d", datos);
    printf("\nMin: %d", archivo[0]);
    printf("\nMax: %d", archivo[datos-1]);
    
    for(int i=0; i<3; i++){
        cuartil[i]=sacaCuartiles(valoresP[i],datos);
        printf("\nCuartil %d es: %d", (i+1), archivo[(int)(cuartil[i])]);
    }
    printf("\nMedia: %f", calculaMedia(archivo, datos));
    return 0;
}


