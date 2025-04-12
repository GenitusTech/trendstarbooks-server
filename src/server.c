#include "server.h"
#include "http_request.h"
// #include "router.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Server *server_instance = NULL;

static void handle_signal(int signal)
{
  if (signal == SIGINT || signal == SIGTERM)
  {
    if (server_instance != NULL)
    {
      server_instance->running = 0; // FALSE
    }
  }
}

static void close_connection(int fd)
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
  signal(SIGINT, handle_signal);
  signal(SIGTERM, handle_signal);

  // Create socket
  server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server->server_fd < 0)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  opt = 1;
  // Set socket options to prevent "address already in use" errors
  if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
  {
    perror("error: setsockopt");
    close(server->server_fd);
    exit(EXIT_FAILURE);
  }

  // Configure server address
  server->server_addr.sin_family = AF_INET;
  server->server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Inet 127.0.0.1 => localhost only
  server->server_addr.sin_port = htons((uint16_t) port);

  // Bind socket to (localhost) address
  if (bind(server->server_fd, (struct sockaddr *) &server->server_addr, sizeof(server->server_addr)) < 0)
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

  printf("Server started on port %hu\n", ntohs(server->server_addr.sin_port));
  server->running = 1; // TRUE

  while (server->running)
  {
    struct sockaddr_in client_addr;
    socklen_t client_len;
    int client_fd;

    // Accept client incoming connection
    client_len = sizeof(client_addr);
    client_fd = accept(server->server_fd, (struct sockaddr *) &client_addr, &client_len);
    if (client_fd < 0)
    {
      if (server->running)
      {
        perror("Accept failed");
      }
      continue;
    }

    // Read client request
    handle_request(client_fd);

    // Properly close connection
    close_connection(client_fd);
  }

  server->running = 0; // FALSE
  close_connection(server->server_fd);
  printf("Server stopped\n");
}
