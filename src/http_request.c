#include "http_request.h"
#include <inttypes.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

void handle_request(int fd)
{
  char buffer[BUFFER_SIZE] = {0};
  ssize_t bytes_read;

  // Read request
  bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
  if (bytes_read < 1)
  {
    perror("Read file descriptor failed");
    return;
  }
  buffer[bytes_read] = '\0';
}

void free_request(void)
{
  //
}
