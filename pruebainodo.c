#include <stdlib.h>	//constantes EXIT_SUCCESS y EXIT_FAILURE
#include <stdio.h>	//función printf
#include <sys/stat.h> 
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(){

	/*
	Se abre el inodo del padre para chequear si es file o directory

	S_ISREG(m)
	is it a regular file?

	S_ISDIR(m)

	directory?

	Si es directory, se abre el directorio y se almacenan los nombres en una cola
	De la cola se crea un proceso por cada directorio, si existe alguno
	Cada proceso realiza un BFS, se comunica con el padre por un pipe
	si llega a un directorio hoja o a un archivo
	El padre lee el pipe con los strings y retorna el archivo
	Funcion de palindromo
	*/

	struct stat nodo;
	int tmp;

	char *archivo="/home/sandra/Documents/"; //cambien este path por uno de un directorio y uno de un archivo para que vean la diferencia
	tmp = stat(archivo,&nodo);

	if(tmp != 0){
		perror("error obteniendo inode\n");
		return EXIT_FAILURE;	//el programa no puede continuar a pesar de que el usuario hizo todo bien
	}

	mode_t modo = nodo.st_mode;
	
	char buf[100];
	int fd[2];//pipe
	pipe(fd);
	
	if(S_ISDIR(modo)==1){
		printf("Es un directorio.\n");

		pid_t pid_hijo;
		pid_hijo=fork();
		FILE *archivo_pipe;
		int status;
		int count=0;
		if(pid_hijo==0){			
			DIR *directorio = opendir(archivo);
			struct dirent *dp; //Para el directorio
			char *nombre_archivo;
			close(fd[0]);
        	dup2(fd[1], STDIN_FILENO);
			while(((dp=readdir(directorio))!=NULL)){
				if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")){}
				else{
					nombre_archivo = dp->d_name;
					//Lo escribe al pipe
					write(fd[1],nombre_archivo,100);
				}
			}
			closedir(directorio);
			close(fd[1]);
		}else{
			//el padre espera y luego imprime el output
			waitpid(pid_hijo, &status,0);
			close(fd[1]);
				while(read(fd[0],buf,100)>0){
					printf("%s\n", buf);
					count++;
				}
			close(fd[0]);
			printf("%d\n", count);
		}
	}else if(S_ISREG(modo)==1){
		printf("Es un archivo regular.\n");
	}
	close(fd[0]);
	close(fd[1]);

}