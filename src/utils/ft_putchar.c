#include "libraries.h"

void ft_putchar(char c)
{
  (void) !write(1, &c, 1);
}
