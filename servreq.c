/*

  SERVREQ.C
  =========
  (c) Copyright Paul Griffiths 1999
  Email: mail@paulgriffiths.net

  Implementation of function to service requests.

*/

#include <stdio.h>
#include <errno.h>

#include "helper.h"
#include "reqhead.h"
#include "resphead.h"
#include "resource.h"

extern int first_header;

/*  Service an HTTP request  */
int Service_Request(int conn) {

    struct ReqInfo reqinfo;
    int resource = 0;

    InitReqInfo(&reqinfo);
    
	// magic number..
	first_header = 1;
    /*  Get HTTP request  */
    if (Get_Request(conn, &reqinfo) < 0) {
		Error_Warn("Failed to parse request");
		return -1;
	}
	
	printf("method=%d type=%d\n", reqinfo.method, reqinfo.type);
	printf("referer=%s\n", reqinfo.referer);
	printf("useragent=%s\n", reqinfo.useragent);
	printf("resource=%s\n", reqinfo.resource);
	printf("\n");

	if (reqinfo.method == 2)
		Error_Warn("Unsupported method");
    
    /*  Check whether resource exists, whether we have permission
	to access it, and update status code accordingly.          */
    if (reqinfo.status == 200 && (resource = Check_Resource(&reqinfo)) < 0) {
		if (errno == EACCES)
			reqinfo.status = 401;
		else
			reqinfo.status = 404;
	}

    /*  Output HTTP response headers if we have a full request  */
    if (reqinfo.type == FULL)
		Output_HTTP_Headers(conn, &reqinfo);

    /*  Service the HTTP request  */
    if (reqinfo.status == 200) {
		if (Return_Resource(conn, resource, &reqinfo))
		    Error_Quit("Something wrong returning resource.");
	} else
		Return_Error_Msg(conn, &reqinfo);

	printf("status=%d\n", reqinfo.status);

    if (resource > 0 && close(resource) < 0)
	    Error_Quit("Error closing resource.");
    FreeReqInfo(&reqinfo);

    return 0;
}
