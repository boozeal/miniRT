/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_self.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:25:41 by bok               #+#    #+#             */
/*   Updated: 2023/04/04 12:56:29 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	*_vec_add(t_vec *a, t_vec b)
{
	a->x += b.x;
	a->y += b.y;
	a->z += b.z;
	return (a);
}

t_vec	*_vec_sub(t_vec *a, t_vec b)
{
	a->x -= b.x;
	a->y -= b.y;
	a->z -= b.z;
	return (a);
}

t_vec	*_vec_mul(t_vec *a, float f)
{
	a->x *= f;
	a->y *= f;
	a->z *= f;
	return (a);
}

t_vec	*_vec_norm(t_vec *vec)
{
	const float	tmp = vec_len(*vec);

	if (tmp == 0.0f)
		exit_msg(1, "vec_norm");
	return (_vec_mul(vec, 1.0f / tmp));
}
