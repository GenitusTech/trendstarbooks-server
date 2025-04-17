#include "http_request.h"
#include "http_response.h"
#include "utils/libft.h"
#include <string.h>
// #include <netinet/in.h>
#include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

void handle_client_request(int fd)
{
  (void) fd;
  // HttpRequest *http_request;
  // HttpResponse *http_response;

  // char buffer[BUFFER_SIZE];
  // Get client request information as text
  // memset(buffer, '\0', BUFFER_SIZE);
  // if (read(fd, buffer, BUFFER_SIZE - 1) <= 0)
  // {
  //   perror("Read file descriptor failed");
  //   return;
  // }

  // // Instanciate HttpRequest
  // http_request = (HttpRequest *) malloc(sizeof(HttpRequest));
  // if (!http_request)
  // {
  //   perror("Could not allocate HttpRequest");
  //   return;
  // }

  // // Initialize all request fields to NULL
  // http_request->method = NULL;
  // http_request->path = NULL;
  // http_request->protocol = NULL;
  // http_request->headers = NULL;
  // http_request->body = NULL;

  // // Read

  // free(http_request);
}
