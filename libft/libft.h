/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:19:24 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/19 20:21:41 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

/* First part */
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *str);
void			*ft_memset(void *ptr, int value, size_t num);
void			*ft_bzero(void *ptr, size_t num);
void			*ft_memcpy(void *dest, const void *source, size_t num);
void			*ft_memmove(void *dest, const void *source, size_t num);
size_t			ft_strlcpy(char *dest, const char *src, unsigned int size);
size_t			ft_strlcat(char *dest, const char *src, unsigned int size);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
void			free_split(char **doc);
/* Second part */
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
/* Bonue part */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
/* GNL part */
char			*find_enter(char *str);
int				get_buffer(int fd, char *array[257]);
char			*devide(char **remain);
char			*get_next_line(int fd);
size_t			gnl_strlen(const char *str);
size_t			gnl_strlcpy(char *dest, char *src, size_t size);
char			*gnl_strjoin(char *s1, char *s2);
int				gnl_strchr(const char *str, int c);
char			*handle_eof(char **array);
/* Extra part */
unsigned int	ft_abs(int a);
#endif
