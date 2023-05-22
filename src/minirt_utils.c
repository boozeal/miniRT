/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:16:21 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 17:58:36 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
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
	if (*s)
		exit_msg(1, "Invalid parse arg");
	return (sign * lf);
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

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	is_valid_cam(t_obj *cam)
{
	if (vec_len(cam->dir) < 0.999 || vec_len(cam->dir) > 1.001)
	{
		_vec_norm(&cam->dir);
		printf("Invalid orientation vector: try with \
%f,%f,%f\n", cam->dir.x, cam->dir.y, cam->dir.z);
		exit(1);
	}
	_vec_norm(&cam->dir);
	if (cam->fov <= 0.0f || cam->fov > 180.0f)
		exit_msg(1, "FOV of camera must be in range (0.0,180.0]");
	else if (cam->fov >= 180.0f)
		cam->fov = 179.999;
	if (cam->aa <= 0)
		exit_msg(1, "AA scale must be a non zero positive integer");
	else if ((unsigned int)INT_MAX / cam->aa < SCREEN_HEIGHT || \
	(unsigned int)INT_MAX / cam->aa < SCREEN_WIDTH)
		exit_msg(1, "AA scale or SCREEN_SIZE is too large");
}
