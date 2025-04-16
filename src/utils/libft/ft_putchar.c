#include "../libft.h"

void ft_putchar(const char c)
{
  if (write(1, &c, 1) < 0)
  {
    perror("ft_putchar: cannot write N bytes of BUF to FD");
  }
}
