#include "http_request.h"
#include "http_response.h"
#include "utils/libft.h"
#include <string.h>
// #include <netinet/in.h>
#include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

static char *custom_allocation(const char *str, size_t size)
{
  char *data;

  data = (char *) malloc(sizeof(char) * size + 1);
  (void) ft_memset(data, '\0', size + 1);
  (void) ft_strlcpy(data, str, size + 1);
  return (data);
}

static void get_request_first_line(HttpRequest *req, const char *str)
{
  unsigned int pos_start;
  unsigned int pos_end;
  unsigned int i;

  pos_start = 0;
  pos_end = 0;
  i = 0;
  while (str[pos_end] != '\0')
  {
    if (str[pos_end] == 32 || str[pos_end + 1] == '\0')
    {
      // Request: METHOD
      if (i == 0 && (pos_end - pos_start) <= 8)
      {
        req->method = custom_allocation(str + pos_start, (pos_end - pos_start));
      }
      // Request: PATH
      else if (i == 1 && (pos_end - pos_start) <= 256)
      {
        req->path = custom_allocation(str + pos_start, (pos_end - pos_start));
      }
      // Request: PROTOCOL
      else if (i == 2 && (pos_end - pos_start) <= 12)
      {
        req->protocol = custom_allocation(str + pos_start, (pos_end - pos_start) + 1);
      }
      pos_start = pos_end + 1;
      i += 1;
    }
    pos_end += 1;
  }
}

HttpRequest *get_client_request(const char *raw_content)
{
  HttpRequest *http_request;
  char *duplicate_content;
  char *content_line;
  unsigned int i;
  size_t len;

  http_request = (HttpRequest *) malloc(sizeof(HttpRequest));
  if (!http_request)
  {
    return (0);
  }

  // Initialize all fields to NULL
  http_request->method = NULL;
  http_request->path = NULL;
  http_request->protocol = NULL;
  http_request->headers = NULL;
  http_request->body = NULL;

  duplicate_content = ft_strdup(raw_content);
  if (!duplicate_content)
  {
    free_request(http_request);
    return (0);
  }

  content_line = strtok(duplicate_content, "\n");
  if (!content_line)
  {
    free(duplicate_content);
    free_request(http_request);
    return (0);
  }

  i = 0;
  len = 0;
  while (content_line != NULL)
  {
    ft_strdelchar(content_line, '\r');
    if (i == 0)
    {
      get_request_first_line(http_request, content_line);
      len += ft_strlen(content_line);
      i += 1;
      continue;
    }
    // Headers & Body

    // printf("%s\n", content_line);
    len += ft_strlen(content_line);
    // Get next content
    content_line = strtok(NULL, "\n");
    i += 1;
  }

  free(duplicate_content);
  return (http_request);
}

void free_request(HttpRequest *req)
{
  if (req->method)
  {
    free(req->method);
  }
  if (req->path)
  {
    free(req->path);
  }
  if (req->protocol)
  {
    free(req->protocol);
  }
  if (req->headers)
  {
    free(req->headers);
  }
  if (req->body)
  {
    free(req->body);
  }
  free(req);
}
