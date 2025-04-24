#include "http_request.h"
#include "handle_method.h"
#include "handle_path.h"
#include "libft.h"
#include "log.h"
#include <stdio.h>
#include <string.h>

size_t fetch_method(const char *content, HttpRequest *req)
{
  // Break point (or first delimiter index)
  size_t bkpt;
  char *buffer;

  bkpt = (size_t) ft_strchrpos(content, ' ');
  if (bkpt <= 0)
  {
    error_log("no point break found");
    return (0);
  }
  buffer = (char *) malloc(sizeof(char) * (bkpt + 1));
  if (!buffer)
  {
    error_log("could not allocate buffer for method");
    return (0);
  }
  (void) ft_strlcpy(buffer, content, bkpt);
  if (string_to_method((const char *) buffer) <= 0)
  {
    free(buffer);
    error_log("request method is not allowed");
    return (0);
  }
  req->method = buffer;
  return (bkpt + 1);
}

size_t fetch_path(const char *content, HttpRequest *req)
{
  // Break point (or first delimiter index)
  size_t bkpt;
  char *buffer;

  bkpt = (size_t) ft_strchrpos(content, ' ');
  if (bkpt <= 0)
  {
    error_log("no point break found");
    return (0);
  }
  if (bkpt > PATH_LENGTH)
  {
    error_log("url path is too long");
    return (0);
  }
  buffer = (char *) malloc(sizeof(char) * (bkpt + 1));
  if (!buffer)
  {
    error_log("could not allocate buffer for path");
    return (0);
  }
  (void) ft_strlcpy(buffer, content, bkpt);
  if (!sanitize_url_path(buffer))
  {
    free(buffer);
    error_log("url path is not invalid");
    return (0);
  }
  req->path = buffer;
  return (bkpt + 1);
}

size_t fetch_protocol(const char *content, HttpRequest *req)
{
  // Break point (or first delimiter index)
  size_t bkpt;
  char *buffer;

  bkpt = (size_t) (ft_strstr(content, "\r\n") - content);
  if (bkpt <= 0)
  {
    error_log("no point break found");
    return (0);
  }
  buffer = (char *) malloc(sizeof(char) * (bkpt + 1));
  if (!buffer)
  {
    error_log("could not allocate buffer for protocol");
    return (0);
  }
  (void) ft_strlcpy(buffer, content, bkpt);
  if (!buffer)
  {
    free(buffer);
    error_log("protocol is not invalid");
    return (0);
  }
  req->protocol = buffer;
  return (bkpt + 2);
}

size_t fetch_headers(const char *content, HttpRequest *req)
{
  // Break point (or first delimiter index)
  size_t bkpt;
  char *buffer;

  bkpt = (size_t) (ft_strstr(content, "\r\n\r\n") - content);
  if (bkpt <= 0)
  {
    error_log("no point break found");
    return (0);
  }
  buffer = (char *) malloc(sizeof(char) * (bkpt + 1));
  if (!buffer)
  {
    error_log("could not allocate buffer for headers");
    return (0);
  }
  (void) ft_strlcpy(buffer, content, bkpt);
  req->headers = buffer;
  return (bkpt + 4);
}

size_t fetch_body(const char *content, HttpRequest *req)
{
  // Break point (or first delimiter index)
  size_t bkpt;
  char *buffer;

  if (ft_strstr(content, "\r\n"))
  {
    return (0);
  }
  bkpt = ft_strlen(content);
  if (bkpt <= 0)
  {
    return (0);
  }
  buffer = (char *) malloc(sizeof(char) * (bkpt + 1));
  if (!buffer)
  {
    error_log("could not allocate buffer for body");
    return (0);
  }
  (void) ft_strlcpy(buffer, content, bkpt);
  req->body = buffer;
  return (bkpt);
}

HttpRequest *get_request(const char *content)
{
  HttpRequest *req;
  size_t content_len;
  size_t pos;

  content_len = ft_strlen(content);
  req = (HttpRequest *) malloc(sizeof(HttpRequest));
  if (!req)
  {
    error_log("could not allocate http_request");
    return ((void *) 0);
  }
  req->method = NULL;
  req->path = NULL;
  req->protocol = NULL;
  req->headers = NULL;
  req->body = NULL;

  pos = 0;

  pos += fetch_method(content, req);
  if (req->method == NULL)
  {
    return (req);
  }

  pos += fetch_path(content + pos, req);
  if (req->path == NULL)
  {
    return (req);
  }

  pos += fetch_protocol(content + pos, req);
  if (req->protocol == NULL)
  {
    return (req);
  }

  pos += fetch_headers(content + pos, req);
  pos += fetch_body(content + pos, req);

  if (content_len != pos) {
    error_log("an error occured");
  }

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
