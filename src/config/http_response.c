#include "http_response.h"
#include "http_request.h"
#include "libft.h"
#include "log.h"

// Status code to text mapping
const char *http_status_text[] = {
    [100] = "Continue",
    [101] = "Switching Protocols",
    [200] = "OK",
    [201] = "Created",
    [202] = "Accepted",
    [204] = "No Content",
    [301] = "Moved Permanently",
    [302] = "Found",
    [304] = "Not Modified",
    [400] = "Bad Request",
    [401] = "Unauthorized",
    [403] = "Forbidden",
    [404] = "Not Found",
    [405] = "Method Not Allowed",
    [500] = "Internal Server Error",
    [501] = "Not Implemented",
    [502] = "Bad Gateway",
    [503] = "Service Unavailable",
};

HttpResponse *get_response(HttpRequest *req)
{
  HttpResponse *res;

  res = (HttpResponse *) malloc(sizeof(HttpResponse));
  if (!res)
  {
    error_log("could not allocate http_response");
    return (0);
  }
  res->body = NULL;
  res->status_code = 0;

  (void) req;
  return (res);
}

void free_response(HttpResponse *res)
{
  if (res)
  {
    if (res->body)
    {
      free(res->body);
    }
    res->status_code = 0;
    free(res);
  }
}

void handle_response(int fd, HttpResponse *res)
{
  (void) res;
  send_response(fd, HTTP_OK, "application/json", "{\"message\":\"OK\"}");
}

void send_response(int client_fd,
                   int status_code,
                   const char *content_type,
                   const char *body)
{
  size_t header_length;
  size_t body_length;

  char header[BUFFER_SIZE];

  ft_bzero(header, BUFFER_SIZE);

  header_length = ft_strlen(header);
  body_length = ft_strlen(body);

  snprintf(header,
           sizeof(header),
           "HTTP/1.1 %d %s\r\n"
           "Server: Genitus Technologies Server\r\n"
           "Content-Type: %s\r\n"
           "Content-Length: %lu\r\n"
           "Connection: close\r\n"
           "\r\n",
           status_code,
           http_status_text[status_code],
           content_type,
           body_length);

  (void) write(client_fd, header, header_length);

  if (body && body_length)
  {
    (void) write(client_fd, body, body_length);
  }
}
