/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:36:20 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/12 12:31:49 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*re;
	size_t			i;
	unsigned int	length;

	length = ft_strlen(s);
	if (length < start)
	{
		re = (char *)malloc(1);
		re[0] = 0;
		return (re);
	}
	if (length - start < len)
		len = length - start;
	re = (char *)malloc(len + 1);
	if (!re)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		re[i] = s[i + start];
		i++;
	}
	re[i] = 0;
	return (re);
}
