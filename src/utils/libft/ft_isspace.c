#include "../libft.h"

int ft_isspace(int c)
{
  // 32 = ' ' (SPACE)
  // 09 = '\t' (HORIZONTAL TABULATION)
  // 13 = '\r' (CARRIAGE RETURN)
  return ((c == 32) || (9 <= c && c <= 13));
}
