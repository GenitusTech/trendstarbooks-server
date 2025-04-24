#include "libft.h"

char *ft_strstr(const char *haystack, const char *needle)
{
  size_t i;
  size_t j;

  if (!haystack)
  {
    return (0);
  }
  if (!*needle)
  {
    return ((char *) haystack);
  }
  i = 0;
  while (haystack[i])
  {
    j = 0;
    while (haystack[i + j] == needle[j])
    {
      if (needle[j + 1] == '\0')
      {
        return ((char *) haystack + i);
      }
      j += 1;
    }
    i += 1;
  }
  return (0);
}
