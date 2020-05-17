/*
 * Ejercicio 1 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (){

	int ipc[2], proc;
	int leido;
	char buff[80];

	//Padre crea la tubería
	pipe(ipc);

	// Muestra los descriptores de lectura y escritura, ipc[0] -> lectura
	printf ("ipc[0] = %d ipc[1] = %d \n ", ipc[0], ipc[1]);	

	// Padre crea hijo que hereda los descriptores de tubería
	proc = fork();


	// HIJO
	if (proc == 0 ){ 
		
		// Se cierra el lado de escritura del hijo
		close(ipc[1]);
		
		// Lee la tubería, en leido se guarda la cantidad de bytes leidos
		// Como la tubería no tiene nada, el hijo se bloquea hasta que alguien 
		// escriba algo en la tubería		
		leido = read(ipc[0], buff, sizeof(buff));
		if(leido < 1){
			write (0, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
		}else {
			
			// Escribir en consola
			write (0, "\nLeido de la tuberia: ", sizeof("\nLeido de la tuberia: "));
			write (0, buff, leido-1);
			printf(", por el proceso hijo, pid %d \n", getpid());
		}
		// Termina el hijo
		exit(0);
	
	}
	// Se cierra el lado de lectura del padre
	close(ipc[0]);
	
	printf("\nIngrese una cadena de caracteres por consola:\n");
	// Se lee por consola
	leido = read(0, buff,  sizeof(buff));

	// Se escribe en la tuberia
	write(ipc[1], buff, leido);
	
	// Se cierra el lado de escritura. Se destruye la tuberia.
	close(ipc[1]);
	// Espera que el hijo termine
	wait(NULL);	
	// Escribe en pantalla lo que escribió el padre
	write (0, "\nEscrito en la tuberia: ", sizeof("\nEscrito en la tuberia: "));
	write (0, buff, leido-1);
	printf(", por el proceso padre, pid %d \n", getpid());

	exit(0);

}
