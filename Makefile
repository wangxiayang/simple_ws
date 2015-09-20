webserv: webserv.o helper.o servreq.o reqhead.o resphead.o resource.o
	gcc -o $@ $^ -Wall -lpthread

webserv.o: webserv.c
	gcc -o $@ $^ -c -Wall

helper.o: helper.c
	gcc -o $@ $^ -c -Wall

servreq.o: servreq.c
	gcc -o $@ $^ -c -Wall

reqhead.o: reqhead.c
	gcc -o $@ $^ -c -Wall

resphead.o: resphead.c
	gcc -o $@ $^ -c -Wall

resource.o: resource.c
	gcc -o $@ $^ -c -Wall -D CONTENT_PATH=\"$(shell pwd)/web\"

clean:
	rm -f *.o webserv
