/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:01:05 by seonghyu          #+#    #+#             */
/*   Updated: 2023/03/30 16:15:31 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*re;
	// int		i;
	int		size;

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
	ft_strcpy(re, s1);
	ft_strcpy(re + ft_strlen(s1), s2);
	re[size] = 0;
	return (re);
}
