/*
 * Ejercicio 5a del TP de Cola de mensajes
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <signal.h>

#define MENSAJE "DATA PARA PROCESO"
#define MQ_PATH "/MQ_TD3" // El nombre de la cola de mensajes debe empezar con "/"

   int err, leido;
   char buff[1024];   
   mqd_t mqd; 
   struct mq_attr attr, attr_rcv;


void lee_mensaje(int a){ 

        leido = 0;
        leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, 0);
        if (( leido < 0 )){
            printf ("error en mq_receive()");
            exit(-1); }

        printf("Mensaje leido: %s\n", buff);
        sleep(1);
}






int main() {
   

    
    signal(SIGINT, lee_mensaje);  

    printf("Soy el proceso: %d \n ",getpid());

   // Se fijan algunos parametros de la cola de mensajes antes de crearla
   attr.mq_msgsize = sizeof(buff);
   attr.mq_maxmsg = 5;
   
   // Se crea cola de mensajes
   mqd = mq_open(MQ_PATH, O_RDONLY, 0666, &attr); 
   if (mqd < 0) {
      printf ("error en mq_open()");   
      exit(-1); }
      
   printf("Cola de mensajes creada\n"); 
   

   
   // Se leen parametros de la cola de mensajes
   if (mq_getattr(mqd, &attr_rcv) == -1){
      printf ("error en mq_getattr()");
      exit(-1); }
      
   printf("Nro max. de mensajes en cola de mensajes: %ld\n",attr_rcv.mq_maxmsg);
   printf("Longitud max. de mensaje: %ld\n",attr_rcv.mq_msgsize);
   printf("Nros de mensajes pendientes en cola de mensajes: %ld\n",attr_rcv.mq_curmsgs);

    while(1){

    }


      
   exit(0);
}