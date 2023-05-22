/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 20:26:40 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 16:45:57 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		downscale(t_mlx *mlx, t_data *data);
t_color	merge_pixels(t_color *piexls, size_t aa);

void	mlx_refresh(t_mlx *mlx, t_data *data)
{
	rt_pixels_multi(data);
	downscale(mlx, data);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image, 0, 0);
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
