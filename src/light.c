/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:41:14 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/07 21:25:24 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_deque.h"

// t_vec	get_incident_light(t_obj light, t_vec contact_vec)
// {
// 	light
// }

t_color	get_diffuse(t_data *data, t_vec *vector, t_obj *obj, int i)
{
	t_color	color;
	t_vec	incident_vec;
	int		kd;
	float	constant;

	kd = 1;
	color = (t_color){0};
	incident_vec = vec_norm(vec_sub(((t_obj *) \
	(data->lights->content[i]))->origin, vector[1]));
	constant = ((kd * (vec_dot(vector[0], incident_vec)) + 1) / 2);
	_add_color(&color, dot_color(mul_color(((t_obj *) \
		(data->lights->content[i]))->color, constant), obj->color));
	return (color);
}

t_color	get_specular(t_data *data, t_vec *vector, int i)
{
	t_color	color;
	t_vec	ref_vec;
	t_vec	view_vec;
	float	ks;
	float	constant;

	ks = 0.9;
	ref_vec = vec_norm(reflect_vec(vector[0], vec_sub(((t_obj *) \
		(data->lights->content[i]))->origin, vector[1])));
	view_vec = vec_norm(vec_sub(data->viewport.rays->origin, vector[1]));
	constant = powf((ks * (vec_dot(ref_vec, view_vec) + 1) / 2), 5);
	color = mul_color(((t_obj *)(data->lights->content[i]))->color, constant);
	return (color);
}

float	distance(t_obj *s, t_vec origin, t_vec dir)
{
	t_ray	ray;
	float	dis;
	float	d;

	ray.origin = origin;
	ray.dir = dir;
	dis = __FLT_MAX__;
	if (s->property == E_PLANE)
	{
		d = get_det_plane(&ray, s);
		// d = -1;
	}
	else if (s->property & E_SPHERE)
		d = solution_sphere(&ray, s, get_det_sphere(&ray, s));
	else if (s->property & E_CYLINDER)
		d = solution_cylinder(&ray, s, get_det_cylinder(&ray, s), &dis);
	else if (s->property & E_CONE)
		d = solution_cone(&ray, s, get_det_cone(&ray, s), &dis);
	else
		return (-1);
	dis = __FLT_MAX__;
	if (d == -2 && s->property & E_CONE)
		d = get_det_subplane(&ray, s, 1, &dis);
	if (d == -2 && s->property & E_CYLINDER)
		d = get_det_subplane(&ray, s, 0, &dis);
	return (d);
}

int	cal_shadow(t_data *data, t_vec contact_vec, int i)
{
	int		j;
	float	d;
	t_vec	inc_vec;
	t_vec	light_origin;

	j = 0;
	light_origin = ((t_obj *)data->lights->content[i])->origin;
	inc_vec = vec_sub(contact_vec, light_origin);
	while (j < data->objs->size)
	{
		d = distance((t_obj *)data->objs->content[j], \
			light_origin, vec_norm(inc_vec));
		if (d > -0.001f && d < vec_len(inc_vec))
			return (-1);
		j++;
	}
	return (0);
}
