#include "../libft.h"

char *ft_strdup(const char *str)
{
  int i;
  char *buffer;

  i = 0;
  buffer = (char *) malloc(sizeof(char) * ft_strlen(str) + 1);
  if (!buffer) {
    return (NULL);
  }
  while (str[i])
  {
    buffer[i] = str[i];
    i += 1;
  }
  buffer[i] = '\0';
  return (buffer);
}
