#ifndef SERVER_H_
#define SERVER_H_

#include <netinet/in.h>
#include <signal.h>

#define MAX_CONNECTIONS 10

typedef struct
{
  int server_fd; // server socket file descriptor
  struct sockaddr_in server_addr;
  sig_atomic_t running;
} Server;

void init_server(Server *server, int port);
void start_server(Server *server);

#endif // SERVER_H_
