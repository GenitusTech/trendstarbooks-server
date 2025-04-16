#include "../libft.h"

char *ft_strdup(const char *str)
{
  size_t len;
  char *buffer;

  if (!str)
  {
    return (0);
  }
  len = ft_strlen(str);
  buffer = (char *) malloc(sizeof(char) * len + 1);
  if (!buffer)
  {
    return (0);
  }
  ft_memset(buffer, '\0', len + 1);
  while (len)
  {
    buffer[len] = str[len];
    len -= 1;
  }
  return (buffer);
}
