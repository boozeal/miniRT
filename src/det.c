/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   det.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:52:37 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/20 18:17:48 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_deque.h"

float	get_det_sphere(t_ray *ray, t_obj *s)
{
	t_vec	origin;
	float	b;
	float	c;
	float	det;

	origin = vec_sub(ray->origin, s->origin);
	b = vec_dot(origin, ray->dir);
	c = vec_dot(origin, origin) - s->rad * s->rad;
	det = b * b - c;
	return (det);
}

float	get_det_plane(t_ray *ray, t_obj *s)
{
	float	a;
	float	b;
	float	t;

	a = vec_dot(s->dir, ray->dir);
	if (checkf(a) < 0)
		return (-1);
	b = vec_dot(vec_sub(s->origin, ray->origin), s->dir);
	t = b / a;
	if (checkf(t) || t < 0 || t > 1000)
		return (-1);
	return (t);
}

float	get_det_subplane(t_ray *ray, t_obj *s, int flag)
{
	float	a;
	float	b;
	float	t;
	t_vec	origin;
	t_vec	contact_vec;

	if (flag == 1 && vec_dot(s->dir, ray->dir) >= 0)
		return (-1);
	if (vec_dot(s->dir, ray->dir) < 0 || flag == 1)
		origin = vec_add(s->origin, vec_mul(s->dir, s->height));
	else
		origin = s->origin;
	a = vec_dot(s->dir, ray->dir);
	if (checkf(a) < 0)
		return (-1);
	b = vec_dot(vec_sub(origin, ray->origin), s->dir);
	t = b / a;
	contact_vec = vec_add(ray->origin, vec_mul(ray->dir, t));
	if (vec_dot(vec_sub(origin, contact_vec), vec_sub(origin, contact_vec)) \
		<= pow(s->rad, 2) && t >= 0)
	{
		return (t);
	}
	return (-1);
}

float	get_det_cylinder(t_ray *ray, t_obj *s)
{
	t_vec	origin;
	float	a;
	float	b;
	float	c;
	float	det;

	a = powf(vec_dot(ray->dir, s->dir), 2) - 1;
	origin = vec_sub(ray->origin, s->origin);
	b = vec_dot(ray->dir, s->dir) * vec_dot(origin, s->dir) \
		- vec_dot(origin, ray->dir);
	c = powf(s->rad, 2) - vec_dot(origin, origin) + \
		powf(vec_dot(origin, s->dir), 2);
	det = (b * b) - c * a;
	return (det);
}

float	get_det_cone(t_ray *ray, t_obj *s)
{
	t_vec	origin;
	float	a;
	float	b;
	float	c;
	float	cos2;

	cos2 = powf(s->height, 2) / (powf(s->height, 2) + powf(s->rad, 2));
	a = powf(vec_dot(ray->dir, s->dir), 2) - cos2;
	origin = vec_sub(ray->origin, s->origin);
	b = vec_dot(ray->dir, s->dir) * vec_dot(origin, s->dir) \
		- (vec_dot(origin, ray->dir) * cos2);
	c = powf(vec_dot(origin, s->dir), 2) \
		- (vec_dot(origin, origin) * cos2);
	return ((b * b) - c * a);
}
