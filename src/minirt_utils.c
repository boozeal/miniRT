/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:16:21 by jbok              #+#    #+#             */
/*   Updated: 2023/04/06 19:29:03 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_atof(char *s)
{
	double	lf;
	int		sign;
	int		prec;

	lf = 0;
	sign = 1;
	while (*s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s++ == '-')
			sign *= -1;
	}
	while (ft_isdigit(*s))
		lf = floor(lf * 10) + (*s++ - '0');
	if (*s == '.')
		s++;
	prec = -1;
	while (ft_isdigit(*s))
		lf += pow(10, prec--) * (*s++ - '0');
	return (sign * lf);
}

int	checkf(float a)
{
	if (a < EPSILON && a >= 0)
		return (-1);
	else if (a > -EPSILON && a <= 0)
		return (-1);
	return (0);
}

int	exit_msg(int n, char *str)
{
	printf("%s\n", str);
	exit(n);
	return (0);
}

int	check_valid_str(char *str)
{
	size_t	i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str && str[i])
	{
		if (str[i] == ',')
		{
			cnt++;
			if (cnt > 2)
				return (0);
		}
		i++;
	}
	if (cnt == 2)
		return (1);
	return (0);
}
