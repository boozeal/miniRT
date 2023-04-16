/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:25:41 by bok               #+#    #+#             */
/*   Updated: 2023/04/06 21:33:19 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec_len(t_vec vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

float	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	return ((t_vec){a.y * b.z - a.z * b.y, \
	a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x});
}

t_vec	vec_norm(t_vec vec)
{
	const float	tmp = vec_len(vec);

	if (checkf(tmp) == -1)
		exit_msg(1, "vec_norm");
	return (vec_mul(vec, 1.0f / tmp));
}

t_vec	reflect_vec(t_vec normal_vector, t_vec incident_vec)
{
	t_vec	reflected_vector;
	t_vec	temp;
	float	c;

	c = vec_dot(normal_vector, incident_vec) * 2;
	temp = vec_mul(normal_vector, c);
	reflected_vector = vec_sub(temp, incident_vec);
	return (reflected_vector);
}
