/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:56:07 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/10 23:23:15 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t num)
{
	unsigned char	*temp;
	unsigned char	*re;
	size_t			i;

	if (source == 0 && dest == 0)
		return (0);
	temp = (unsigned char *)source;
	re = (unsigned char *)dest;
	if (temp > re)
		i = 0;
	else
		i = num - 1;
	while (i < num && i >= 0)
	{
		re[i] = temp[i];
		if (temp > re)
			i++;
		else
			i--;
	}
	return (re);
}
