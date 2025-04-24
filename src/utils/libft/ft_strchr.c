#include "libft.h"

char *ft_strchr(const char *s, int c)
{
  while (s && *s)
  {
    if (*s == (char) c)
    {
      return ((char *)s);
    }
    s++;
  }
  return (0);
}
