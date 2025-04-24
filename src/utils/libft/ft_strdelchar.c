#include "libft.h"

void ft_strdelchar(char *str, char c)
{
  char *src;
  char *dst;

  if (!str)
  {
    return;
  }
  src = (char *) str;
  dst = (char *) str;
  while (*src != '\0')
  {
    if (*src != c)
    {
      *dst = *src;
      dst++;
    }
    src++;
  }
  *dst = '\0';
}
