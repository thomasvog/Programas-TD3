/*
 * Ejercicios 3 y 4 de TP Seniales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*
void manejador_senial(int a){
   
}
*/
int main ()
{

   //signal(SIGKILL, SIG_IGN);
   signal(SIGTSTP, SIG_IGN);  //Ctrl + z
   
   printf("Proceso PID = %d\n", getpid());   
   
   while(1);
   
   exit(0);
}

// Lo que ocurre es que al ejecutar kill, el proceso termina, ya que la señal SIGKILL
// no puede ser ignorada.

// Al querer terminar la señal SIGTSTP utilizando Ctrl + Z, se puede observar que
// la misma si puede ser ignorada.
