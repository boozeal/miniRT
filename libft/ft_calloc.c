/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:17:08 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/11 10:01:56 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*re;
	size_t			tmpsize;
	size_t			i;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	tmpsize = count * size;
	re = malloc(tmpsize);
	if (!re)
		return (0);
	i = 0;
	while (i < tmpsize)
	{
		re[i] = 0;
		i++;
	}
	return ((void *)re);
}
