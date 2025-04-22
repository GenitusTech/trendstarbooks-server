#ifndef SERVER_H_
#define SERVER_H_

#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>

#define MAX_CONNECTIONS 10

struct SServer
{
  // Server socket file descriptor.
  int server_fd;
  // server socket address.
  struct sockaddr_in server_addr;
  // While 1 is TRUE, server is running, else 0.
  sig_atomic_t running;
};
typedef struct SServer Server;

void init_server(Server *server, int port);
void handle_signal(int signal);
void start_server(Server *server);
void close_connection(int fd);
void *handle_client(void *arg);
void get_client_ip(int fd, char *ip, size_t size);
void get_client_content(int fd, char *content, size_t size);

#endif // SERVER_H_
