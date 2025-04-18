#include "../libft.h"

char *ft_strdup(const char *str)
{
  size_t i;
  size_t len;
  char *buffer;

  if (!str)
  {
    perror("ft_strdup: empty string");
    return (0);
  }
  len = ft_strlen(str);
  buffer = (char *) malloc(sizeof(char) * len + 1);
  if (!buffer)
  {
    perror("ft_strdup: count not malloc");
    return (0);
  }
  buffer = ft_memset(buffer, '\0', len + 1);
  i = 0;
  while (str[i])
  {
    buffer[i] = str[i];
    i += 1;
  }
  return (buffer);
}
