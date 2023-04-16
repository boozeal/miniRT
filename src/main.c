/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:25:59 by jbok              #+#    #+#             */
/*   Updated: 2023/04/09 19:36:34 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	rt_sphere(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	contact_vec;
	t_vec	normal_vec;

	t = solution_sphere(ray, s, get_det_sphere(ray, s));
	if (t > *dis || t < 0.0f)
		return ((t_color){-1});
	else
	{
		*dis = t;
		contact_vec = vec_add(ray->origin, vec_mul(ray->dir, t));
		normal_vec = vec_norm(vec_sub(contact_vec, s->origin));
		return (cal_bright(data, normal_vec, contact_vec, s));
	}
}

t_color	rt_plane(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	contact_vec;

	t = get_det_plane(ray, s);
	if (t > *dis || t < 0.0f)
		return ((t_color){-1});
	else
	{
		*dis = t;
		contact_vec = vec_add(ray->origin, vec_mul(ray->dir, t));
		return (cal_bright(data, s->dir, contact_vec, s));
	}
}

t_color	rt_subplane_cy(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	contact_vec;

	t = get_det_subplane(ray, s, 0, dis);
	if (t > *dis || t < 0.0f)
		return ((t_color){-1});
	else
	{
		*dis = t;
		contact_vec = vec_add(ray->origin, vec_mul(ray->dir, t));
		return (cal_bright(data, s->dir, contact_vec, s));
	}
}

t_color	rt_subplane_co(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	float	t;
	t_vec	contact_vec;

	t = get_det_subplane(ray, s, 1, dis);
	if (t > *dis || t < 0.0f)
		return ((t_color){-1});
	else
	{
		*dis = t;
		contact_vec = vec_add(ray->origin, vec_mul(ray->dir, t));
		return (cal_bright(data, s->dir, contact_vec, s));
	}
}

t_color	rt_cylinder(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	const float	t = solution_cylinder(ray, s, get_det_cylinder(ray, s), dis);
	t_vec		contact_vec;
	t_vec		normal_vec;
	t_vec		cp;

	if (t == -2)
		return (rt_subplane_cy(data, ray, s, dis));
	if (t > *dis || t < 0.0f)
		return ((t_color){-1});
	else
	{
		*dis = t;
		contact_vec = vec_add(ray->origin, vec_mul(ray->dir, t));
		cp = vec_sub(contact_vec, s->origin);
		normal_vec = vec_norm(vec_sub(cp, \
			vec_mul(s->dir, vec_dot(cp, s->dir))));
		return (cal_bright(data, normal_vec, contact_vec, s));
	}
}

t_color	rt_cone(t_data *data, t_ray *ray, t_obj *s, float *dis)
{
	const float	t = solution_cone(ray, s, get_det_cone(ray, s), dis);
	t_vec		contact_vec;
	t_vec		normal_vec;
	t_vec		cp;

	if (t == -2)
		return (rt_subplane_co(data, ray, s, dis));
	if (t < 0.0f || t > *dis)
		return ((t_color){-1});
	else
	{
		*dis = t;
		contact_vec = vec_add(ray->origin, vec_mul(ray->dir, t));
		cp = vec_sub(contact_vec, s->origin);
		normal_vec = vec_norm(vec_sub(cp, \
			vec_mul(s->dir, vec_dot(cp, s->dir))));
		return (cal_bright(data, normal_vec, contact_vec, s));
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

int	rt_pixels(t_data *data, t_mlx *mlx)
{
	ssize_t	x;
	ssize_t	y;

	(void)mlx;
	x = -1;
	while (++x < data->viewport.w)
	{
		y = -1;
		while (++y < data->viewport.h)
			data->viewport.pixels[x + y * data->viewport.w] = \
			rt_ray(data, data->viewport.rays + x + y * data->viewport.w);
	}
	return (0);
}

t_color	merge_pixels(t_color *piexls, size_t aa)
{
	size_t	x;
	size_t	y;
	size_t	rgb[3];
	t_color	ret;

	x = -1;
	ft_memset(rgb, 0, sizeof(rgb));
	while (++x < aa)
	{
		y = -1;
		while (++y < aa)
		{
			rgb[0] += piexls[x + y * SCREEN_WIDTH * aa].r;
			rgb[1] += piexls[x + y * SCREEN_WIDTH * aa].g;
			rgb[2] += piexls[x + y * SCREEN_WIDTH * aa].b;
		}
	}
	ret.a = 0;
	ret.r = rgb[0] / (aa * aa);
	ret.g = rgb[1] / (aa * aa);
	ret.b = rgb[2] / (aa * aa);
	return (ret);
}

int	downscale(t_mlx *mlx, t_data *data)
{
	size_t	x;
	size_t	y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
			mlx->addr[x + (SCREEN_HEIGHT - 1 - y) * mlx->line_length / \
			sizeof(t_color)] = merge_pixels(data->viewport.pixels + x * \
			data->viewport.cam->aa + y * SCREEN_WIDTH * data->viewport.\
			cam->aa * data->viewport.cam->aa, data->viewport.cam->aa);
	}
	return (0);
}

int	rt_pixels_multi(t_data *data);

int	mlx_refresh(t_mlx *mlx, t_data *data)
{
	// rt_pixels(data, mlx);
	rt_pixels_multi(data);
	downscale(mlx, data);
	free(data->viewport.rays);
	free(data->viewport.pixels);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image, 0, 0);
	printf("refresh\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_mlx	mlx;

	if (argc != 2 || ft_strncmp(".rt", argv[1] + ft_strlen(argv[1]) - 3, -1))
	{
		printf("usage: %s *.rt", argv[0]);
		return (1);
	}
	ft_memset(&mlx, 0, sizeof(mlx));
	init_mlx(&mlx, argv[0] + 2);
	ft_memset(&data, 0, sizeof(data));
	data.mlx = mlx.mlx;
	init_data(&data, argv[1]);
	init_viewport(&data.viewport);
	mlx_hook(mlx.win, 2, 0, key_press, &mlx);
	mlx_hook(mlx.win, 17, 0, window_closed, &mlx);
	mlx_refresh(&mlx, &data);
	mlx_loop(mlx.mlx);
}
