/*
 * Ejercicio 3 del TP FIFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MENSAJE "HOLA PROCESO HIJO"
#define FIFO_PATH "/tmp/MI_FIFO"

main(){

	int err, fifo_d;
	char buff[80];
	int leido;

	unlink(FIFO_PATH);    //si la FIFO existe la borro                   

	// FIFO puede ser leida, escrita y ejecutada por: 
	err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
	// Comprueba creacion
    if(err == -1) {
		write (0, "\nError al crear FIFO, la FIFO ya existe", sizeof("\nError al crear FIFO, la FIFO ya existe")); 
	}else {
		write (0, "\nFIFO creado correctamente\n", sizeof("\nFIFO creado correctamente\n")); 
	}

    // Crea hijo
	switch (fork()){ 
		
		case -1:		
			write (0, "\nError al crear hijo", sizeof("\nError al crear hijo")); 
			return -1;
		break;			

        // HIJO
		case 0:

			write (0, "\nEntrando proceso HIJO", sizeof("\nEntrando proceso HIJO"));

			sleep(5);

			/*  
			//El Hijo que debe hacer con la FIFO ?
			*/	

            // ----------------------- AGREGADO POR MI ------------------------

            
            fifo_d = open(FIFO_PATH, O_RDONLY, 0); // O_NONBLOCK //Funcionamiento normal
			//fifo_d = open(FIFO_PATH, O_RDONLY | O_NONBLOCK, 0); // O_NONBLOCK no bloqueante
			if(fifo_d == -1){
				write (0, "\nHIJO: Error al abrir FIFO ", sizeof("\nHIJO: Error al abrir FIFO "));
				return -1;
			}else {
				write (0, "\nHIJO: FIFO abierto correctamente", sizeof("\nHIJO: FIFO abierto correctamente"));
			}
			
			// Se lee FIFO
			leido = read(fifo_d, buff, sizeof(buff));	
			if(leido == -1){
				write (0, "\nHIJO: Error al leer en FIFO", sizeof("\nHIJO: Error al leer en FIFO"));
			}else {
				write (0, "\nHIJO: Leido del FIFO: ", sizeof("\nHIJO: Leido del FIFO: "));
				write (0, buff, leido-1); 
				write (0, "\n", sizeof("\n")); 
			}
			close(fifo_d); 


            // ----------------------- AGREGADO POR MI ------------------------


			write (0, "\nSaliendo proceso HIJO\n", sizeof("\nSaliendo proceso HIJO\n")); 
			exit(0);	
		break;	
		
        // Padre
		default:
			write (0, "\nEntrando proceso PADRE", sizeof("\nEntrando proceso PADRE")); 
			
            // Abre fifo en modo escritura
			fifo_d = open(FIFO_PATH, O_WRONLY, 0);
			if(fifo_d == -1){
				write (0, "\nPADRE: Error al abrir FIFO ", sizeof("\nPADRE: Error al abrir FIFO "));
				return -1;
			}else {
				write (0, "\nPADRE: FIFO abierto correctamente", sizeof("\nPADRE: FIFO abierto correctamente"));
			}

			// Se escribe en el FIFO
			err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
			if(err == -1) {
				write (0, "\nPADRE: Error al escribir en FIFO", sizeof("\nPADRE: Error al escribir en FIFO"));
			} else {
				write (0, "\nPADRE: Escritos MENSAJE en FIFO", sizeof("\nPADRE: Escritos MENSAJE en FIFO"));
			}

			close(fifo_d); 
			
			wait(NULL);	
			write (0, "\nSaliendo proceso PADRE\n", sizeof("\nSaliendo proceso PADRE\n")); 

		break;	
	}
	
	//Eliminaci�n FIFO
	//if (unlink(FIFO_PATH) < 0) {
 	//	printf("\nNo se puede borrar FIFO.\n");  }			

	exit(0);

}

// En este caso el que se queda bloqueado es el padre, esperando que alguien
// abra la FIFO en modo lectura, por lo que el programa nunca termina.

// La solucion es copiar el segmento de codigo del hijo del programa fifo01.