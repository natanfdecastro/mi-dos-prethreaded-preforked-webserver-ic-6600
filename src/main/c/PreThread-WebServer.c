#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include "Socket.h"
#include <unistd.h>
#include <string.h>
#include "PreThread-WebServer.h"

#define BUFFSIZE 4096

char extentions[17][5] = {
	"gif",
	"jpg",
	"jpeg",
	"png",
	"mp3",
	"mp4",
	"avi",
	"ico",
	"zip",
	"gz",
	"tar",
	"txt",
	"json",
	"doc",
	"docx",
	"htm",
	"html"
};

char mimes[17][100] = {
	"image/gif",
	"image/jpeg",
	"image/jpeg",
	"image/png",
	"audio/mpeg",
	"audio/mpeg",
	"video/x-msvideo",
	"image/vnd.microsoft.icon",
	"application/zip",
	"application/gzip",
	"application/x-tar",
	"text/plain",
	"application/json",
	"application/msword",
	"application/vnd.openxmlformats-officedocument.wordprocessingml.document",
	"text/html",
	"text/html"
};

// Método que da un "header" de respuesta al cliente.
void headers(int client, int length, const char *fileType) {
	char response_header[1000];              // Donde se almacenará el encabezado de la respuesta.

	sprintf(response_header, "HTTP/1.1 200 OK\r\n%sAccept-Ranges: bytes\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n",
			"Server: PreThreadWebServer\r\n", length, fileType);       // Se especifica la línea del servidor, el largo del archivo
			                                        // y el tipo de archivo.
	fprintf(stdout, "Encabezado de la respuesta:\n%s\n", response_header);

	send(client, response_header, strlen(response_header), 0);      // Se le envía el mensaje al cliente.
}

//Encarga de manejar los hilos
void *thread_handler(){
	int new_socket_aux;
	int i;
	int j;
  char *message = (char *)calloc(5000, sizeof(char));
	char *file_name = (char *)calloc(5000, sizeof(char));
	char *ext = (char *)calloc(50, sizeof(char));
	char *mime = (char *)calloc(150, sizeof(char));
  char actualpath[256];
  ssize_t bytes_read;

		pthread_mutex_lock(&mutex);
		while (new_socket == -1){
			pthread_cond_wait(&condition, &mutex);
		}

		new_socket_aux = new_socket;
		new_socket = -1;
		pthread_mutex_unlock(&mutex);

		if ( new_socket_aux > 0){

			recv(new_socket_aux , message , 2000 , 0); // Lee lo que el cliente le manda
	    printf("------------------------------------------------------\n");


      printf("REQUEST: %s\n", message);
      fflush(stdout);

			i = 0;
			j = 0;

			if (message[i] == 71) {
				i += 5;
				while(message[i] != 32){
					file_name[j] = message[i];
					j++;
					i++;
				}
			}

			i = 0;
			j = 0;

			if(message[i] == 71){
				i+=5;
				while(message[i] != 32){
					if (message[i] == 46) {
						while(message[i+1] != 32){
							ext[j] = message[i];
							j++;
							i++;
						}
					}
					i++;
				}
			}
			i = 0;
			while(i < 18){
				if(strcmp(ext,extentions[i]) == 0){
					mime = mimes[i];
					break;
				}
				i++;
			}

/*

			else if () {

			}

			else if () {

			}

			else{

			}
		*/

      // validity check
			printf("the file is: %s\n",file_name);
      if (realpath(file_name, actualpath) == NULL) {
          printf("ERROR(bad path): %s\n", buffer);
          close(new_socket_aux);
          return NULL;
      }

      // read file and send its content to client
      FILE *fp = fopen(actualpath, "r");
      if (fp == NULL) {
          printf("ERROR(open): %s\n", buffer);
          close(new_socket_aux);
          return NULL;
      }

      printf("Waiting for server process...\n");
      sleep(1);

   // read file contents and send them to client
   // note this is a fine example program, but rather insecure
   // a real programm would probably limit the client to certain files
			struct stat st;
			stat(actualpath, &st);
			int response_length = st.st_size;
			headers(new_socket_aux, response_length, mime);
			int response = open(actualpath,O_RDONLY);
			sendfile(new_socket_aux,response,0, response_length);

			close(new_socket_aux);
			printf("Conexion finalizada correctamente.\n");
			pthread_mutex_lock(&number_mutex);
			current_thread--;
			pthread_mutex_unlock(&number_mutex);
			pthread_cond_signal(&accept_condition);
		}
}

