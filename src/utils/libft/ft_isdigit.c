#include "libft.h"

int ft_isdigit(int c)
{
  // 48 = '0'
  // 57 = '9'
  if (c >= 48 && c <= 57)
  {
    return (1);
  }
  return (0);
}
