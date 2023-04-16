/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:05:31 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/09 09:20:20 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				i;
	int				flag;
	unsigned char	tmpc;

	i = ft_strlen(str);
	flag = 0;
	tmpc = (unsigned char)c;
	if (c == 0)
		return ((char *)(str + i));
	if (i == 0)
		return (NULL);
	while (i >= 0)
	{
		if (str[i] == tmpc)
		{
			flag = 1;
			break ;
		}
		i--;
	}
	if (flag == 1)
		return ((char *)(str + i));
	else
		return (NULL);
}
