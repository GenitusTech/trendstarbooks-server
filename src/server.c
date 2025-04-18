#include "server.h"
#include "http_request.h"
#include "http_response.h"
#include "utils/libft.h"
// #include "middleware.h"
// #include "router.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

Server *server_instance = 0;

void handle_signal(int signal)
{
  if (signal == SIGINT || signal == SIGTERM)
  {
    if (server_instance != 0)
    {
      server_instance->running = 0; // FALSE
    }
  }
}

void *handle_client(void *arg)
{
  int client_fd;
  char client_ip[INET_ADDRSTRLEN];
  char raw_content[BUFFER_SIZE];
  HttpRequest *http_request;

  client_fd = *(int *) arg;

  // Get client IP
  (void) ft_memset(client_ip, '\0', INET_ADDRSTRLEN);
  get_client_ip(client_fd, client_ip);

  // Get client buffer content
  (void) ft_memset(raw_content, '\0', BUFFER_SIZE);
  get_client_content(client_fd, raw_content, BUFFER_SIZE);

  close_connection(client_fd);

  http_request = get_client_request(raw_content);

  free_request(http_request);

  return (0);
}

void close_connection(int fd)
{
  if (shutdown(fd, SHUT_RDWR) < 0)
  {
    perror("Connection could not shutdown");
  }
  if (close(fd) < 0)
  {
    perror("File descriptior could not close");
  }
}

void init_server(Server *server, int port)
{
  int opt;

  // Set instance for signal handler callback
  server_instance = server;

  // Set up signal handling
  (void) signal(SIGINT, handle_signal);
  (void) signal(SIGTERM, handle_signal);

  // Create socket
  server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server->server_fd < 0)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  opt = 1;
  // Set socket options to prevent "address already in use" errors
  if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, (socklen_t) sizeof(opt)) < 0)
  {
    perror("error: setsockopt");
    close(server->server_fd);
    exit(EXIT_FAILURE);
  }

  // Configure server address
  server->server_addr.sin_family = AF_INET;
  server->server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Inet 127.0.0.1 => localhost only
  server->server_addr.sin_port = ntohs((uint16_t) port);

  // Bind socket to (localhost) address
  if (bind(server->server_fd, (struct sockaddr *) &server->server_addr, (socklen_t) sizeof(server->server_addr)) < 0)
  {
    perror("Binding socket to address failed");
    close(server->server_fd);
    exit(EXIT_FAILURE);
  }

  server->running = 0; // FALSE
}

void start_server(Server *server)
{
  // Start listening
  if (listen(server->server_fd, MAX_CONNECTIONS) < 0)
  {
    perror("Listen server socket failed");
    close(server->server_fd);
    exit(EXIT_FAILURE);
  }

  printf("Server starting on port %hu\n", (unsigned short int) ntohs(server->server_addr.sin_port));
  server->running = 1; // TRUE

  while (server->running)
  {
    struct sockaddr_in client_addr;
    socklen_t client_len;
    int client_fd;
    // pthread_t thread_id;

    client_len = (socklen_t) sizeof(client_addr);
    // Accept client incoming connection
    client_fd = accept(server->server_fd, (struct sockaddr *) &client_addr, &client_len);

    if (client_fd < 0)
    {
      if (server->running)
      {
        perror("Client incoming connection acceptance failed");
      }
      continue;
    }

    (void) handle_client((void *) &client_fd);
    // // Create thread
    // if (pthread_create(&thread_id, NULL, handle_client, &client_fd))
    // {
    //   perror("error: pthread_create");
    //   close_connection(client_fd);
    //   continue;
    // }
    // // Detach thread -> FREE when terminate is completed
    // pthread_detach(thread_id);
  }

  server->running = 0; // FALSE
  close_connection(server->server_fd);
  printf("Server stopped\n");
}

void get_client_ip(int client_fd, char *client_ip)
{
  struct sockaddr_in client_addr;
  socklen_t client_len;

  client_len = (socklen_t) sizeof(client_addr);

  // Get client address from file descriptor
  if (getpeername(client_fd, (struct sockaddr *) &client_addr, &client_len) != 0)
  {
    perror("Cannot retreive client address from file descriptor");
    return;
  }

  (void) inet_ntop(AF_INET, &(client_addr.sin_addr), (char *) client_ip, INET_ADDRSTRLEN);
}

void get_client_content(int client_fd, char *buffer, size_t buffer_size)
{
  // char buffer[BUFFER_SIZE];
  ssize_t bytes_read;

  bytes_read = read(client_fd, buffer, buffer_size - 1);
  if (bytes_read <= 0)
  {
    perror("file descriptor reading failed");
    return;
  }
}
