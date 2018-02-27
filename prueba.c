#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

void sigHandler(int signum){
	if(signum==SIGUSR1){
		printf("Se le envio una señal al padre\n");
	}else{
		printf("No, chamita\n");
	}
}

int main(){
	
	pid_t pid_padre, pid_hijo;
	//SIGUSR1 es el numero 10
	pid_padre=getpid();
	//execvp o execlp
	pid_hijo=fork();
	int status;
	if(pid_hijo==0){
		pid_hijo=getpid();
		//Hace ls
		execlp("/bin/ls","ls","/home/prenuevos/Documents/SV/",NULL);
		//kill(pid_padre,SIGUSR1); Esto nunca llega a pasar

	}else{
		//pause();
		waitpid(pid_hijo, &status,0);
		printf("Padre %d\n", pid_padre);
		//wait(pid_hijo,&status,NULL);
	}
	signal(SIGUSR1,sigHandler);
	kill(pid_padre,SIGUSR1);
	
	return 0;
}