#include "server.h"
#include "http_request.h"
#include "http_response.h"
#include "libft.h"
#include "log.h"

#include <pthread.h>
#include <stdlib.h>

// Server instance to maintain the server information on callbacks.
Server *server_instance = 0;

void init_server(Server *server, int port)
{
  // Option value to be returned on 'setsockopt'.
  int opt;

  // Set instance for signal handler callback.
  server_instance = server;

  // Set up signal handling.
  (void) signal(SIGINT, handle_signal);
  (void) signal(SIGTERM, handle_signal);

  // Create netword socket.
  server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server->server_fd < 0)
  {
    close(server->server_fd);
    error_log("socket creation failed");
    exit(EXIT_FAILURE);
  }

  opt = 1;
  // Set socket options to prevent "address already in use" errors.
  if (setsockopt(server->server_fd,
                 SOL_SOCKET,
                 SO_REUSEADDR,
                 &opt,
                 (socklen_t) sizeof(opt)) < 0)
  {
    error_log("call on 'setsockopt' has failed");
    close(server->server_fd);
    exit(EXIT_FAILURE);
  }

  // Configure server address.
  server->server_addr.sin_family = AF_INET;
  // Inet 127.0.0.1 => localhost only.
  server->server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  // Set up port number (between 0 and 65535).
  server->server_addr.sin_port = ntohs((uint16_t) port);

  // Bind socket to (localhost) address.
  if (bind(server->server_fd,
           (struct sockaddr *) &server->server_addr,
           (socklen_t) sizeof(server->server_addr)) < 0)
  {
    error_log("binding server socket to address and port failed");
    close(server->server_fd);
    exit(EXIT_FAILURE);
  }

  server->running = 0; // FALSE
}

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

void start_server(Server *server)
{
  // Start listening to localhost on port 8088.
  if (listen(server->server_fd, MAX_CONNECTIONS) < 0)
  {
    error_log("listen server socket failed");
    close(server->server_fd);
    exit(EXIT_FAILURE);
  }

  ft_putstr("Server starting on port: 8088\n");
  server->running = 1; // TRUE

  while (server->running)
  {
    struct sockaddr_in client_addr;
    socklen_t client_len;
    int fd;
    pthread_t thread_id;

    client_len = (socklen_t) sizeof(client_addr);

    // Accept client incoming connection.
    fd = accept(server->server_fd,
                (struct sockaddr *) &client_addr,
                &client_len);

    if (fd < 0)
    {
      if (server->running)
      {
        error_log("client incoming connection acceptance failed");
      }
      continue;
    }

    // Create thread
    if (pthread_create(&thread_id, NULL, handle_client, &fd))
    {
      error_log("call on 'pthread_create' has failed");
      close_connection(fd);
      continue;
    }
    // Detach thread -> FREE when terminate is completed
    pthread_detach(thread_id);
  }

  server->running = 0; // FALSE
}

void close_connection(int fd)
{
  if (shutdown(fd, SHUT_RDWR) < 0)
  {
    error_log("connection could not shutdown");
  }
  if (close(fd) < 0)
  {
    error_log("file descriptor could not close");
  }
}

void *handle_client(void *arg)
{
  // Client file descriptor
  int fd;
  // Client IP address
  char ip[INET_ADDRSTRLEN];
  // full content read but unfiltered & unparsed
  char content[BUFFER_SIZE];
  // Server request from client
  HttpRequest http_request;
  // Server response for client
  HttpResponse http_response;

  // Get file descriptor integer
  fd = *(int *) arg;

  // Get client IP
  get_client_ip(fd, ip, INET_ADDRSTRLEN);
  if (!ft_strlen(ip))
  {
    error_log("could not retreive client IP");
    return (void *) (1); // EXIT WITH ERROR
  }

  // Get client content
  get_client_content(fd, content, BUFFER_SIZE);
  if (!ft_strlen(content))
  {
    error_log("could not retreive client content");
    return (void *) (1); // EXIT WITH ERROR
  }

  get_request(&http_request, content);
  get_response(&http_request, &http_response);

  free_request(&http_request);
  free_response(&http_response);

  return (0);
}

void exit_server(Server *server)
{
  close_connection(server->server_fd);
  ft_putstr("Server stopped\n");
}

void get_client_ip(int fd, char *ip, size_t size)
{
  struct sockaddr_in client_addr;
  socklen_t client_len;

  client_len = (socklen_t) sizeof(client_addr);

  // Get client address from file descriptor
  if (getpeername(fd, (struct sockaddr *) &client_addr, &client_len) != 0)
  {
    error_log("cannot retreive client address from file descriptor");
    return;
  }

  ft_bzero(ip, size);
  (void) inet_ntop(AF_INET,
                   &(client_addr.sin_addr),
                   (char *) ip,
                   (socklen_t) size);
}

void get_client_content(int fd, char *content, size_t size)
{
  ssize_t bytes_read;

  ft_bzero(content, size);
  bytes_read = read(fd, content, size - 1);
  if (bytes_read <= 0)
  {
    error_log("file descriptor reading failed");
    return;
  }
}
