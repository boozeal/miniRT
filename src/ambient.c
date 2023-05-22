/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:20:24 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/20 14:28:58 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	amb_diffuse(t_data *data, t_color texture)
{
	t_color	color;
	int		kd;
	float	constant;

	color.color = 0;
	kd = 1;
	constant = kd * data->ambient->ratio;
	_add_color(&color, dot_color(mul_color(data->ambient->color, constant), \
		texture));
	return (color);
}

t_color	amb_specular(t_data *data, t_vec *vector)
{
	t_color	color;
	t_vec	ref_vec;
	t_vec	view_vec;
	float	ks;
	float	constant;

	ks = 0.9;
	ref_vec = vec_norm(vec_mul(vector[E_NOR], -1));
	view_vec = vec_norm(vec_sub(data->viewport.rays->origin, vector[1]));
	constant = powf((ks * (vec_dot(ref_vec, view_vec) + 1) / 2), 5) \
		* data->ambient->ratio;
	color = mul_color(data->ambient->color, constant);
	return (color);
}
