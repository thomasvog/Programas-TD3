/*
 * Ejercicio 16 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main(void) {
	
	int err;
	
	//err = execl	("/bin/ls", "ls", "-l", (char *)NULL);
	err = execl("/otro_directorio/ls", "ls", "-l", (char *)NULL);
	
	if (err == -1)
		printf("Este printf se ejecuta en caso de error. Por que?\n");
			
	exit(0);

}

// Por consola se observa "Este printf se ejecuta en caso de error. Por que?"
// La salida a cambiado porque el directorio "otro_directorio" es inexistente.
