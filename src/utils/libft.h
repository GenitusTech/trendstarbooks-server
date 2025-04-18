#ifndef LIBFT_H_
#define LIBFT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *ft_memset(void *s, int c, size_t n);
void ft_putchar(const char c);
void ft_putstr(const char *str);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strdup(const char *str);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
size_t ft_strlen(const char *str);
int ft_isspace(char c);

void ft_strdelchar(char *str, char c);

#endif // LIBFT_H_
