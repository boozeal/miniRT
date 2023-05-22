/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:17:45 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/20 18:21:39 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	rt_subplane_cy(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	vector[3];

	t = get_det_subplane(ray, s, 0);
	if (t > *dis || t < 0.0f)
		return ((t_color){-1});
	else
	{
		*dis = t;
		vector[E_CON] = vec_add(ray->origin, vec_mul(ray->dir, t));
		vector[E_NOR] = s->dir;
		vector[E_INC] = ray->dir;
		return (cal_bright(data, vector, s));
	}
}

t_color	rt_subplane_co(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	vector[3];

	t = get_det_subplane(ray, s, 1);
	if (t > *dis || t < 0.0f)
		return ((t_color){-1});
	else
	{
		*dis = t;
		vector[E_CON] = vec_add(ray->origin, vec_mul(ray->dir, t));
		vector[E_NOR] = s->dir;
		vector[E_INC] = ray->dir;
		return (cal_bright(data, vector, s));
	}
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

int	checkf(float a)
{
	if (a < EPSILON && a >= 0)
		return (-1);
	else if (a > -EPSILON && a <= 0)
		return (-1);
	return (0);
}
