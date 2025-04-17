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

void handle_signal(int signal);
void *handle_client(void *arg);
void close_connection(int fd);
void init_server(Server *server, int port);
void start_server(Server *server);
void get_client_ip(int client_fd, char *client_ip);
void get_client_content(int client_fd, char *buffer, size_t buffer_size);

#endif // SERVER_H_
