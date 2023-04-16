/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:49:27 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/11 00:56:46 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nbrpt(long nb1, int fd)
{
	char	numre[10];
	int		state;

	state = 0;
	while (nb1)
	{
		numre[state] = nb1 % 10 + '0';
		nb1 = nb1 / 10;
		state++;
	}
	while (state)
	{
		write(fd, numre + state - 1, 1);
		state--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	mnb;
	char	m[1];

	m[0] = '-';
	if (n > 0)
	{
		mnb = n;
		ft_nbrpt(mnb, fd);
	}
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		mnb = n;
		mnb = -mnb;
		write(fd, m, 1);
		ft_nbrpt(mnb, fd);
	}
}
