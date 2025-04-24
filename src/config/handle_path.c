#include "handle_path.h"
#include "log.h"

int is_valid_path_char(char c)
{
  // Allow alphanumeric characters and selected safe symbols
  return (c == '-' || c == '_' || c == '.' || c == '~' || c == '/' ||
          ft_isalnum(c));
}

int sanitize_url_path(const char *url_path)
{
  size_t url_path_len;
  size_t i;

  if (!url_path)
  {
    return (0);
  }

  url_path_len = ft_strlen(url_path);
  if (url_path_len == 0 || url_path_len > PATH_LENGTH)
  {
    return (0);
  }

  // Check for absolute paths or scheme prefixes
  if (url_path[0] != '/' || ft_strstr(url_path, "://"))
  {
    return (0);
  }

  // Check for parent directory traversal attempts
  if (ft_strstr(url_path, "../") || ft_strstr(url_path, "..\\"))
  {
    return (0);
  }

  // Check for null byte injection attempts
  if (ft_memchr(url_path, '\0', url_path_len))
  {
    return (0);
  }

  i = 0;
  // Validate each character
  while (i < url_path_len)
  {
    if (!is_valid_path_char(url_path[i]))
    {
      return (0);
    }
    i += 1;
  }

  return (1);
}
