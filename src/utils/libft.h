#ifndef LIBFT_H_
#define LIBFT_H_

#include <stdlib.h>
#include <unistd.h>

int ft_putchar(int c);
void ft_putstr(const char *str);
void ft_bzero(void *s, size_t n);
void *ft_memset(void *s, int c, size_t n);
void *ft_memchr(const void *s, int c, size_t n);
size_t ft_strlen(const char *str);
char *ft_strchr(const char *s, int c);
char *ft_strstr(const char *haystack, const char *needle);
int ft_strchrpos(const char *str, int c);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
int ft_strcmp(const char *s1, const char *s2);
void ft_strdelchar(char *str, char c);
int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_islower(int c);
int ft_isupper(int c);
#endif // LIBFT_H_
