#ifndef HANDLE_PATH_H_
#define HANDLE_PATH_H_

#define PATH_LENGTH 256

#include "libft.h"

int is_valid_path_char(char c);
int sanitize_url_path(const char *url_path);

#endif // HANDLE_PATH_H_
