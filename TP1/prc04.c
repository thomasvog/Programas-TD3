/*
 * Ejercicio 4 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i;

	pid = fork();		
	printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);

     switch (pid){

        case -1:
            printf ("Error ha ocurrido\n");
            break;

        case 0: 
            printf ("Proceso hijo\n");
            break;

        default: 
            printf ("Proceso padre\n");

     }
	// Ejecute pstree en otra consola	
	sleep(5); 

	exit(0);

}