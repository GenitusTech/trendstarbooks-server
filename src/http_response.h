#ifndef HTTP_RESPONSE_
#define HTTP_RESPONSE_

struct SResponse
{
  char *method;
  char *path;
  char *protocol;
  char *headers;
  char *body;
};
typedef struct SResponse HttpResponse;

void free_response(void);

#endif // HTTP_RESPONSE_
