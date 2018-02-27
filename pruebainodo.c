#include <stdlib.h>	//constantes EXIT_SUCCESS y EXIT_FAILURE
#include <stdio.h>	//función printf
#include <time.h>	//funciones localtime, asctime
#include <sys/stat.h> 
#ifdef CONFIG_BLOCK	//no funciona en todas las versiones de unix
	#include <linux/fs.h>	//función bdget
#endif
#include <pwd.h>	//función getpwuid
#include <grp.h>	//función getgrgid

int main(){

	/*
	Se abre el inodo del padre para chequear si es file o directory
	Si es directory, se abre el directorio y se almacenan los nombres en una cola
	De la cola se crea un proceso por cada directorio, si existe alguno
	Cada proceso realiza un BFS, se comunica con el padre por un pipe
	si llega a un directorio hoja o a un archivo
	El padre lee el pipe con los strings y retorna el archivo
	Funcion de palindromo
	*/

	struct stat nodo;
	int tmp;

	char *archivo="~/Documents/";
	tmp = stat(archivo,&nodo);

	if(tmp != 0){
		perror("error obteniendo inode\n");
		return EXIT_FAILURE;	//el programa no puede continuar a pesar de que el usuario hizo todo bien
	}

	mode_t modo = nodo.st_mode;
	

}