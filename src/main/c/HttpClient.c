#include "HttpClient.h"
#include <unistd.h>

//Funcion que conecta con el server
int initSocket(int port){

	sock = socket(AF_INET , SOCK_STREAM , 0);
	server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

	//Si da menor que 0 signific que hubo un error al conectarse con el server
  if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
  {

      printf("Error al conectar con el server.\n");

  }
	return sock;
}

int main(int argc, char *argv[]){

	int puerto = 8080;
	char *url = (char *)calloc(5000, sizeof(char));
	int option;
	//While para determinar los paramentros que ingresara el usuario
	while((option = getopt(argc,argv,"u:")) != -1){
		switch(option){
			case 'u':
				url = optarg;
				break;
		}
	}

	//Inicia el socket de comunicacion con el servidor
	sock = initSocket(puerto);
	int n;

	//Escribe o manda el mensaje (la prioridad) al server
	n = write(sock,url,sizeof(url));
	if (n < 0){
		printf("ERROR writing to socket");
	}
	//Si dio menor que 0, significa que hubo un error con la escritura

	//Lee el mensaje que le devolvio el server
	bzero(buffer,256);
	int k;
	k = read(sock,buffer,255);
	//Si da menor a 0 significa que hubo un error leyendo del socket
	if (k < 0){
		printf("\nERROR leyendo del socket\n");
	}else{
		printf("------------------------------------------------------\n");
		printf("\nSu respuesta fue: %s \n",buffer);
		printf("------------------------------------------------------\n");
		//Si la prioridad que devolvio el server es 0, se hara un sleep de 8 segundos para representar la entrega rapida
	}

	if(sock <0){
		return 0;
	}

	return 0;
}
