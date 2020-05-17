/*
* Ejercicio 4 del TP de Cola de mensajes
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <mqueue.h>

#define MENSAJE "DATA PARA OTROS PROCESOS"
#define MQ_PATH "/MQ_TD3"  // El nombre de la cola de mensajes debe empezar con "/"

int main() {
   
   int err, leido;
   char buff[1024];   
   mqd_t mqd; 
   struct mq_attr attr, attr_rcv;
  
   // Se fijan algunos parametros de la cola de mensajes antes de crearla
   attr.mq_msgsize = sizeof(buff);
   attr.mq_maxmsg = 5;
   
   // Se crea cola de mensajes
   mqd = mq_open(MQ_PATH, O_RDONLY | O_NONBLOCK, 0666, &attr); 
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
        // Se lee de cola de mensajes
        leido = 0;
        leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, 0);
        if (( leido < 0 )){
            printf ("error en mq_receive()");
            exit(-1); }

        printf("Mensaje leido: %s\n", buff);
        sleep(1);
    }
   // Se cierra cola de mensajes
   err = mq_close(mqd);
   if (( err < 0 )){
      printf ("error en mq_close()");
      exit(-1);   }

      printf("Cola de mensajes cerrada (%d)\n", err);
   
   // Se elimina cola de mensajes
   err = mq_unlink(MQ_PATH);
   if(err == -1){
      printf ("error en mq_unlink()");
      exit(-1);   }

      printf("Cola de mensajes eliminada (%d)\n", err);
      
   exit(0);
}

// Al ejecutar el programa, este inicia normalmente, pero al leer los 5 mensajes
// almacenados en la cola, se queda sin mensajes para leer y da error de lectura,
// esto se debe a que no se puede quedar en estado bloqueado.

// Al ejecutar ambos programas al mismo tiempo, lo que sucede es que siempre hay
// un espacio para escribir y por lo tanto uno para leer, por lo que ambos
// programas se ejecutan sin interrupción.