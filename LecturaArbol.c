#include <stdlib.h>	//constantes EXIT_SUCCESS y EXIT_FAILURE
#include <stdio.h>	//función printf
#include <sys/stat.h> 
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "Cola.h"
#include "Elemento.h"

void sigHandler(int signum){
	if(signum==SIGUSR1){
		
	}
}

Elemento* lecturaArbol(char *archivo){

	struct stat nodo;
	int tmp;
	tmp = stat(archivo,&nodo);

	if(tmp != 0){
		perror("Error obteniendo inode.\n");
		return EXIT_FAILURE;	//el programa no puede continuar a pesar de que el usuario hizo todo bien
	}

	mode_t modo = nodo.st_mode;
	
	char buf[100];
	int fd[2];//pipe
	pipe(fd);
	Elemento* padre_definitivo;
	if( (padre_definitivo = (Elemento *)malloc (sizeof(Elemento))) == NULL){
		return NULL;
	}
	padre_definitivo->nombre=archivo;

	if(S_ISDIR(modo)==1){
		Cola* hijos;
		if( (hijos = (Cola*) malloc(sizeof(Cola))) == NULL){
			return NULL;
		}

		inicializacion_cola(hijos);
		padre_definitivo->hijos=hijos;

		pid_t pid_hijo;
		pid_hijo=fork();
		FILE *archivo_pipe;
		int status;
		char stringcopy[100];
		if(pid_hijo==0){
			printf("El proceso es el %d\n", getpid() );			
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

					strcpy(stringcopy, archivo);
					//printf("HOllaa\n");

					strcat(stringcopy, nombre_archivo);
					//printf("El sring q tal %s\n", stringcopy);
					write(fd[1],stringcopy,100);
				}
			}
			closedir(directorio);
			close(fd[1]);
			//Le envia una señal al padre para que lo mate
			exit(0);
			//waitpid(getppid(),&status,0);
		}else{
			//pause();
			//signal(SIGUSR1,sigHandler);
			waitpid(pid_hijo, &status,0);
			//kill(pid_hijo,SIGQUIT);
			close(fd[1]);
			int i=0;
			while(read(fd[0],buf,100)>0){
				//Agrega los nodos a la cola
				encolar(hijos,buf,i);
				i++;
			}
			close(fd[0]);
		}

	}else if(S_ISREG(modo)==1){

		//exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	return padre_definitivo;
}

int main(){
	// Elemento* padre = lecturaArbol("/");
	// printf("Cola inicial.\n");
	// imprimir_cola(padre->hijos);
	Elemento* padre_1 = lecturaArbol("/home/sandra/Documents/Operativos/");

	imprimir_cola(padre_1->hijos);
	Elemento * aux = padre_1->hijos->inicio;

	while(aux != NULL) {
		printf("Padre %s\n",aux->nombre);
		Elemento* hijo = lecturaArbol(aux->nombre);
		printf("inicio");
		Cola* nietos;
		if( (nietos = (Cola*) malloc(sizeof(Cola))) == NULL){
			return -1;
		}
		inicializacion_cola(nietos);
		
		encolar(nietos, hijo->nombre, nietos->tamanio);
		printf("antes %s\n", aux->nombre);
		aux = aux->siguiente;
		printf("despues %s\n", aux->nombre);
		imprimir_cola(aux->hijos);
	}
	// printf("La de otro directorio\n");
	// imprimir_cola(padre_1->hijos);
	// Elemento* padre_2 = lecturaArbol("/home/sandra/Documents/Orga/");
	// imprimir_cola(padre_2->hijos);
	//printf("%d\n", getpid());

	return 0;
}