#include "http_request.h"
#include "http_response.h"
#include "utils/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *custom_allocation(const char *str, size_t size)
{
  char *data;

  data = (char *) malloc(sizeof(char) * size + 1);
  if (!data)
  {
    return (0);
  }
  (void) ft_memset(data, '\0', size + 1);
  (void) ft_strlcpy(data, str, size);
  return (data);
}

static size_t get_request_first_line(HttpRequest *req, const char *str)
{
  size_t pos;
  size_t prev_pos;
  char *line;
  unsigned short int occurence;

  pos = (size_t) ft_strpos(str, "\n");
  line = (char *) malloc(sizeof(char) * pos + 1);
  if (!line)
  {
    perror("error: malloc");
    return (0);
  }
  ft_memset(line, '\0', pos + 1);
  ft_strlcpy(line, str, pos);

  // Retreive Method & Path & Protocol
  pos = 0;
  occurence = 0;
  prev_pos = 0;
  while (line[pos] != '\0')
  {
    if (line[pos] == 32 || line[pos + 1] == '\0')
    {
      // Request - Method
      if (occurence == 0 && (pos - prev_pos) <= 8)
      {
        req->method = custom_allocation(str + prev_pos, (pos - prev_pos));
      }
      // Request - Path
      else if (occurence == 1 && (pos - prev_pos) <= 256)
      {
        req->path = custom_allocation(str + prev_pos, (pos - prev_pos));
      }
      // Request - Protocol
      else if (occurence == 2 && (pos - prev_pos) <= 12)
      {
        req->protocol = custom_allocation(str + prev_pos, (pos - prev_pos) + 1);
      }
      prev_pos = pos + 1;
      occurence += 1;
    }
    pos += 1;
  }
  free(line);
  return (pos + 1);
}

static size_t get_request_headers(HttpRequest *req, const char *str)
{
  size_t i;
  size_t pos;

  i = 0;
  pos = ft_strpos(str, "\n\n");
  req->header_count = 0;
  while (i < pos + 1 && str[i] != '\0')
  {
    if (str[i] == '\n')
    {
      req->header_count += 1;
    }
    i += 1;
  }
  req->headers = custom_allocation(str, pos);
  return (pos);
}

static size_t get_request_body(HttpRequest *req, const char *str)
{
  size_t i;

  i = 0;
  while (ft_isspace(str[i]) || str[i] == '\n')
  {
    i += 1;
  }
  req->body = custom_allocation(str + i, ft_strlen(str) - i);
  return (i);
}

HttpRequest *get_request(const char *raw_content)
{
  HttpRequest *req;
  char *duplicate_content;
  size_t pos_read;

  req = (HttpRequest *) malloc(sizeof(HttpRequest));
  if (!req)
  {
    return (0);
  }

  duplicate_content = ft_strdup(raw_content);
  if (!duplicate_content)
  {
    free_request(req);
    return (0);
  }

  // Initialize all fields to NULL
  req->method = NULL;
  req->path = NULL;
  req->protocol = NULL;
  req->headers = NULL;
  req->body = NULL;

  // Remove all '\r' characters
  ft_strdelchar(duplicate_content, '\r');

  pos_read = 0;
  pos_read += get_request_first_line(req, duplicate_content);
  pos_read += get_request_headers(req, duplicate_content + pos_read);
  pos_read += get_request_body(req, duplicate_content + pos_read);

  free(duplicate_content);
  return (req);
}

void parse_request(HttpRequest *req)
{
  (void) req;
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
