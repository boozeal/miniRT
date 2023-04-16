/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:41:06 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/09 09:19:47 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
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
		return ((char *)(str + i));
	else
		return (NULL);
}
