#ifndef HELPER_H_
#define HELPER_H_

#include "../utils/libft.h"

#include <stdbool.h>

bool is_valid_path_char(char c);
char *sanitize_url_path(const char *input);

#endif // HELPER_H_
