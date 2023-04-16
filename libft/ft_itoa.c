/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:16:57 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/20 17:44:34 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*putarr(long number, int count, int minus)
{
	char	*re;

	re = (char *)malloc(count);
	if (!re)
		return (NULL);
	re[count - 1] = 0;
	if (minus == 1)
		re[0] = '-';
	while (count > 1 + minus)
	{
		re[count - 2] = number % 10 + '0';
		number /= 10;
		count--;
	}
	return (re);
}

static char	*putzero(void)
{
	char	*re;

	re = (char *)(malloc(2));
	if (!re)
		return (NULL);
	re[0] = '0';
	re[1] = 0;
	return (re);
}

char	*ft_itoa(int n)
{
	int		count;
	long	number;

	count = 0;
	number = n;
	if (n == 0)
		return (putzero());
	while (n)
	{
		n = n / 10;
		count++;
	}
	if (number < 0)
	{
		number = -number;
		return (putarr(number, count + 2, 1));
	}
	return (putarr(number, count + 1, 0));
}
