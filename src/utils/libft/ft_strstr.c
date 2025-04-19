#include "../libft.h"

char *ft_strstr(const char *haystack, const char *needle)
{
  unsigned int i;
  unsigned int j;

  if (!*needle)
  {
    return ((char *) haystack);
  }
  i = 0;
  while (haystack[i] != '\0')
  {
    j = 0;
    while (needle[j] != '\0' && needle[j] == haystack[i + j])
    {
      j += 1;
    }
    if (needle[j] == '\0')
    {
      return (char *) haystack + i;
    }
    i += 1;
  }
  return (0);
}
