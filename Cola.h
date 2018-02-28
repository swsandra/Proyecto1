/* Universidad Simon Bolivar
 * Sistemas de Operacion
 * Enero Marzo 2018
 * Jonathan Bandes; 11-10075
 * Giuli Latella; 08-10596
 * Profesor Lovera.
*/
#ifndef COLATA_H
#define COLATA_H value


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "Elemento.h"

typedef struct structCola{
	Elemento *inicio;
	Elemento *final;
	int tamanio;
} Cola;
void inicializacion_cola (Cola* tas);
int encolar (Cola* tas, char* nombre, int indice);
Elemento* quitar_cola (Cola* tas);
void imprimir_cola (Cola* tas);
Elemento* encontrar_cola(Cola* tas, int indice);

#endif// COLATA_H