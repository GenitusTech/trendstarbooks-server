#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#define BUFFER_SIZE 4096

struct SRequest
{
  char *method;
  char *path;
  char *protocol;
  char *headers;
  char *body;
  unsigned int header_count;
};
typedef struct SRequest HttpRequest;

HttpRequest *get_request(const char *raw_content);
void parse_request(HttpRequest *http_request);
void free_request(HttpRequest *req);

#endif // HTTP_REQUEST_H_
