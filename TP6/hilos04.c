/*  
 * Ejercicio 4 del TP Hilos
 *   
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int suma=0;

void *hilo1 (void * nro)
{
   int numero, temp;
   
   numero = *(int*)nro;
   temp = suma;
   //usleep(300);
   pthread_yield();
   temp = temp + 1 ;
   suma = temp;
   
   printf("Ejecutando hilo %d\n", numero);
   pthread_exit(NULL);
}

int main()
{
   pthread_t hilo[100];
   int rc, t, arre[100];

   for(t=0; t< 100 ; t++){
      printf("Creando el hilo %d\n", t);
      arre[t] = t;
      rc = pthread_create(&hilo[t], NULL, hilo1 , (void *)(&arre[t]) );
      if (rc){
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);
      }
   }

   int i;
   for (i=0; i<100;i++) {
       while(pthread_join(hilo[i], NULL));
   }
  
   printf("Valor de globlal = %d\n", suma);
      
   exit(0);
}

// El objetivo del programa es crear 100 hilos en los que por cada hilo
// creado se sumara 1 a la variable suma.

// Al ejecutar el programa varias veces se observa que el valor de la variable
// global "suma" es siempre igual a 100.

// Al descomentar la linea 18 y ejecutar varias veces el programa, se observa
// que el valor de "suma" es distinto en cada ejecución. Esto se debe a que
// la demora incorporada por usleep produce que se creen y ejecuten hilos mientras
// se está esperando para avanzar, por lo que los hilos que se ejecutaron durante el
// usleep no son considerados en la suma y por ello el resultado distinto al finalizar
// el programa.

// Al comentar 18 y descomentar 19 tambien se observa que el resultado de "suma"
// es distinto en cada ejecución.