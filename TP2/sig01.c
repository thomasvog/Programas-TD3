/*
 * Ejercicios 1 y 2 de TP Señales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


int main ()
{

   sleep(5);
   
   exit(5);
}

// Si, el valor que proporciona echo es 5 si termina de forma normal, pero
// si termina de forma abrupta, el mismo proporciona el valor 130.
