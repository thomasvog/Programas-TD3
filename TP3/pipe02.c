/*
 * Ejercicio 2 de TP PIPE
 * 
*/

//Carga de librerias
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//Definición de variables
#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80


// Inicia main
int main (){

    // Inicia variables
	int ipc[2], proc;
	int leido, success;
	char buff[BUFF_SIZE] = {0};

    // Si la tubería da error, 
	if (pipe(ipc) == -1)
		exit(-1);
    // Padre crea al hijo
	switch (fork()){ 
		
		case 0:
            // Hijo cierra el descriptor de escritura
			//close(ipc[1]);
            // Copia lo que hay en DATA a buff
			strncpy(buff, DATA, sizeof(DATA));
            // Escribe en la tubería lo que hay en buff 
			write(ipc[1], buff, sizeof(DATA));
			exit(0);
			
            // PADRE
		default:
			printf("Leyendo tuberia... \n");
            // Lee de tubería
			leido = read(ipc[0], buff, sizeof(buff));

            // Si lee bien, escribe en consola
			if(leido < 1){
				write (0, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
			}else {

				write (0, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
				write (0, buff, leido-1);
				printf(", por el proceso padre, pid %d \n", getpid());
			}	

            // Espera que el hijo termine	
			wait(NULL);	
			
			exit(0);		
	}
}

// El problema es que se cierra el descriptor de escritura del hijo
// antes de que el mismo pueda escribir en la tubería.
// Para solucionarlo solo se debe comentar la linea de cierre de descriptor