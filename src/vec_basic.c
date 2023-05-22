/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:25:41 by bok               #+#    #+#             */
/*   Updated: 2023/04/20 17:03:14 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

inline t_vec	vec_sub(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec	vec_cross_safe(t_vec a, t_vec b)
{
	float	tmp;

	tmp = vec_dot(a, b);
	if (tmp > 0.999)
	{
		tmp = vec_dot(a, (t_vec){0, 1, 0});
		if (tmp > 0.999)
			return ((t_vec){1, 0, 0});
		else if (tmp < -0.999)
			return (vec_cross(a, (t_vec){-1, 0, 0}));
		else
			return (vec_cross(a, (t_vec){0, 1, 0}));
	}
	else if (tmp < -0.999)
	{
		tmp = vec_dot(a, (t_vec){0, -1, 0});
		if (tmp > 0.999)
			return ((t_vec){-1, 0, 0});
		else if (tmp < -0.999)
			return (vec_cross(a, (t_vec){1, 0, 0}));
		else
			return (vec_cross(a, (t_vec){0, -1, 0}));
	}
	else
		return (vec_cross(a, b));
}
