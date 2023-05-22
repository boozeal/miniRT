/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solutions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:49:43 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/20 18:26:36 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_deque.h"

float	solution_sphere(t_ray *ray, t_obj *s, float det)
{
	t_vec	origin;
	float	b;
	float	t;

	if (det < 0)
		return (-1);
	origin = vec_sub(ray->origin, s->origin);
	b = vec_dot(origin, ray->dir);
	t = (b * (-1) - sqrtf(det));
	if (t >= 0)
		return (t);
	else
	{
		t = (b * (-1) + sqrtf(det));
		return (t);
	}
}

float	solution_cylinder(t_ray	*ray, t_obj *s, float det)
{
	t_vec	origin;
	t_vec	cp;
	float	a;
	float	b;
	float	t;

	if (det < 0)
		return (-1);
	a = powf(vec_dot(ray->dir, s->dir), 2) - 1;
	origin = vec_sub(ray->origin, s->origin);
	b = vec_dot(ray->dir, s->dir) * vec_dot(origin, s->dir) \
		- vec_dot(origin, ray->dir);
	t = fmin((b * (-1) + sqrtf(det)) / a, (b * (-1) - sqrtf(det)) / a);
	cp = vec_sub(vec_add(ray->origin, vec_mul(ray->dir, t)), s->origin);
	if (!(t < 0 || vec_dot(cp, s->dir) < 0 || vec_dot(cp, s->dir) > s->height))
		return (t);
	t = fmax((b * (-1) + sqrtf(det)) / a, (b * (-1) - sqrtf(det)) / a);
	cp = vec_sub(vec_add(ray->origin, vec_mul(ray->dir, t)), s->origin);
	if (t < 0 || vec_dot(cp, s->dir) < 0 || vec_dot(cp, s->dir) > s->height)
		return (-1);
	return (t);
}

float	solution_cone(t_ray	*ray, t_obj *s, float det)
{
	t_vec	temp;
	float	a;
	float	b;
	float	t;
	float	cos;

	if (det < 0)
		return (-1);
	cos = sqrt(powf(s->height, 2) / (powf(s->height, 2) + powf(s->rad, 2)));
	a = powf(vec_dot(ray->dir, s->dir), 2) - powf(cos, 2);
	temp = vec_sub(ray->origin, s->origin);
	b = vec_dot(ray->dir, s->dir) * vec_dot(temp, s->dir) \
		- (vec_dot(temp, ray->dir) * powf(cos, 2));
	t = fmin((b * (-1) + sqrtf(det)) / a, (b * (-1) - sqrtf(det)) / a);
	temp = vec_sub(vec_add(ray->origin, vec_mul(ray->dir, t)), s->origin);
	if (!(t < 0 || vec_dot(temp, s->dir) < 0 || \
		vec_dot(temp, s->dir) > s->height))
		return (t);
	t = fmax((b * (-1) + sqrtf(det)) / a, (b * (-1) - sqrtf(det)) / a);
	temp = vec_sub(vec_add(ray->origin, vec_mul(ray->dir, t)), s->origin);
	if (t < 0 || vec_dot(temp, s->dir) < 0 || vec_dot(temp, s->dir) > s->height)
		return (-1);
	return (t);
}
