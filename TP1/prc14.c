/*
 * Ejercicio 14 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main ()
{
	
	fprintf (stdout, "Texto stdout\n");
	fprintf (stderr, "Texto stderr\n");

}

// Por consola se observa unicamente el flujo stdout
// El contenido del archivo err.txt es "Texto stderr"
// El operador 2> sirve para almacenar los errores, si existen, en el archivo especificado
