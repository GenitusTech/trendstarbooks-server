#include "../libft.h"

void *ft_memcpy(void *dst, const void *src, size_t n)
{
  size_t i;

  i = 0;
  while (((char *) src)[i] != '\0' && i < n)
  {
    ((char *)dst)[i] = ((char *)src)[i];
    i += 1;
  }
  while (i < n) {
    ((char *)dst)[i] = '\0';
    i += 1;
  }
  return (dst);
}
