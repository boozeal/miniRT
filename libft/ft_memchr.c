/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:51:37 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/10 16:39:10 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmps;
	unsigned char	tmpc;
	size_t			i;
	int				flag;

	tmps = (unsigned char *)s;
	tmpc = (unsigned char)c;
	i = 0;
	flag = 0;
	while (i < n)
	{
		if (tmps[i] == tmpc)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 1)
		return ((unsigned char *)(tmps + i));
	else
		return (NULL);
}
