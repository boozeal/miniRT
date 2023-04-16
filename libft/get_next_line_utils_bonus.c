/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:16:17 by seonghyu          #+#    #+#             */
/*   Updated: 2023/03/30 16:15:54 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	gnl_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (src[i] != '\0')
	{
		i++;
		count++;
	}
	i = 0;
	while ((i + 1 < size) && (i < count))
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (count);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*re;
	// int		i;
	int		size;

	if (s1 == NULL)
	{
		re = (char *)malloc(ft_strlen(s2) + 1);
		ft_strlcpy(re, s2, -1);
		return (re);
	}
	size = ft_strlen(s1) + ft_strlen(s2);
	if (size == 0)
	{
		re = (char *)malloc(1);
		re[0] = 0;
		return (re);
	}
	// i = 0;
	re = (char *)malloc(size + 1);
	if (!re)
		return (0);
	ft_strlcpy(re, s1, -1);
	ft_strlcpy(re + ft_strlen(s1), s2, -1);
	re[size] = 0;
	return (re);
}

int	gnl_strchr(const char *str, int c)
{
	int				i;
	int				flag;
	unsigned char	tmpc;

	i = 0;
	flag = 0;
	tmpc = (unsigned char)c;
	while (str[i])
	{
		if (str[i] == tmpc)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (str[i] == tmpc)
		flag = 1;
	if (flag == 1)
		return (i);
	else
		return (-1);
}

char	*handle_eof(char **array)
{
	char	*re;

	re = (char *)malloc(sizeof(char) * (ft_strlen(*array) + 1));
	if (!re)
		return (NULL);
	ft_strlcpy(re, *array, -1);
	free(*array);
	*array = NULL;
	return (re);
}
