/*
 * Ejercicio 7 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i=0;

    do{
        pid = fork();		
        printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d, i vale: %d\n", getpid(), getppid(), pid, i);
        i++;
    }while (i<3);

    
	// Ejecute pstree en otra consola	
	sleep(5); 

	exit(0);
    
}

// Es creado un solo hijo, pero éste tiene a su vez mas hijos.
// Si se cuenta como hijo cada vez que devuelve 0, entonces se crean 7 hijos.
// El valor de i se repite en algunas ocasiones.