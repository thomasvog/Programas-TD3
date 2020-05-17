/*
 * Ejercicios 5 y 6 de TP Seniales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int flag;

void sig_user1(int a){
	
   write (STDOUT_FILENO,"\n Me rehuso a terminar\n", sizeof("\n Me rehuso a terminar\n"));

}

int main ()
{

   //signal(SIGKILL, sig_user1); // Termina el proceso al enviar un kill desde otra consola.
   signal(SIGUSR1, sig_user1);  // Al ejecutar kill -SIGUSR1 en la consola se muestra la oración
								// "Me rehuso a terminar" sin terminar el proceso.
   
   printf("Proceso PID = %d\n", getpid());   
   
   while(1);
   
   exit(0);
}
