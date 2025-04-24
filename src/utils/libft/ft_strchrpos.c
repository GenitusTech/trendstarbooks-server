#include "libft.h"

int ft_strchrpos(const char *str, int c)
{
  char *ptr;

  ptr = ft_strchr(str, c);
  if (!ptr) {
    return (-1);
  }
  return (int)(ptr - str);
}
