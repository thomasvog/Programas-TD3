/* Ejercicio 2 del TP mutex 
 acceso a variables compartidas sin uso mutex */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


/* Variables Globales */
int t,total, vueltas ;

void *HILO0(void *nro) {

int local1 , j, numero;

	numero= *(int*)nro;
	
	for(j=0;j< vueltas;j++){
		local1 = total;
		local1++;
		total=local1;
	}
	
	printf("Hola soy, el thread %d, total= %d\n", numero,total);
	pthread_exit(NULL);
}

int main() {

pthread_t hilo[5];
int rc ;
int arre[5];

	total=0;
	vueltas=100000;
	
	for(t=0; t< 5 ; t++){
		printf("El main ... creando el thread nro %d\n", t);
		arre[t] = t;
		
		rc = pthread_create(&hilo[t], NULL, HILO0 , (void *)&arre[t]  ); 
		if (rc){
			printf("ERROR; pthread_create() = %d\n", rc);
			exit(-1);    }
	}
	
	pthread_join(hilo[0],NULL);
	pthread_join(hilo[1],NULL);
	pthread_join(hilo[2],NULL);
	pthread_join(hilo[3],NULL);
	pthread_join(hilo[4],NULL);
	
	printf("Total= %d\n",total);
	
	pthread_exit(NULL);
}

// El objetivo del programa es sumar 100000 veces 1 en la variable total cada vez que se
// ejecuta un hilo.

// El valor de la variable global total deberia ser 500000 al finalizar.

// Solo algunas veces la variable global total resulta 500000. Lo que sucede es que
// al no producirse la suma de manera atomica, otro hilo puede interrumpir al actual,
// produciendo error en el resultado de la variable total.