#include "../libft.h"

size_t ft_strpos(const char *s1, const char *s2)
{
  char *str;

  str = ft_strstr(s1, s2);
  if (!str)
  {
    return (0);
  }
  return (ft_strlen(s1) - ft_strlen(str));
}
