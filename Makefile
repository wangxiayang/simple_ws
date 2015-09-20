webserv: webserv.o helper.o servreq.o reqhead.o resphead.o resource.o
	gcc -o webserv webserv.o helper.o servreq.o reqhead.o resphead.o resource.o -Wall -lpthread

webserv.o: webserv.c helper.h servreq.h
	gcc -o webserv.o webserv.c -c -pedantic -Wall

helper.o: helper.c helper.h
	gcc -o helper.o helper.c -c -pedantic -Wall

servreq.o: servreq.c servreq.h helper.h
	gcc -o servreq.o servreq.c -c -pedantic -Wall

reqhead.o: reqhead.c reqhead.h servreq.h helper.h
	gcc -o reqhead.o reqhead.c -c -pedantic -Wall

resphead.o: resphead.c resphead.h helper.h
	gcc -o resphead.o resphead.c -c -pedantic -Wall

resource.o: resource.c resource.h
	gcc -o resource.o resource.c -c -pedantic -Wall

clean:
	rm -f *.o webserv
