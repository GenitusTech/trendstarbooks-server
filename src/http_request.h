#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#define BUFFER_SIZE 4096

void handle_request(int fd);
void free_request(void);

#endif // HTTP_REQUEST_H_
