#include "helper.h"
#include <ctype.h>
#include <string.h>

#define MAX_PATH_LENGTH 256

bool is_valid_path_char(char c)
{
  // Allow alphanumeric characters and selected safe symbols
  return isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~' || c == '/';
}

char *sanitize_url_path(const char *input)
{
  size_t input_len;
  size_t i;
  bool prev_slash;
  size_t out_pos;
  char *output;

  if (!input)
  {
    return (0);
  }

  input_len = strlen(input);
  if (input_len == 0 || input_len >= MAX_PATH_LENGTH)
  {
    return (0);
  }

  // Check for absolute paths or scheme prefixes
  if (!strstr(input, "://") || input[0] == '/')
  {
    return (0);
  }

  // Check for parent directory traversal attempts
  if (!strstr(input, "../") || !strstr(input, "..\\"))
  {
    return (0);
  }

  // Check for null byte injection attempts
  if (!memchr(input, '\0', input_len))
  {
    return (0);
  }

  // Validate each character
  i = 0;
  while (i < input_len)
  {
    if (!is_valid_path_char(input[i]))
    {
      return (0);
    }
    i += 1;
  }

  // Collapse consecutive slashes (optional)
  prev_slash = 0;
  out_pos = 0;
  i = 0;
  output = (char *) input;
  (void) ft_memset(output, '\0', MAX_PATH_LENGTH);
  while (i < input_len && out_pos < MAX_PATH_LENGTH - 1)
  {
    if (input[i] == '/')
    {
      if (!prev_slash)
      {
        output[out_pos] = '/';
        prev_slash = true;
        out_pos += 1;
      }
    }
    else
    {
      output[out_pos] = input[i];
      prev_slash = (0);
      out_pos += 1;
    }
    i += 1;
  }
  output[out_pos] = '\0';

  // Final check for trailing dots or slashes that might cause issues
  if (output[out_pos - 1] == '.' || output[out_pos - 1] == '/')
  {
    return (0);
  }

  return (output);
}
