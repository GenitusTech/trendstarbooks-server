#include "../libft.h"

size_t ft_strlen(const char *str)
{
  size_t i;

  i = 0;
  while (str && str[i])
  {
    i += 1;
  }
  return (i);
}
