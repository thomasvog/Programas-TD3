/*
 * Ejercicio 9 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i;

	pid = fork();		
	

     switch (pid){

        case -1:
            printf ("Error ha ocurrido\n");
            break;

        case 0: 
            printf ("Soy el proceso hijo, mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);
            sleep (30);
            break;

        default: 
            printf ("Soy el proceso padre, mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);

     }
	// Ejecute pstree en otra consola	
	 
    wait(NULL);
	exit(0);

}