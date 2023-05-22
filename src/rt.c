/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:14:50 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/20 18:45:58 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	rt_sphere(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	vector[3];

	t = solution_sphere(ray, s, get_det_sphere(ray, s));
	if (t > *dis || t < 0.0f)
		return ((t_color){-1});
	else
	{
		*dis = t;
		vector[E_CON] = vec_add(ray->origin, vec_mul(ray->dir, t));
		vector[E_NOR] = vec_norm(vec_sub(vector[1], s->origin));
		vector[E_INC] = ray->dir;
		return (cal_bright(data, vector, s));
	}
}

t_color	rt_plane(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	vector[3];

	t = get_det_plane(ray, s);
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

t_color	rt_cylinder(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	vector[3];
	t_vec	cp;
	float	temp;

	t = solution_cylinder(ray, s, get_det_cylinder(ray, s));
	temp = get_det_subplane(ray, s, 0);
	if (temp >= 0)
		t = temp;
	if (t > *dis || t < 0.0f)
		return ((t_color){-1});
	else
	{
		if (temp >= 0)
			return (rt_subplane_cy(data, ray, s, dis));
		*dis = t;
		vector[E_CON] = vec_add(ray->origin, vec_mul(ray->dir, t));
		cp = vec_sub(vector[E_CON], s->origin);
		vector[E_NOR] = vec_norm(vec_sub(cp, \
			vec_mul(s->dir, vec_dot(cp, s->dir))));
		vector[E_INC] = ray->dir;
		return (cal_bright(data, vector, s));
	}
}

t_color	rt_cone(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	vector[3];
	t_vec	cp;
	float	temp;

	t = solution_cone(ray, s, get_det_cone(ray, s));
	temp = get_det_subplane(ray, s, 1);
	if (temp >= 0)
		t = temp;
	if (t < 0.0f || t > *dis)
		return ((t_color){-1});
	else
	{
		if (temp >= 0)
			return (rt_subplane_co(data, ray, s, dis));
		*dis = t;
		vector[E_CON] = vec_add(ray->origin, vec_mul(ray->dir, t));
		cp = vec_sub(vector[E_CON], s->origin);
		vector[E_NOR] = vec_norm(vec_sub(cp, \
			vec_mul(s->dir, vec_dot(cp, s->dir))));
		vector[E_INC] = ray->dir;
		return (cal_bright(data, vector, s));
	}
}

t_color	rt_ray(t_data *data, t_ray *ray)
{
	ssize_t	i;
	float	dis;
	t_color	color;
	t_color	tmp;

	i = 0;
	dis = __FLT_MAX__;
	color.color = 0;
	while (i < data->objs->size)
	{
		if (((t_obj *)(data->objs->content[i]))->property & E_SPHERE)
			tmp = rt_sphere(data, ray, data->objs->content[i], &dis);
		else if (((t_obj *)(data->objs->content[i]))->property & E_PLANE)
			tmp = rt_plane(data, ray, data->objs->content[i], &dis);
		else if (((t_obj *)(data->objs->content[i]))->property & E_CYLINDER)
			tmp = rt_cylinder(data, ray, data->objs->content[i], &dis);
		else if (((t_obj *)(data->objs->content[i]))->property & E_CONE)
			tmp = rt_cone(data, ray, data->objs->content[i], &dis);
		if (tmp.color != (unsigned int)-1)
			color = tmp;
		i++;
	}
	return (color);
}
