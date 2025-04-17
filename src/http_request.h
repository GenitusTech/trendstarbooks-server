#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#define BUFFER_SIZE 4096

struct SRequest
{
  char method[16];
  char path[256];
  char protocol[16];
  char *headers;
  char body[3200];
};
typedef struct SRequest HttpRequest;

void handle_client_request(int fd);
HttpRequest *get_request(int fd);
// HttpRequest *parse_request(const char *raw_request);
// void free_request(void);

#endif // HTTP_REQUEST_H_
