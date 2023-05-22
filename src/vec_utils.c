/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:25:41 by bok               #+#    #+#             */
/*   Updated: 2023/04/20 17:03:39 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_vec	vec_mul(t_vec vec, float f)
{
	return ((t_vec){vec.x * f, vec.y * f, vec.z * f});
}

inline float	vec_len(t_vec vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

inline float	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline t_vec	vec_cross(t_vec a, t_vec b)
{
	return ((t_vec){a.y * b.z - a.z * b.y, \
	a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x});
}

inline t_vec	vec_norm(t_vec vec)
{
	const float	tmp = vec_len(vec);

	if (tmp == 0.0f)
		return ((t_vec){0, 1, 0});
	return (vec_mul(vec, 1.0f / tmp));
}
