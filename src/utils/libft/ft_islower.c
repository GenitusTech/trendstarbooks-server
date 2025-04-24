#include "libft.h"

int ft_islower(int c)
{
  // 97 = 'a'
  // 122 = 'z'
  if (c >= 97 && c <= 122)
  {
    return (1);
  }
  return (0);
}
