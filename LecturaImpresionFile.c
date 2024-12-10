//****************************  INSTRUCCIONES  ************************************//
/*Haz un dibujo con caracteres (ascii art) o toma uno de https://www.asciiart.eu en el bloc
de notas, coloca las iniciales del autor. Desde el programa lee e imprime el contenido del
archivo caracter a caracter, reporta el número de renglones, caracteres especiales, espacios
en blanco, dígitos y letras. Cada integrante del equipo muestra su dibujo.*/


//conteo del número de caracteres especiales
//conteo del número de espacios
		//conteo del número de dígitos
				//conteo del número de letras
#include <stdio.h> //aquí están funciones como fopen
#include <ctype.h>

int main(){
	FILE *dibujo_ascii;
	char elemento;
	int num_renglones = 0, num_char_especiales = 0,
	 num_espacios=0, num_digitos = 0,  num_letras = 0;
	dibujo_ascii = fopen("dibujo3.txt","r"); //abrimos nuestro dibujo en modo lectura
	if (dibujo_ascii == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
	//mientras que no sea el final del archivo vamos a: 
	//obtener caracteres por caracter de nuestro file
	while(( elemento = fgetc(dibujo_ascii)) != EOF){
		printf("%c",elemento);
		if (elemento == '\n') //num renglones
			num_renglones++;					
		if (ispunct(elemento) !=0 && isalnum(elemento) == 0) 
			num_char_especiales++;	 
		if (isspace(elemento) != 0 && elemento != '\n' 
		&& elemento != '\t' && elemento != '\f')
			num_espacios++;	
		if(isdigit(elemento) != 0)
			num_digitos++;
		if(isalpha(elemento) !=0)
			num_letras++;
	}
	fclose(dibujo_ascii);
 //Se le agrega uno más porque el último renglón ya no tiene un /n sino un EOF
	printf("\n\nNumero de renglones: %d\n", num_renglones+1);
    printf("Numero de caracteres especiales: %d\n", num_char_especiales);
    printf("Numero de espacios en blanco: %d\n", num_espacios);
    printf("Numero de digitos: %d\n", num_digitos);
    printf("Numero de letras: %d\n", num_letras);	
	return 0;	
}

