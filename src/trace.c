/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:53:48 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/08 19:27:01 by jbok             ###   ########.fr       */
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

float	solution_cylinder(t_ray	*ray, t_obj *s, float det, float *dis)
{
	t_vec	origin;
	t_vec	cp;
	float	a;
	float	b;
	float	t;

	if (get_det_subplane(ray, s, 0, dis) > 0)
		return (-2);
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

float	solution_cone(t_ray	*ray, t_obj *s, float det, float *dis)
{
	t_vec	temp;
	float	a;
	float	b;
	float	t;
	float	cos;

	if (get_det_subplane(ray, s, 1, dis) > 0)
		return (-2);
	if (det < 0)
		return (-1);
	cos = sqrt(powf(s->height, 2) / (powf(s->height, 2) + powf(s->rad, 2)));
	a = powf(vec_dot(ray->dir, s->dir), 2) - powf(cos, 2);
	temp = vec_sub(ray->origin, s->origin);
	b = vec_dot(ray->dir, s->dir) * vec_dot(temp, s->dir) \
		- (vec_dot(temp, ray->dir) * powf(cos, 2));
	t = fmin((b * (-1) + sqrtf(det)) / a, (b * (-1) - sqrtf(det)) / a);
	temp = vec_sub(vec_add(ray->origin, vec_mul(ray->dir, t)), s->origin);
	if (!(t < 0 || vec_dot(temp, s->dir) < 0 || vec_dot(temp, s->dir) > s->height))
		return (t);
	t = fmax((b * (-1) + sqrtf(det)) / a, (b * (-1) - sqrtf(det)) / a);
	temp = vec_sub(vec_add(ray->origin, vec_mul(ray->dir, t)), s->origin);
	if (t < 0 || vec_dot(temp, s->dir) < 0 || vec_dot(temp, s->dir) > s->height)
		return (-1);
	return (t);
}

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

float	get_det_subplane(t_ray *ray, t_obj *s, int flag, float *dis)
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
		*dis = t;
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

// t_vec axis;
// if (fabsf(obj->dir.y) > 0.999)
//     axis = (t_vec){obj->dir.y, 0, 0};
// else
//     axis = vec_cross((t_vec){0, 1, 0}, obj->dir);
// axis = vec_normalize(axis);

// t_vec local_coord = (t_vec){vec_dot(coord, axis), coord.y, vec_dot(coord, obj->dir)};
// float u = 0.5 + atan2f(local_coord.x, local_coord.z) / (2 * M_PI);
// if (u < 0)
//     u += 1;
// float v = local_coord.y / obj->height;

// t_color	uv_color(float u, float v, t_obj *obj)
// {
	
// }

void	set_uv(t_vec contact, t_vec norm, t_obj *obj, float *uv)
{
	t_vec	axis;
	float	tmp;

	if (obj->property & E_SPHERE)
	{
		uv[0] = 0.5 + atan2f(contact.x / obj->rad, contact.z / obj->rad) / (2 * M_PI);
		uv[1] = 0.5 + asinf(contact.y / obj->rad) / M_PI;
	}
	else if (obj->property & E_CONE || obj->property & E_CYLINDER)
	{
		if (fabsf(obj->dir.y) > 0.999)
			axis = vec_norm((t_vec){obj->dir.y, 0, 0});
		else
			axis = vec_norm(vec_cross((t_vec){0, 1, 0}, obj->dir));
		if (fabs(vec_dot(norm, obj->dir)) > 0.999)
		{
			_vec_sub(&contact, vec_mul(obj->dir, vec_dot(contact, obj->dir)));
			uv[1] = vec_len(contact) / (obj->rad);
			_vec_norm(&contact);
		}
		else
		{
			uv[1] = vec_dot(contact, obj->dir) / (obj->height);
			_vec_norm(_vec_sub(&contact, vec_mul(obj->dir, vec_dot(contact, obj->dir))));
		}
		tmp = vec_dot(axis, contact);
		if (tmp < -1)
			tmp = -0.99;
		else if (tmp > 1)
			tmp = 0.99;
		if (vec_dot(vec_cross(axis, contact), obj->dir) > 0)
			uv[0] = 0.5 + acosf(tmp) / (2 * M_PI);
		else
			uv[0] = 0.5 - acosf(tmp) / (2 * M_PI);
	}
	else
	{
		// t_vec	u;
		// t_vec	v;

		// u = vec_norm(vec_cross(norm, obj->dir));
		// v = vec_norm(vec_cross(norm, u));
		// u.x * a + v.x * b == contact.x;
		// u.y * a + v.y * b == contact.y;
		// u.z * a + v.z * b == contact.z;

		// (u.x  v.x)(u) = contact.x;
		// (u.y  v.y)(v) = contact.y;
		float	f;
		uv[0] = fabsf(modff(contact.x, &f));
		uv[1] = fabsf(modff(contact.y, &f));
	}
}

// t_color	texture(float *uv, t_texture *texture)
// {
// 	// printf("%f %f\n", uv[0], uv[1]);
// 	return (texture->addr[(int)(uv[0] * (texture->w - 1)) + (int)(texture->h - uv[1] * texture->h - 1) * texture->size_line / sizeof(t_color)]);
// }

void	apply_normal(float uv[2], t_vec *w, t_obj *obj)
{
	t_vec	normal = obj->normal->map[(int)(uv[0] * (obj->normal->w - 1)) + (int)(uv[1] * (obj->normal->h - 1)) * obj->normal->w];
	t_vec	u;
	t_vec	v;

	// printf("normal: %f %f %f\n", normal.x, normal.y, normal.z);
	u = vec_norm(vec_cross(*w, obj->dir));
	v = vec_norm(vec_cross(*w, u));
	_vec_mul(&u, normal.x);
	_vec_mul(w, normal.y);
	_vec_mul(&v, normal.z);
	_vec_add(w, u);
	_vec_add(w, v);
	_vec_norm(w);
}

t_color	set_ambient(t_data *data, t_vec *vector, t_obj *obj)
{
	t_color	color;
	float	uv[2];

	uv[0] = 0;
	uv[1] = 0;
	if (obj->property & E_TEXTURE || obj->property & E_NORMAL)
	{
		set_uv(vec_sub(vector[1], obj->origin), vector[0], obj, uv);
		if (obj->property & E_TEXTURE)
			color = obj->texture->map[(int)(uv[0] * (obj->texture->w - 1)) + (int)(uv[1] * (obj->texture->h - 1)) * obj->texture->w];
		if (obj->property & E_NORMAL)
			apply_normal(uv, vector, obj);
	}
	color.r |= (int)(data->ambient->color.r / 255.0 * data->ambient->ratio);
	color.g |= (int)(data->ambient->color.g / 255.0 * data->ambient->ratio);
	color.b |= (int)(data->ambient->color.b / 255.0 * data->ambient->ratio);
	return (color);
}

t_color	cal_bright(t_data *data, t_vec nor_vec, t_vec con_vec, t_obj *obj)
{
	t_color	color;
	int		i;
	t_vec	bias;
	t_vec	vector[2];

	vector[0] = nor_vec;
	vector[1] = con_vec;
	color = set_ambient(data, vector, obj);
	bias = vec_mul(vector[0], 0.2);
	i = -1;
	while (++i < data->lights->size)
	{
		if (cal_shadow(data, vec_add(vector[1], bias), i) < 0)
			continue ;
		_add_color(&color, get_diffuse(data, vector, obj, i));
		_add_color(&color, get_specular(data, vector, i));
	}
	return (color);
}

//ambient세기 * 물체의 ambient 상수 + (-빛의 diffuse 세기 * 물체의 diffuse 상수 * vec_mul(normal_vec, 입사광))
//+ 빛의 specular 세기 * 물체의 specular 상수 * powf(vec_mul(반사광, camera-objs), 물체의 반짝이는 정도);

