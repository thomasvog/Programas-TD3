/*
 * Ejercicio 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){
	
	printf ("Mi pid es %d y el pid de papa es %d\n", getpid(),getppid());

	exit(0);   
	}

	// PID: Es el número de identificación del proceso que se ejecuta
	// El PID del padre es menor al del hijo ya que el padre fue ejecutado antes que el hijo