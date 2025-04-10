#include "libraries.h"

int main(void)
{
  char *text;

  text = (char *) malloc(sizeof(char) * 11);
  (void) ft_strlcpy(text, "TEST 1 2 3", 11);
  ft_putstr(text);
  free(text);
  return (EXIT_SUCCESS);
}
