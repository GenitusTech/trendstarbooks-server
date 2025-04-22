#ifndef HTTP_RESPONSE_H_
#define HTTP_RESPONSE_H_

#include "http_request.h"
#include <stdio.h>

// HTTP Status Code Definitions
#define HTTP_CONTINUE              100
#define HTTP_SWITCHING_PROTOCOLS   101
#define HTTP_OK                    200
#define HTTP_CREATED               201
#define HTTP_ACCEPTED              202
#define HTTP_NO_CONTENT            204
#define HTTP_MOVED_PERMANENTLY     301
#define HTTP_FOUND                 302
#define HTTP_NOT_MODIFIED          304
#define HTTP_BAD_REQUEST           400
#define HTTP_UNAUTHORIZED          401
#define HTTP_FORBIDDEN             403
#define HTTP_NOT_FOUND             404
#define HTTP_METHOD_NOT_ALLOWED    405
#define HTTP_INTERNAL_SERVER_ERROR 500
#define HTTP_NOT_IMPLEMENTED       501
#define HTTP_BAD_GATEWAY           502
#define HTTP_SERVICE_UNAVAILABLE   503

struct SResponse
{
  unsigned short int status_code;
  char *body;
};
typedef struct SResponse HttpResponse;

HttpResponse *get_response(HttpRequest *req);
void free_response(HttpResponse *res);
void handle_response(int fd, HttpResponse *res);
void send_response(int fd,
                   int status_code,
                   const char *content_type,
                   const char *body);

#endif // HTTP_RESPONSE_H_
