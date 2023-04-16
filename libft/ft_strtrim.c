/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:10:58 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/11 00:56:12 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	setchk(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*re;
	unsigned int	length;
	unsigned int	start;
	unsigned int	end;

	length = ft_strlen(s1);
	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	if (length == 0)
		return (ft_strdup(""));
	start = 0;
	end = length - 1;
	while (start < length - 1 && setchk(s1[start], set) == 1)
		start++;
	while (end > 0 && setchk(s1[end], set) == 1)
		end--;
	if (end < start)
		return (ft_strdup(""));
	re = (char *)malloc(end - start + 2);
	if (!re)
		return (NULL);
	ft_strlcpy(re, s1 + start, end - start + 2);
	return (re);
}
