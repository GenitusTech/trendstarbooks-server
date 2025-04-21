#include "libft.h"

void ft_putstr(const char *str)
{
  while (str && *str)
  {
    ft_putchar(*str);
    str++;
  }
}
