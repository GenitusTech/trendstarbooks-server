#include "server.h"
#include <stdio.h>
#define PORT 8088

int main(void)
{
  Server server;

  init_server(&server, PORT);
  start_server(&server);

  close_connection(server.server_fd);
  printf("Server stopped\n");

  return (0);
}
