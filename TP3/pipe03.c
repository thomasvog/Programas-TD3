/*
 * Ejercicio 3 de TP PIPE
*/

// Inicia librerias
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

// Define variables
#define FRASE_A "INFORMACION IMPORTANTE"
#define FRASE_B "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

// Inicia manejador
void pipe_sign_handler(int a){
	
	write (0, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
}

// Inicia main
int main (){

    // Declara variables
	int ipc[2], proc;
    //int ipc2[2];
	int leido, success;
	char buff[BUFF_SIZE] = {0};

    // Declara señal con su manejador
	signal(SIGPIPE, pipe_sign_handler);
	
    // Crea tubería
	pipe(ipc);
    //pipe(ipc2);

    // Crea hijos
	switch (fork()){ 
		
        // HIJO 1
		case 0:
        // Cierra descriptor de lectura
		close(ipc[0]);	
        // Copia contenido de fraseA a buff	
		strncpy(buff, FRASE_A, sizeof(FRASE_A)); 
        // Escribe en la tubería
		write(ipc[1], buff, sizeof(FRASE_A));
		exit(0);
		break;
		
		default:
        // Crea otro son
		switch (fork()){ 
			// HIJO 2	
			case 0:
                // Cierra descriptor de lectura            
				close(ipc[0]);
                    //close(ipc2[0]);	
                // Copia contenido de B a buff				
				strncpy(buff, FRASE_B, sizeof(FRASE_B)); 
                // Escribe en la tubería
				write(ipc[1], buff,    sizeof(FRASE_B));
                    //write(ipc2[1], buff,    sizeof(FRASE_B));
				exit(0);		
			break;
			default:
            // Padre cierra descriptor de escritura
				close(ipc[1]);
				int i;
                // Bucle, 2 veces
				for(i=0; i<2; i++){
                    // Lee el contenido de tubería
					leido = read(ipc[0], buff, sizeof(buff));
                    // Caso de error
					if(leido < 1){
						write (0, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
					}else {
                        // Escribe en consola lo que leyó de la tubería
						write (0, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
						write (0, buff, leido-1);
						printf(", por el proceso padre, pid %d \n", getpid());
					}
				}
				// Padre cierra descriptor de lectura y mata tubería
				close(ipc[0]);
                // Padre espera que sus children terminen	
				wait(NULL);	
				wait(NULL);					
				exit(0);
			break;
		}
	}	
}

// El problema en este ejercicio es que el padre si bien puede leer
// la info que le pasa cada hijo, no sabe cual es de quien.
// Por lo tanto la solución a este inconveniente es crear una segunda tubería.
// Gracias a esto cada hijo tendra su propia tubería para comunicarse con papi.