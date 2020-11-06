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