//FUNCION QUE PONE EL SERVER A ESCUCHAR CONEXIONES
void listen_to_connections(){
	if(listen(starter_socket, MAX_CONEXIONES) == -1){
		printf("Se ha producido un error al intentar escuchar conexiones.\n");
	}
	printf("\nListo para recibir conexiones\n");
}

//FUNCION QUE CREA LOS THREADS
void create_threads(int max){
	pthread_t threads[max];
	for (int i = 0; i < max; i++){
		//Crea los threads
		int err = pthread_create(&(threads[i]), NULL, thread_handler, NULL);
		printf("\n Se ha creado el hilo %d \n", i+1);
		//Verifica si el thread se ha creado correctamente
		if (err){
			printf("Error al iniciar un hilo.\n");
		}
	}
}

//FUNCION QUE INICIA LOS THREADS
void initiate_threads(int number_of_threads){
	//Nueva conexion
	int new_connection;
	new_socket = -1;
	//Crea los hilos
	create_threads(number_of_threads);
	//Se pone a escuchar conexiones
	listen_to_connections();
	while(1){
		//Acepta la nueva conexion o el nuevo cliente
		new_connection = accept(starter_socket, NULL, NULL);
		printf("Se ha conectado un nuevo cliente\n");
		if(new_connection<0){
			printf("Error al conectar el cliente\n");
		}
		else{

				// Mutexes: Routines that deal with synchrnization (mutual exclusion)
				// https://computing.llnl.gov/tutorials/pthreads/

				pthread_mutex_lock(&mutex);

				new_socket = new_connection;
	     	pthread_mutex_unlock(&mutex);
	     	pthread_cond_broadcast(&condition);
	     	pthread_mutex_lock(&number_mutex); // Mutex: Rutinas que trabajan con
	     	current_thread++;

				printf("------------------------------------------------------\n");
	     	printf("El numero de hilos es: %d \n", number_of_threads);
	     	printf("El numero de actuales es: %d \n", current_thread);

	     	if (number_of_threads < current_thread){ //si se llenan los hilos espera

					printf("Espere mientras sea su turno\n");
	        pthread_cond_wait(&accept_condition, &number_mutex);

	     	}

				pthread_mutex_unlock(&number_mutex);

	     }
    }
}

//MAIN
int main(int argc, char **argv)
{
	//Se toma el numero de hilos y el puerto como parametros
	int thread_count;
	int port;
  char *resources_path = (char *)calloc(5000, sizeof(char));
	int option;
	//While para determinar los paramentros que ingresara el usuario
	while((option = getopt(argc, argv, "n:w:p:")) != -1){
		switch(option){
			case 'p':
				port = atoi(optarg);
				break;
      case 'w':
    		resources_path = optarg;
    		break;
			case 'n':
				thread_count = atoi(optarg);
				break;
		}
	}

	printf("-------------------------------------------------");
	printf("\n");
	printf(">>> NUMBER OF THREADS: %d",thread_count);
	printf("\n");
	printf(">>> PORT NUMBER: %d", port);
	printf("\n");
	printf("-------------------------------------------------\n");

	//Se va crear el socket
	starter_socket = create_socket();
	printf("\nServer initiated succesfully\n");
	//Se le asigna el puerto correspondiente al server
	bindSocket(starter_socket, port);
	printf("-------------------------------------------------\n");
	//Llama a la funcion de iniciar los hilos
	initiate_threads(thread_count);


	return 0;
}
