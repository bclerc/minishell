/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:34:51 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 16:37:27 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

long			ft_atol(const char *str);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_putnstr(char *s, int n);
char			*ft_strsave(char *s, char c);
char			*ft_strcdup(char *str, char c);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_isupper(char c);
int				ft_todigit(int c);
int				ft_strisdigit(char *str);
char			*ft_strsdup(char *str, char *set);
void			*ft_memalloc(size_t size);
char			*ft_swap(char *a, char *b);
char			*ft_strdup(const char *str);
char			*ft_strndup(const char *str, int len);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strncat(char *dest, const char *src, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *src, const char *find);
char			*ft_strnstr(const char *src, const char *find, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_atoi(const char *str);
char			*ft_strnew(size_t t);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlen(const char *str);
void			ft_memdel(void **ap);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(const char *str);
void			ft_putstr_fd(const char *str, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int i);
void			ft_putnbr_fd(int i, int fd);
char			*ft_itoa(int n);
char			*ft_itoa_base(long value, int bases);
long long		ft_abs(long long nb);
char			**ft_strsplit(char const *s, char c);
#endif
