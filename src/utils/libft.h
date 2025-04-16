#ifndef LIBFT_H_
#define LIBFT_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *ft_memset(void *s, int c, size_t n);
void ft_putchar(const char c);
void ft_putstr(const char *str);
char *ft_strdup(const char *str);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
size_t ft_strlen(const char *str);

#endif // LIBFT_H_
