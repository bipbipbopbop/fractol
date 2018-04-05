/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:09:08 by jhache            #+#    #+#             */
/*   Updated: 2018/02/25 13:37:43 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** MACRO pour les flags des fonctions
*/
/*
** ft_strjoinfree
*/
# define FIRST 1
# define SECOND 2
# define BOTH 3

/*
** ft_sqrt
*/
# define UPROUNDED 4

/*
** ft_str(r)str
*/
# define STR 5
# define CHAR 6

/*
** **********************************
*/

/*
** macro pour calculer la valeur absolue :
*/
# define ABS(x) ((x < 0) ? ((x) * -1) : x)

# include <string.h>
# include <inttypes.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strrev(char *str);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_charpos(const char *s, int c);
size_t			ft_mulcharpos(const char *s, const char *c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack,
							const char *needle, int flag);
char			*ft_strrstr(const char *haystack,
							const char *needle, int flag);
char			*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
size_t			ft_nbrlen(intmax_t n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
void			ft_toupper(char *c);
void			ft_tolower(char *c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoinfree(char *s1, char *s2, int flag);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_llitoa(long long n);
char			*ft_imaxtoa(intmax_t n);
char			*ft_ullitoa(unsigned long long n);
char			*ft_uimaxtoa(uintmax_t n);
char			*ft_itoa_base(int n, char *base_from, char *base_to);
char			*ft_llitoa_base(long long n, char *base_from, char *base_to);
char			*ft_imaxtoa_base(intmax_t n, char *base_from, char *base_to);
char			*ft_ullitoa_base(unsigned long long n,
								char *base_from, char *base_to);
char			*ft_uimaxtoa_base(uintmax_t n, char *base_from, char *base_to);
char			*ft_convert_base(char *nb, char *base_from, char *base_to);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(intmax_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(intmax_t n, int fd);
t_list			*ft_lstnew(void const *content, size_t cont_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
int				ft_lstlen(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
unsigned int	ft_sqrt(unsigned int nb, int flag);
long			ft_power(int nb, unsigned int power);
int				ft_printf(const char *format, ...);
int				get_next_line(const int fd, char **line);
#endif
