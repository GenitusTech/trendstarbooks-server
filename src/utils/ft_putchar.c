#include "libraries.h"

void ft_putchar(char c)
{
  long int len = write(1, &c, 1);
  if (len < 0) {
    perror("Error on 'write' function.");
  }
}
