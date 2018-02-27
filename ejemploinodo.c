#include <stdlib.h>	//constantes EXIT_SUCCESS y EXIT_FAILURE
#include <stdio.h>	//función printf
#include <time.h>	//funciones localtime, asctime
#include <sys/stat.h> 
#ifdef CONFIG_BLOCK	//no funciona en todas las versiones de unix
	#include <linux/fs.h>	//función bdget
#endif
#include <pwd.h>	//función getpwuid
#include <grp.h>	//función getgrgid

int main(int argc, char* argv[]){
	struct stat nodo;
	int tmp;
	
	if(argc > 1)
		tmp = stat(argv[1], &nodo);
	else{
		printf("Debe dar un nombre de archivo como parametro");
		return EXIT_SUCCESS;	//el programa termina, tal y como debe, dada la entrada
	}
	
	if(tmp != 0){
		perror("error obteniendo inode\n");
		return EXIT_FAILURE;	//el programa no puede continuar a pesar de que el usuario hizo todo bien
	}
	
	//A continuación se accede a todos los campos de struct stat definidos en el estándar
	//nota: x->y es igual a (*x).y
	#ifdef CONFIG_BLOCK
		printf("En el dispositivo: %s\n", bdget(nodo.st_dev)->bd_disk->disk_name);	//la estructura devuelta puede darles otra información (como la lista de solicitudes de acceso); investiguen más si les interesa
	#else
		printf("En el dispositivo numero: %d\n", nodo.st_dev);
	#endif
	printf("Numero de inode: %d\n", nodo.st_ino);
	printf("Modo: 0x%X\n", nodo.st_mode);	//lo correcto es matemáticamente extraer cada bit, pero esto es solo un ejemplo
	printf("Numero de links: %d\n", nodo.st_nlink);
	printf("Pertenece a: %s\n", getpwuid(nodo.st_uid)->pw_name);	//la estructura devuelta por getpwuid puede darles otra información (como nombre y apellido); investiguen más si les interesa
	printf("Del grupo: %s\n", getgrgid(nodo.st_gid)->gr_name);	//la estructura devuelta por getgrgid puede darles otra información (como número de miembros); investiguen más si les interesa
	#ifdef CONFIG_BLOCK
		printf("El dispositivo especial (si aplica) es: %s\n", bdget(nodo.st_rdev)->bd_disk->disk_name);
	#else
		printf("El numero de dispositivo especial (si aplica) es: %d\n", nodo.st_rdev);
	#endif
	printf("El archivo ocupa %d bytes\n", nodo.st_size);
	printf("Fue accedido por ultima vez el %s\n", asctime(localtime(&nodo.st_atime)));	//localtime devuelve un struct del cual pueden extraer solo el mes o solo el minuto, etc. Investiguen más si les interesa
	printf("Fue modificdo por ultima vez el %s\n", asctime(localtime(&nodo.st_mtime)));
	printf("Esta informacion fue cambiada por ultima vez el %s\n", asctime(localtime(&nodo.st_ctime)));
	
	return EXIT_SUCCESS;	//el programa ha termnado exitosamente
}