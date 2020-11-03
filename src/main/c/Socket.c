#include "Socket.h"

//Funcion que crea el servidor (Crea el socket)
int create_socket(){
	//Busca el id del socket
	int socket = socket(AF_INET , SOCK_STREAM , 0);
	//Si da -1, no se pudo crear el socket
	if (id_Socket == -1){
	    printf("Error al crear el socket");
	}
	printf("Socket creado con exito\n");
	//Retorna el id del socket
	return socket;
}

//Funcion que le asigna el puerto correspondiente al server
//Recibe como parametros el id del socket y el puerto
void bindSocket(int socket, int puerto){
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(puerto);
	//Bind
	if( bind(socket,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
	    printf("\nError durante el bind\n");
	}else{
		printf("\nEscuchando en el puerto -> %i\n",puerto);
	}
}
