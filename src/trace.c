/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:53:48 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/20 17:58:51 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_deque.h"

void	apply_normalmap(float uv[2], t_vec *w, t_obj *obj)
{
	t_vec	normal;
	t_vec	u;
	t_vec	v;

	normal = obj->normal->map[(int)(uv[0] * (obj->normal->w - 1)) \
	+ ((int)(uv[1] * (obj->normal->h - 1))) * obj->normal->w];
	u = vec_norm(vec_cross_safe(*w, obj->dir));
	v = vec_norm(vec_cross(*w, u));
	_vec_mul(&u, normal.x);
	_vec_mul(&v, normal.z);
	_vec_norm(_vec_add(_vec_add(_vec_mul(w, normal.y), u), v));
}

t_color	cal_bright(t_data *data, t_vec *vector, t_obj *obj)
{
	t_color	texture;
	t_color	color;

	color.color = 0;
	texture = get_texturecolor(vector, obj);
	_add_color(&color, get_phong(data, vector, texture));
	return (color);
}

t_color	get_texturecolor(t_vec *vector, t_obj *obj)
{
	t_color	texture;
	float	uv[2];

	if (obj->property & E_TEXTURE || obj->property & E_NORMAL)
	{
		uv[0] = 0;
		uv[1] = 0;
		if (obj->property & E_SPHERE)
			set_sphere_uv(uv, vector, obj);
		else if (obj->property & E_CONE || obj->property & E_CYLINDER)
			set_quadric_uv(uv, vector, obj);
		else if (obj->property & E_PLANE)
			set_plane_uv(uv, vector, obj);
	}
	if (obj->property & E_TEXTURE)
		texture = obj->texture->map[(int)(uv[0] * (obj->texture->w - 1)) \
		+ ((int)(uv[1] * (obj->texture->h - 1))) * obj->texture->w];
	else
		texture.color = obj->color.color;
	if (obj->property & E_NORMAL)
		apply_normalmap(uv, vector, obj);
	return (texture);
}

t_color	get_phong(t_data *data, t_vec *vector, t_color texture)
{
	int		i;
	t_color	color;
	t_vec	bias;

	bias = vec_mul(vector[E_NOR], 0.001);
	color.color = 0;
	_add_color(&color, amb_diffuse(data, texture));
	_add_color(&color, amb_specular(data, vector));
	i = -1;
	while (++i < data->lights->size)
	{
		if (cal_shadow(data, vec_add(vector[E_CON], bias), i) < 0)
			continue ;
		_add_color(&color, get_diffuse(data, vector, texture, i));
		_add_color(&color, get_specular(data, vector, i));
	}
	return (color);
}
