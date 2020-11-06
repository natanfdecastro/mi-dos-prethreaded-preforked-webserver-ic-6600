# Mi DoS. Prethread - preforked Webserver. 
WebServer that uses entirely the HTTP/1.1 protocol, implements the prethread and preforked technique for managing high demand service.  

Also creates a web client that seek to defeat webservers by leaving them unable to provide service to another client.

# Sections

## Pre-thread WebServer

A web server which implements the technique called prethread. This technique consists of previously creating several threads of execution of the method that serves the requests. These threads are created using the __Unix pthreads__ library. It must receive as a parameter the number of __threads N__ that is should pre-create, the web server will listen on the standard HTTP port, and it will have N possible threads to service the request, each request will be served by the first thread that is available. In which there are no more available show a message error, indicating that the number of clients that can be catered.

> Executing the Pre-thread WebServer

``` $ prethread-webserver -n <cantidad-hilos> -w <path-www-root> -p <port>```

## Pre-forked WebServer 

A web server which implements the technique called pre-forked. This technique consists of previously creating several processes of the method that serves requests. These processes are created using the system call Unix standard. It receive as a parameter the number of processes N that must be pre-created, the webserver listen on the standard HTTP port, and have N possible processes to attend the request, each request will be attended by the first process that is available. In case there are no more available it will show an error message, indicating that the number of clients that they can be cared for.

> Executing the Pre-thread WebServer

```$ preforked-webserver -n <cantidad-hilos> -w <path-www-root> -p <port>```

## HTTPClient 

An HTTP client which allows downloading a resource. For it uses the curl library in the Python language.

> Executing the HTTPClient

```$ httpclient -u <url-de-recurso-a-obtener>```

## HTTPClient C Language

An HTTP client which allows downloading a resource. For it uses the curl library in the C language.

## StressCMD

An application that receives an executable as a parameter (In addition to the executable parameters). Then creates the amount of threads specified by the client, in order to launch a Deny attack of service. The main objective of joining the HTTPClient and the StressCMD is to saturate the
webservers until they are able to serve another client. In the Python language.

> Executing the StressCMD

```$ stress -n <thread-number> httpclient <parameters-from-client>```

## CGI Injector (exploit)

This client will be in charge of injecting new code to the previously created server.

## 

# Documentación

## 1. Introducción
  La siguiente tarea tiene como propósito el desarrollo de un WebServer que usa el protocolo HTTP 1.1 e implementa la técnica de prethread y preforked para manejar alta demanda del servicio. Dicha aplicación debe tener un client web que 

## 2. Ambiente de desarrollo

Se utilizaron las siguientes herramientas para la implementación de la tarea;
* Sistema Operativo GNU/Linux Ubuntu 20.04
* Editor de texto Sublime Text versión 3.2.2
* GNU Compiler Collection (GCC) versión 7.5.0
* Mozilla Firefox versión 82

## 3. Estructuras de datos usadas y funciones
* initSocket: Inicializa el socket con el puerto para la conexión.
* thread_handler: Se encarga de manejar hilos según sea necesario, hace uso de mutex para solucionar problemas asociados a la condición de carrera. Es una función que se implementa por referencia y no valor.
* listen_to_connections: Pone a escuchar el socket inicializado, con las conexiones por parámetro.
* create_threads: crea los los hilos y lo inserta en el pool de hilos pthreads.
* initiate_threads: Se encarga de inicializar los threads con el número de threads deseados.
* create_socket: Se encarga de crear los sockets en el stream y lo retorna.
* bind_socket: Asigna el puerto correspondiente al server. 


## 4. Instrucciones para ejecutar el programa
* ```$ make```
* ```$ preforked-webserver -n <cantidad-hilos> -w <path-www-root> -p <port>```

## 5. Actividades realizadas por estudiante
| Fecha |  Inicio |   Fin   |      Duración     |                        Actividad                       |
|:-----:|:-------:|:-------:|:-----------------:|:------------------------------------------------------:|
| 26/10 | 3:20 PM | 4:40 PM | 1 hora 20 minutos | Lectura de especificación y estructuración de proyecto |
| 28/10 | 5:00 PM | 7:00 PM |      2 horas      |                Investigación de p-thread               |
| 31/10 | 6:30 PM | 8:30 PM |      2 horas      |                   Escritura de código                  |
| 02/11 | 7:00 PM | 9:00 PM |      2 horas      |                 Correcciones al código                 |
| 03/11 | 4:00 PM | 5:00 PM |       1 hora      |                 Correcciones al código                 |
| 05/11 | 6:00 PM | 8:00 PM |      2 horas      |            Documentación y arreglos finales            |

## 6. Autoevaluación
Se encontró con problemas para mostrar archivos de resources, el cual mostraba solo los caracteres y no el recursos como tal. También se encontraron problemas con la asignación de puertos y la liberación de estos una vez que se ejecutaban para la escucha. 

* WebServer: 40 % / 40 %
* Implementación de Protocolos: 0% / 10 %
* http-Client: 5% / 5 %
* http-Client en C: 5% / 5 %
* Stress-Client: 0 % / 10 %
* CGI Injector (Exploit): 0 % / 10 %
* Documentación utilizando MD: 20 % / 20 %

## 7. Lecciones Aprendidas
El proyecto es de complejidad medio-fácil si se piensa simple, sin complicarlo de más, ya que se cometió el error de pensar que algunas funciones salían en menos tiempo, pero mostraban errores confusos que alargaron su implementación. Tener en cuentra el proceso y teoría que se requiere para la implementación de este tipo de técnicas como lo son pthreads y preforked. 

## 8. Bibliografía

Jacob Sorber. (2018, 10 diciembre). How to create and join threads in C (pthreads). [Vídeo]. YouTube. https://www.youtube.com/watch?v=uA8X5zNOGw8&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM 
