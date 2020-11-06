THREADHEADERS = PreThread-WebServer.h Socket.h
THREADFILES = PreThread-WebServer.c Socket.c

LIBRARYS = -pthread

CLIENTHEADERS = HttpClient.h
CLIENTFILES = HttpClient.c

EXE = Prethread-WebServer
EXE2 = HttpClient
all: 
	gcc $(LIBRARYS) $(THREADHEADERS) $(THREADFILES) -o $(EXE)
	gcc $(CLIENTHEADERS) $(CLIENTFILES) -o $(EXE2)
	
run_default_pre-thread:
	./$(EXE) -n 10 -w /resources -p 8080 

clean:
	rm $(EXE)
	rm $(EXE2)

