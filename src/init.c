/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:57:02 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 17:56:17 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minirt.h"

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
		exit_msg(1, "Not enough memory");
	str = get_next_line(fd);
	while (str)
	{
		if (str[0] == '#' || str[0] == '\n')
			free(str);
		else
			ft_vec_push(vec, str_to_obj(str));
		str = get_next_line(fd);
	}
	set_objs(data, vec);
	set_images(data);
	if (!data->viewport.cam || !data->ambient || \
	!data->lights->size || !data->objs->size)
		exit_msg(1, "Not enough elements");
}

void	init_viewport(t_viewport *vp)
{
	const float	width = tanf(vp->cam->fov / 2 * M_PI / 180) * 2;
	const float	height = width / SCREEN_WIDTH * SCREEN_HEIGHT;
	t_vec		uv[2];
	ssize_t		w;
	ssize_t		h;

	vp->w = SCREEN_WIDTH * vp->cam->aa;
	vp->h = SCREEN_HEIGHT * vp->cam->aa;
	vp->rays = malloc(sizeof(t_ray) * vp->w * vp->h);
	vp->pixels = malloc(sizeof(t_color) * vp->w * vp->h);
	if (!vp->rays || !vp->pixels)
		exit_msg(1, "Not enough memory");
	uv[0] = vec_norm(vec_cross_safe(vp->cam->dir, (t_vec){0, 1, 0}));
	uv[1] = vec_norm(vec_cross(uv[0], vp->cam->dir));
	w = -1;
	while (++w < vp->w)
	{
		h = -1;
		while (++h < vp->h)
			vp->rays[w + vp->w * h] = (t_ray){vp->cam->origin, vec_norm(\
			vec_sub(vec_add(vec_add(vec_add(vp->cam->origin, vp->cam->dir), \
			vec_mul(uv[0], (width * (w - vp->w / 2) / vp->w))), vec_mul(\
			uv[1], (height * (h - vp->h / 2) / vp->h))), vp->cam->origin))};
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
		exit_msg(1, "mlx_get_data_addr failed :(");
}
