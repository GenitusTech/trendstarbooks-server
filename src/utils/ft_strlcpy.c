#include "libraries.h"

int ft_strlcpy(char *dest, const char *src, int size)
{
  int i;

  i = 0;
  if (size > 0)
  {
    while (*src && src[i] && i < (size - 1))
    {
      dest[i] = src[i];
      i += 1;
    }
    dest[i] = '\0';
    // /!\ MUST OPTIMIZE: Fill the remaining pointer by '\0'.
  }
  while (*src && src[i])
  {
    i += 1;
  }
  return (i);
}
