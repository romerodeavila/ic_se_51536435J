#include "leon3_bprint.h"

int8_t leon3_print_string(char* str) {
	uint32_t e = 0;
	int i = 0;

	//Comporbamos que no hay error
	// antes de entrar en el bucle
	// ni por fin de cadena -> '\o'
	// ni por el timeout -> e==1
	while (str[i] != '\0' && e == 0) {
		//Si la cadena no se ha acabado
		e += leon3_putchar(str[i]);
		i++;
	}

	return e;
}

// He intentado solucionar lo que me propusisteis en la corrección de la prac2b
int8_t leon3_print_uint8(uint8_t i){
	int8_t e=0; // Error
	uint8_t aux = 100; // Ira conteniendo 100, 10 y 1 para operar
					// con las centenas y decenas
	int8_t first=0; // Cuando el primer dígito se ha escrito cambia a 1
					// De esta forma evitamos que se escriban 0
					// antes del primer dígito

	if(i==0)
		leon3_putchar('0');
	else{
		while(aux&&(!e)){ // Mientras alguno no sean 0
			uint8_t n;

			n=i/aux; //Sacamos las centenas, decenas o unidades
			i-=aux*n; //Restamos las centena, decenas o unidades
			aux=aux/10;
			if(first||n){
				e=leon3_putchar(n+'0');
				first=1;
			}
		}
	}
	return e;
}

int8_t leon3_print_uint32(uint32_t i){
	int8_t e=0; // Error
	uint32_t aux = 1000000000; // Ira conteniendo 10⁹, 10⁸, 10⁷, etc
	int8_t first=0; // Cuando el primer dígito se ha escrito cambia a 1
					// De esta forma evitamos que se escriban 0
					// antes del primer dígito

	if(i==0)
		leon3_putchar('0');
	else{
		while(aux&&(!e)){ // Mientras alguno no sean 0
			uint8_t n;

			n=i/aux; //Sacamos las centenas, decenas o unidades
			i-=aux*n; //Restamos las centena, decenas o unidades
			aux=aux/10;
			if(first||n){
				e=leon3_putchar(n+'0');
				first=1;
			}
		}
	}
	return e;
}
