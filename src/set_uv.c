/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_uv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:46:34 by jbok              #+#    #+#             */
/*   Updated: 2023/04/19 22:07:57 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_quadric_uv2(float *uv, t_vec contact, t_vec axis, t_obj *obj);

void	set_sphere_uv(float *uv, t_vec *vec, t_obj *obj)
{
	const t_vec	contact = vec_sub(vec[E_CON], obj->origin);

	uv[0] = 0.5 + atan2f(contact.x / obj->rad, \
	contact.z / obj->rad) / (2 * M_PI);
	uv[1] = 0.5 + asinf(contact.y / obj->rad) / M_PI;
}

void	set_quadric_uv(float *uv, t_vec *vec, t_obj *obj)
{
	t_vec	contact;
	t_vec	axis;
	float	tmp;

	contact = vec_sub(vec[E_CON], obj->origin);
	if (obj->dir.y > 0.999f)
		axis = (t_vec){1, 0, 0};
	else if (obj->dir.y < -0.999f)
		axis = (t_vec){-1, 0, 0};
	else
		axis = vec_norm(vec_cross((t_vec){0, 1, 0}, obj->dir));
	tmp = vec_dot(vec[E_NOR], obj->dir);
	if (tmp > 0.999f || tmp < -0.999f)
	{
		_vec_sub(&contact, vec_mul(obj->dir, vec_dot(contact, obj->dir)));
		uv[1] = vec_len(contact) / (obj->rad);
		_vec_norm(&contact);
	}
	else
	{
		uv[1] = vec_dot(contact, obj->dir) / (obj->height);
		_vec_norm(_vec_sub(&contact, \
		vec_mul(obj->dir, vec_dot(contact, obj->dir))));
	}
	set_quadric_uv2(uv, contact, axis, obj);
}

void	set_quadric_uv2(float *uv, t_vec contact, t_vec axis, t_obj *obj)
{
	float	cos;

	cos = vec_dot(axis, contact);
	if (cos <= -1.0f)
		cos = -0.999f;
	else if (cos >= 1.0f)
		cos = 0.999f;
	if (vec_dot(vec_cross(axis, contact), obj->dir) > 0)
		uv[0] = 0.5f + acosf(cos) / (2 * M_PI);
	else
		uv[0] = 0.5f - acosf(cos) / (2 * M_PI);
}

void	set_plane_uv(float *uv, t_vec *vec, t_obj *obj)
{
	const t_vec	contact = vec_sub(vec[E_CON], obj->origin);
	t_vec		x;
	t_vec		y;
	float		tmp;

	if (vec[E_NOR].y > 0.999f)
		x = (t_vec){1, 0, 0};
	else if (vec[E_NOR].y < -0.999f)
		x = (t_vec){-1, 0, 0};
	else
		x = vec_norm(vec_cross_safe(vec[E_NOR], (t_vec){0, -1, 0}));
	y = vec_norm(vec_cross(vec[E_NOR], x));
	tmp = vec_dot(contact, x) * 0.2 + 0.5;
	uv[0] = tmp - (int)tmp;
	if (uv[0] < 0)
		uv[0]++;
	tmp = vec_dot(contact, y) * 0.2 + 0.5;
	uv[1] = tmp - (int)tmp;
	if (uv[1] < 0)
		uv[1]++;
}
