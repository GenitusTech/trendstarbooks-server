#include "libft.h"

size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
  size_t i;
  size_t len;

  len = ft_strlen(src);
  if (!size)
  {
    return (len);
  }
  i = 0;
  if (size < len)
  {
    (void) ft_bzero(dst, size + 1);
  }
  else
  {
    (void) ft_bzero(dst, len + 1);
  }
  while (i < size && src[i] != '\0')
  {
    dst[i] = src[i];
    i += 1;
  }
  return (len);
}
