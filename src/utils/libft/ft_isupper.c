#include "libft.h"

int ft_isupper(int c)
{
  // 65 = 'A'
  // 90 = 'Z'
  if (c >= 65 && c <= 90)
  {
    return (1);
  }
  return (0);
}
