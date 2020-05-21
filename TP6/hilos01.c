/*  
 * Ejercicio 1 del TP Hilos
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *hola(void * nro) {
  
   sleep(2);
   printf("Hola, soy el hilo %d\n", * (int*) nro);
   pthread_exit(NULL);
   //exit(0); // Este exit termina todo el proceso en este momento

}

int main() {

    pthread_t hilo[1];
    int rc, t;

    t = 0;
     
    printf("Main creando el hilo nro %d\n", t);
        // Crea hilo (puntero hilo, atributo, funcion, argumento)
    rc = pthread_create(&hilo[0], NULL, hola , (void *)(&t)  );
     
    if (rc != 0){
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);        
         };
  
   printf("Espera a que termine hilo\n");

   pthread_join(hilo[0],NULL);

   printf("Termina hilo main\n");

   pthread_exit(NULL);
   
   return 0;
}
