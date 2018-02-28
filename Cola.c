/* Universidad Simon Bolivar
 * Sistemas de Operacion
 * Enero Marzo 2018
 * Jonathan Bandes; 11-10075
 * Profesor Lovera.
*/
#include "Cola.h"

void inicializacion_cola (Cola* tas){
	
	tas->inicio = NULL;
	tas->final = NULL;
	tas->tamanio = 0;
}
/*Apilar*/
int encolar (Cola* tas, char* nombre, int indice){
		
	Elemento* newElem;

	Elemento* actual = tas->inicio;
	
	if((newElem = (Elemento *)malloc (sizeof(Elemento))) == NULL){
		return -1;
	}

	if ((newElem->nombre = (char *)malloc (50 * sizeof(char))) ==NULL){
		return -1;
	}

	strcpy (newElem->nombre, nombre);
	printf("El sring q tal %s\n",newElem->nombre);
	newElem->indice = indice;
	newElem->siguiente = NULL;
	newElem->hijos = NULL;
	newElem->visitado = 1;

	if (tas->tamanio == 0){
		tas->inicio = newElem;
		tas->final = newElem;
		//newElem->siguiente = NULL;
		tas->tamanio++;
		return 0;
	} else{
		while(actual->siguiente !=NULL){
			
			actual = actual->siguiente;
		}
		tas->final = newElem;
		actual->siguiente = newElem;
		//newElem->siguiente = NULL;
		tas->tamanio++;
	}
	return 0;
}
/*Desencola elemento de la estructura*/
Elemento* quitar_cola (Cola* tas){
	
	Elemento* temporal;
	if(tas->tamanio == 0){
		return NULL;
	}
	temporal = tas->inicio;
	tas->inicio = tas->inicio->siguiente;
	
	tas->tamanio--;
	return temporal;
	//free(temporal->nombre);
	//free(temporal->peso);
	//free(temporal->complex);
	//free(temporal->indice);
	//free(temporal); //tas->inicio->siguiente = NULL;
}
/*Imprime la estructura de cola*/
void imprimir_cola (Cola* tas){
	
	Elemento* actual = tas->inicio;
	Elemento* ultimo = tas->final;
	printf("Cola de Directorios nueva:\n");
	while(actual != NULL){
		printf("#%d: %s visitad: %d\n", actual->indice, actual->nombre, actual->visitado);

		actual = actual->siguiente;
	}
	printf("\n");
}
/*Encuentra el elemento, dado la posición en la ue se encuentre*/

Elemento* encontrar_cola(Cola* tas, int indice){
	Elemento* actual = tas->inicio;
	if (tas->tamanio == 0){
		return NULL;
	}
	while(actual->indice != indice){
		if ( actual->siguiente == NULL){
			return actual->siguiente;
		} else{		
			actual = actual->siguiente;
		}
	}
	return actual;
}