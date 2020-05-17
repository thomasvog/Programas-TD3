/*
 * Ejercicio 4 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){
	
	write (0, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
	exit(-1);
}

int main (){

	int ipc[2], proc;
	int leido, success;
	char buff[BUFF_SIZE] = {0};

	signal(SIGPIPE, pipe_sign_handler);
	// Crea tubería
	if (pipe(ipc) == -1)
		exit(-1);
	// Cierra descriptor de lectura de Padre (Linea a comentar para que ande bien)
	close(ipc[0]);
	// Crea hijo
	switch (fork()){ 
		// HIJO
		case 0:
        // Cierra escritura de tubería
			close(ipc[1]);
			printf("Leyendo tuberia... \n");
            // Lee de tubería
			leido = read(ipc[0], buff, sizeof(buff));
			if(leido < 1){
				write (0, "\nError al leer tuberia\n", sizeof("\nError al leer tuberia\n"));
			}else {
                // Escribe en consola lo que leyó de tubería
				write (0, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
				write (0, buff, leido-1);
				printf(", por el proceso hijo, pid %d \n", getpid());
			}
			exit(0);
			
		default:
            // Padre copia lo que hay en DATA a buff
			strncpy(buff, DATA, sizeof(DATA));
            // Escribe en tubería
			write(ipc[1], buff, sizeof(DATA));
            // Espera que el hijo termine
			wait(NULL);		
			
			exit(0);		
	}
}

// El Problema en este ejercicio es que al principio, antes de crear al hijo
// el padre cierra el descriptor de lectura, por lo tanto, al crear al hijo
// este ultimo nace con el descriptor de lectura cerrado, por lo tanto no puede
// leer de la tubería.
// Para solucionar esto, solo se debe comentar la linea en la que el padre
// cierra la lectura de la tubería.