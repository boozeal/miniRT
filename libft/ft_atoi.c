/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:09:02 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/12 12:13:32 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	flow_chk(int num, char c, int minus, char *a)
{
	a[num] = c;
	a[num + 1] = 0;
	if (num >= 18)
	{
		if ((minus < 0) && ft_strncmp(a, "9223372036854775808", -1) > 0)
			return (0);
		else if ((minus > 0) && ft_strncmp(a, "9223372036854775807", -1) > 0)
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		minus;
	int		num;
	int		count;
	char	a[5000];

	i = 0;
	minus = 1;
	num = 0;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		minus = -1 * (str[i] == '-') + (str[i] == '+');
		i++;
	}
	count = i;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		if (flow_chk(i - count, str[i], minus, a) != 1)
			return (flow_chk(i - count, str[i], minus, a));
		i++;
	}
	return (num * minus);
}
