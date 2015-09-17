/*

  WEBSERV.C
  =========
  (c) Copyright Paul Griffiths 1999
  Email: mail@paulgriffiths.net

  A simple web server

*/

#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <sys/wait.h>         /*  for waitpid()             */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helper.h"
#include "servreq.h"

#define SERVER_PORT 8080

int main(int argc, char *argv[]) {

    int listener;
    struct sockaddr_in servaddr;
    
    /*  Create socket  */
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		Error_Quit("Couldn't create listening socket.");

    /*  Populate socket address structure  */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// INADDR_ANY is defined in the system
    servaddr.sin_port = htons(SERVER_PORT);

    /*  Assign socket address to socket  */ 
	// TODO: why need bind?
    if (bind(listener, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		Error_Quit("Couldn't bind listening socket.");

    /*  Make socket a listening socket  */
	// TODO: ??
    if (listen(listener, LISTENQ) < 0)
		Error_Quit("Call to listen failed.");

    /*  Loop infinitely to accept and service connections  */
    while (1) {
		int conn;
		/*  Wait for connection  */
		if ((conn = accept(listener, NULL, NULL)) < 0)
		    Error_Quit("Error calling accept()");
		printf("\33[0;32mNew Connection..\33[m\n");

		Service_Request(conn);

		/*  Close connected socket and exit  */
		if (close(conn) < 0)
			Error_Quit("Error closing connection socket.");
		printf("\33[0;34mConnection closed.\33[m\n");
    }

    return EXIT_FAILURE;    /*  We shouldn't get here  */
}
