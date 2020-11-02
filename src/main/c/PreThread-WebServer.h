#ifndef _PRETHREADWEBSERVER_H
#define _PRETHREADWEBSERVER_H

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAX_CONEXIONES 100

//VARIABLES
int starter_socket;
int current_thread;
//New Socket
int new_socket;
char buffer[256];

//FUNCIONES DEL PTHREAD
pthread_cond_t condition;
pthread_cond_t accept_condition;
pthread_mutex_t mutex;
pthread_mutex_t number_mutex;

//----- FUNCIONES PARA HILOS -----//
void initiate_threads(int max); 	//Se crean los hilos y se asignan para las conexiones
void *thread_handler(); 			//
void create_threads(int max);	//Se crean los hilos
void listen_to_connections();	//Se pone a escuchar conexiones el server
//----- FUNCIONES PARA HILOS -----//

#endif
