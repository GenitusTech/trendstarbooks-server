#include "http_request.h"
#include "libft.h"
#include "log.h"

HttpRequest *get_request(const char *content)
{
  HttpRequest *req;

  req = (HttpRequest *) malloc(sizeof(HttpRequest));
  if (!req)
  {
    error_log("could not allocate http_request");
    return (0);
  }
  req->method = NULL;
  req->path = NULL;
  req->protocol = NULL;
  req->headers = NULL;
  req->body = NULL;

  (void) content;
  return (req);
}

void free_request(HttpRequest *req)
{
  if (req)
  {
    if (req->method)
    {
      free(req->method);
      req->method = NULL;
    }
    if (req->path)
    {
      free(req->path);
      req->path = NULL;
    }
    if (req->protocol)
    {
      free(req->protocol);
      req->protocol = NULL;
    }
    if (req->headers)
    {
      free(req->headers);
      req->headers = NULL;
    }
    if (req->body)
    {
      free(req->body);
      req->body = NULL;
    }
    free(req);
  }
}

void handle_request(HttpRequest *req)
{
  (void) req;
}
