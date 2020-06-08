/* Ejercicio 5 del TP mutex interbloqueos */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* Variables Globales */
int t,total,total1,vueltas,s ;

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER; // inicializacion estatica del mutex
pthread_mutex_t mtx1=PTHREAD_MUTEX_INITIALIZER; // inicializacion estatica del mutex

void *HILO0(void *nro) {
int local1 , j, numero;

	numero= *(int*)nro;
	
	s=pthread_mutex_lock(&mtx);         //bloqueo del mutex
	if (s!=0){
		printf("ERROR; pthread_mutex() = %d\n", s);
	exit(-1);   }
	
	sleep(2);
	
	printf("Hilo= %d bloquea mutex\n", numero);
	
	s=pthread_mutex_lock(&mtx1);         //bloqueo del mutex
	if (s!=0){
		printf("ERROR; pthread_mutex() = %d\n", s);
	exit(-1);   }
	
	printf("Hilo= %d bloquea mutex1\n", numero);
	
	for(j=0;j< vueltas;j++){
		local1 = total;
		local1++;
		total=local1;   }
	
	for(j=0;j< vueltas;j++){
		local1 = total1;
		local1++;
		total1=local1;    }
	
	printf("Hola soy, el thread %d, total= %d\n", numero,total);
	printf("Hola soy, el thread %d, total1= %d\n", numero,total1);
	
	s=pthread_mutex_unlock(&mtx);      //desbloqueo del mutex
	if (s!=0){
		printf("ERROR; pthread_mutex() = %d\n", s);
	exit(-1);    }
	
	printf("Hilo= %d desbloquea mutex\n", numero);
	
	sleep(2);
	
	s=pthread_mutex_unlock(&mtx1);      //desbloqueo del mutex
	if (s!=0){
		printf("ERROR; pthread_mutex() = %d\n", s);
	exit(-1);    }
	
	printf("Hilo= %d desbloquea mutex1\n", numero);
	
	pthread_exit(NULL);
}

void *HILO1(void *nro) {
int local1 , j, numero;

	numero= *(int*)nro;
	
	s=pthread_mutex_lock(&mtx);         //bloqueo del mutex
	if (s!=0){
		printf("ERROR; pthread_mutex() = %d\n", s);
	exit(-1);   }
	
	printf("Hilo= %d bloquea mutex1\n", numero);
	
	s=pthread_mutex_lock(&mtx1);         //bloqueo del mutex
	if (s!=0){
		printf("ERROR; pthread_mutex() = %d\n", s);
	exit(-1);   }
	
	printf("Hilo= %d bloquea mutex\n", numero);
	
	for(j=0;j< vueltas;j++){
		local1 = total;   
		local1++;
		total=local1;    }
	
	for(j=0;j< vueltas;j++){
		local1 = total1;
		local1++;
		total1=local1;    }
	
	printf("Hola soy, el thread %d, total= %d\n", numero,total);
	printf("Hola soy, el thread %d, total1= %d\n", numero,total1);
	
	s=pthread_mutex_unlock(&mtx1);      //desbloqueo del mutex
	if (s!=0){
		printf("ERROR; pthread_mutex() = %d\n", s);
	exit(-1);    }
	
	printf("Hilo= %d desbloquea mutex1\n", numero);
	
	
	s=pthread_mutex_unlock(&mtx);      //desbloqueo del mutex
	if (s!=0){
		printf("ERROR; pthread_mutex() = %d\n", s);
	exit(-1);    }
	
	printf("Hilo= %d desbloquea mutex\n", numero);
	
	pthread_exit(NULL);
}

int main() {
pthread_t hilo[5];
int rc ;
int arre[5];

	total=0;
	vueltas=10000000;
	t=0;
	arre[t] = t;
	
	printf("El main ... creando el thread nro %d\n", t);
	
	rc = pthread_create(&hilo[t], NULL, HILO0 , (void *)&arre[t]  ); 
	if (rc){
		printf("ERROR; pthread_create() = %d\n", rc);
		exit(-1);}
	
	t=1;
	printf("El main ... creando el thread nro %d\n", t);
	arre[t] = t;
	
	rc = pthread_create(&hilo[t], NULL, HILO1 , (void *)&arre[t]  ); 
	if (rc){
		printf("ERROR; pthread_create() = %d\n", rc);
		exit(-1);}
	
	pthread_join(hilo[0],NULL);
	pthread_join(hilo[1],NULL);
	
	printf("Total= %d\n",total);
	
	pthread_exit(NULL);

}

// El objetivo del programa es sumar en cada variable global (total y total1) hasta
// obtener como resultado 2 millones en cada una.

// El problema está en que cada hilo comienza bloqueando un mutex diferente, por lo que
// al querer bloquear el segundo mutex en ambos casos, ya se encuentra bloqueado
// por el otro hilo y ambos hilos quedan bloqueados en espera de que se desbloquee
// alguno de los mutex, cosa que no sucede.

// La solucion es que ambos hilos bloqueen los mutex en el mismo orden para evitar
// inconvenientes.