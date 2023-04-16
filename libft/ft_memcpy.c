/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:06:11 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/10 23:23:02 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t num)
{
	unsigned char	*temp;
	unsigned char	*re;
	size_t			i;

	if (source == 0 && dest == 0)
		return (0);
	temp = (unsigned char *)source;
	re = (unsigned char *)dest;
	i = 0;
	while (i < num)
	{
		re[i] = temp[i];
		i++;
	}
	return (re);
}
