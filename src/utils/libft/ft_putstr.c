#include "../libft.h"

void ft_putstr(const char *str)
{
  size_t i;

  i = 0;
  while (str[i])
  {
    ft_putchar(str[i]);
    i += 1;
  }
}
