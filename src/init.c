/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:57:02 by jbok              #+#    #+#             */
/*   Updated: 2023/04/09 19:55:01 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minirt.h"

void	apply_objs(t_data *data, t_vector *vec);
t_obj	*str_to_obj(char *str, void *mlx);

void	init_data(t_data *data, char *file)
{
	const int	fd = open(file, O_RDONLY);
	t_vector	*vec;
	char		*str;

	if (fd < 0)
		exit_msg(1, "open failed :(");
	data->lights = ft_vecnew();
	data->objs = ft_vecnew();
	vec = ft_vecnew();
	if (!data->lights || !data->objs || !vec)
		exit_msg(1, "malloc failed :(");
	str = get_next_line(fd);
	while (str)
	{
		if (str[0] == '#' || str[0] == '\n')
			free(str);
		else
			ft_vec_push(vec, str_to_obj(str, data->mlx));
		str = get_next_line(fd);
	}
	apply_objs(data, vec);
	if (!data->viewport.cam || !data->ambient || \
	!data->lights->size || !data->objs->size)
		exit_msg(1, "not enough objs :(");
}

void	init_viewport(t_viewport *vp)
{
	ssize_t		w;
	ssize_t		h;
	const float	width = tanf(vp->cam->fov * M_PI / 360) * 2;
	const float	height = width / SCREEN_WIDTH * SCREEN_HEIGHT;

	vp->w = SCREEN_WIDTH * vp->cam->aa;
	vp->h = SCREEN_HEIGHT * vp->cam->aa;
	if (vp->w / SCREEN_WIDTH != vp->cam->aa || vp->h / SCREEN_HEIGHT \
	!= vp->cam->aa || SSIZE_MAX / vp->h < vp->w * (ssize_t) sizeof(t_ray))
		exit_msg(1, "too large AA scale");
	vp->rays = malloc(sizeof(t_ray) * vp->w * vp->h);
	vp->pixels = malloc(sizeof(t_color) * vp->w * vp->h);
	if (!vp->rays || !vp->pixels)
		exit_msg(1, "malloc failed :(");
	vp->horizonal = vec_norm(vec_cross(vp->cam->dir, (t_vec){0, 1, 0}));
	vp->vertical = vec_norm(vec_cross(vp->horizonal, vp->cam->dir));
	w = -1;
	while (++w < vp->w)
	{
		h = -1;
		while (++h < vp->h)
			vp->rays[w + vp->w * h] = (t_ray){vp->cam->origin, vec_norm(\
			vec_sub(vec_add(vec_add(vec_add(vp->cam->origin, vp->cam->dir), \
			vec_mul(vp->horizonal, (width * (w - vp->w / 2) / vp->w))), \
			vec_mul(vp->vertical, (height * (h - vp->h / 2) / vp->h))), \
			vp->cam->origin))};
	}
}

void	init_mlx(t_mlx *mlx, char *name)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit_msg(1, "mlx_init failed :(");
	mlx->win = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, name);
	if (!mlx->win)
		exit_msg(1, "mlx_new_window failed :(");
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx->image = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!mlx->image)
		exit_msg(1, "mlx_new_image failed :(");
	mlx->addr = (t_color *)mlx_get_data_addr(mlx->image, \
	&mlx->bit_per_pixel, &mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		exit_msg(1, "mlx_get_data_addr :(");
}
