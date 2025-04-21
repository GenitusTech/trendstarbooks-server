#ifndef HTTP_RESPONSE_H_
#define HTTP_RESPONSE_H_

#include "http_request.h"

struct SResponse
{
  unsigned short int status_code;
  char *body;
};
typedef struct SResponse HttpResponse;

void get_response(HttpRequest *req, HttpResponse *res);
void free_response(HttpResponse *res);

#endif // HTTP_RESPONSE_H_
