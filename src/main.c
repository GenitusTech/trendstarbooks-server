#include "server.h"

#define PORT 8088

int main(void)
{
  Server server;

  init_server(&server, PORT);
  start_server(&server);
  exit_server(&server);
  return (0);
}
