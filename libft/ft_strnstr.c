/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:26:48 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/11 00:55:40 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strck(const char *str, const char *to_find, size_t i, size_t length)
{
	size_t	j;

	j = 0;
	while (j < length)
	{
		if (to_find[j] == str[i + j])
			j++;
		else
			break ;
	}
	if (j == length)
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(to_find);
	if (length == 0)
		return ((char *)str);
	while (str[i] && i + length <= len)
	{
		if (strck(str, to_find, i, length) == 1)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
