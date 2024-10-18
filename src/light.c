/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:41:14 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/20 18:23:59 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_deque.h"

t_color	get_diffuse(t_data *data, t_vec *vector, t_color texture, int i)
{
	t_color	color;
	t_vec	incident_vec;
	int		kd;
	float	constant;

	color.color = 0;
	kd = 1;
	incident_vec = vec_norm(vec_sub(((t_obj *) \
	(data->lights->content[i]))->origin, vector[1]));
	constant = ((kd * (vec_dot(vector[0], incident_vec)) + 1) / 2) * ((t_obj *) \
		(data->lights->content[i]))->ratio;
	_add_color(&color, dot_color(mul_color(((t_obj *) \
		(data->lights->content[i]))->color, constant), texture));
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
	constant = powf((ks * (vec_dot(ref_vec, view_vec) + 1) / 2), 5) \
		* ((t_obj *)(data->lights->content[i]))->ratio;
	color = mul_color(((t_obj *)(data->lights->content[i]))->color, constant);
	return (color);
}

float	distance(t_obj *s, t_vec origin, t_vec dir)
{
	t_ray	ray;
	float	d;

	ray.origin = origin;
	ray.dir = dir;
	if (s->property & E_PLANE)
		d = get_det_plane(&ray, s);
	else if (s->property & E_SPHERE)
		d = solution_sphere(&ray, s, get_det_sphere(&ray, s));
	else if (s->property & E_CYLINDER)
		d = solution_cylinder(&ray, s, get_det_cylinder(&ray, s));
	else if (s->property & E_CONE)
		d = solution_cone(&ray, s, get_det_cone(&ray, s));
	else
		return (-1);
	if (d == -2 && s->property & E_CONE)
		d = get_det_subplane(&ray, s, 1);
	if (d == -2 && s->property & E_CYLINDER)
		d = get_det_subplane(&ray, s, 0);
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
