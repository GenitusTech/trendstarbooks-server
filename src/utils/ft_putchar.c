#include "libraries.h"

void ft_putchar(char c)
{
  if (write(1, &c, 1) < 0) {
    perror("Error on 'write' function.");
  }
}
