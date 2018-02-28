/* Universidad Simon Bolivar
 * Sistemas de Operacion
 * Enero Marzo 2018
 * Jonathan Bandes; 11-10075
 * Profesor Lovera.
*/


#ifndef SYMBOL_H
#define SYMBOL_H


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct elementoLista{
	char* nombre[];
	int indice;
	struct elementoLista * siguiente;
	struct structCola *hijos;
	int visitado;
} Elemento;

#endif //SYMBOL_H