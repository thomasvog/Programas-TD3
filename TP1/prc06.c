/*
 * Ejercicio 6 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main ()
{
	int x = 100;
	
	printf("Soy el proceso: %d \n",getpid());
	
	switch (fork())
	{
		case -1:   // No pudo crear el proceso
			printf ("Error. No se crea proceso hijo");
			break;

		case 0:   //proceso hijo
			printf ("Soy el proceso hijo, pid: %d , x = %d, su ubicación es: %d\n", getpid(), --x, (&x));
			break;

		default:  //proceso padre
			printf ("Soy el proceso padre, pid: %d , x = %d, su ubicación es: %d\n", getpid(), ++x, (&x));
	}
    printf ("\nLa var x esta en: %d\n", (&x));
    exit(0);

}

// La variable x se encuentra en una ubicación relativa, por lo que en ambos procesos se encuentra en la misma ubicación.