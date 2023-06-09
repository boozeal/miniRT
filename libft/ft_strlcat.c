/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:24:40 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/19 20:33:25 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	dcount;
	unsigned int	scount;

	dcount = 0;
	scount = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (*dest)
	{
		dcount++;
		dest++;
	}
	while ((*src) && (scount + dcount + 1 < size))
	{
		*dest++ = *src++;
		scount++;
	}
	while (*src++)
		scount++;
	if (size < dcount)
		return (scount + size);
	*dest = '\0';
	return (dcount + scount);
}
