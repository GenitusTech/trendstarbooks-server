#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#include <stddef.h>

#define BUFFER_SIZE 4096

struct SRequest
{
  char *method;
  char *path;
  char *protocol;
  char *headers;
  char *body;
};
typedef struct SRequest HttpRequest;

HttpRequest *get_request(const char *content);
void free_request(HttpRequest *req);
void handle_request(HttpRequest *req);

size_t fetch_method(const char *content, HttpRequest *req);
size_t fetch_path(const char *content, HttpRequest *req);
size_t fetch_protocol(const char *content, HttpRequest *req);
size_t fetch_headers(const char *content, HttpRequest *req);
size_t fetch_body(const char *content, HttpRequest *req);

#endif // HTTP_REQUEST_H_
