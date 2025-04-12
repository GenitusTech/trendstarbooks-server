#include "server.h"
#include <stdlib.h>

#define PORT 8080

int main(void)
{
  Server server;

  init_server(&server, PORT);
  start_server(&server);

  return (EXIT_SUCCESS);
}
