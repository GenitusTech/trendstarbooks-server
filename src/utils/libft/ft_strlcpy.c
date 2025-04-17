#include "../libft.h"

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
    (void) ft_memset(dst, '\0', size);
  }
  else
  {
    (void) ft_memset(dst, '\0', len + 1);
  }
  while (i < (size - 1) && src[i] != '\0')
  {
    dst[i] = src[i];
    i += 1;
  }
  return (len);
}
