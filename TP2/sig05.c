/*
 * Ejercicio 8 de TP Seniales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h> 


int estado;
int status;

void thesignal(int a){
	
    estado = wait(&status);

}

int main ()
{
	
	pid_t pid1;
	
//	signal (SIGCHLD, thesignal);
	
	pid1 = fork();
	
	switch (pid1){
		
		case -1:   // No pudo crear el proceso
			printf ("Error. No se crea proceso hijo");
			break;
			
		case 0:   //proceso hijo
			printf ("PID hijo: %d\n", getpid());
			sleep(2);
			exit(0);
			break;

		default:  //proceso padre
			//printf ("PID padre: %d\n", getppid());
			
			signal (SIGCHLD, thesignal);
			sleep(10);
			printf ("El resultado de wait es: %d. Y el valor de status es: %d", estado, status);
		
		}
	
	
	
	
	
   exit(0);
}
