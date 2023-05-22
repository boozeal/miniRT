/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:42:26 by jbok              #+#    #+#             */
/*   Updated: 2023/04/19 22:01:43 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*img_to_color(t_image *tmp, int w, int h)
{
	t_color	*ptr;
	t_color	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(t_vec) * w * h);
	if (!ret)
		exit_msg(1, "malloc failed :(");
	i = -1;
	while (++i < w)
	{
		j = -1;
		while (++j < h)
		{
			ptr = tmp->addr + i + (h - j - 1) * \
			tmp->size_line / sizeof(t_color);
			(ret + i + j * w)->a = 0;
			(ret + i + j * w)->r = ptr->r;
			(ret + i + j * w)->g = ptr->g;
			(ret + i + j * w)->b = ptr->b;
		}
	}
	return (ret);
}

t_vec	*img_to_vec(t_image *tmp, int w, int h)
{
	t_vec	*ret;
	int		i;
	int		j;
	t_color	*color;
	t_vec	*vec;

	ret = malloc(sizeof(t_vec) * w * h);
	if (!ret)
		exit_msg(1, "malloc failed :(");
	i = -1;
	while (++i < w)
	{
		j = -1;
		while (++j < h)
		{
			color = tmp->addr + i + (h - j - 1) * \
			tmp->size_line / sizeof(t_color);
			vec = ret + i + j * w;
			vec->x = (color->r / 255.0 - 0.5) * 2;
			vec->y = (color->b / 255.0 - 0.5) * 2;
			vec->z = (color->g / 255.0 - 0.5) * 2;
			_vec_norm(vec);
		}
	}
	return (ret);
}

t_normal	*get_normal(char *file, void *mlx)
{
	t_normal	*ret;
	t_image		tmp;

	ret = ft_calloc(1, sizeof(t_normal));
	if (!ret)
		exit_msg(1, "malloc failed :(");
	tmp.img = mlx_xpm_file_to_image(mlx, file, &ret->w, &ret->h);
	if (!tmp.img)
		exit_msg(1, "xpm_to_image failed :(");
	tmp.addr = (t_color *)mlx_get_data_addr(tmp.img, \
	&tmp.bits_per_pixel, &tmp.size_line, &tmp.endian);
	if (!tmp.addr)
		exit_msg(1, "get_data_addr failed :(");
	ret->map = img_to_vec(&tmp, ret->w, ret->h);
	mlx_destroy_image(mlx, tmp.img);
	return (ret);
}

t_texture	*get_texture(char *file, void *mlx)
{
	t_image		tmp;
	t_texture	*ret;

	ret = ft_calloc(1, sizeof(t_texture));
	if (!ret)
		exit_msg(1, "Not enugh memory");
	tmp.img = mlx_xpm_file_to_image(mlx, file, &ret->w, &ret->h);
	if (!tmp.img)
		exit_msg(1, "xpm_to_image failed :(");
	tmp.addr = (t_color *)mlx_get_data_addr(tmp.img, \
	&tmp.bits_per_pixel, &tmp.size_line, &tmp.endian);
	if (!tmp.addr)
		exit_msg(1, "get_data_addr failed :(");
	ret->map = img_to_color(&tmp, ret->w, ret->h);
	mlx_destroy_image(mlx, tmp.img);
	return (ret);
}

void	parse_extra(t_obj *obj, char **strs)
{
	if (!ft_strncmp("-T", strs[0], 2))
	{
		obj->property |= E_TEXTURE;
		obj->texture_name = ft_strdup(strs[0] + 2);
	}
	else
		obj->color = get_color(strs[0]);
	if (!strs[1])
		return ;
	else if (!ft_strncmp("-N", strs[1], 2))
	{
		obj->property |= E_NORMAL;
		obj->normal_name = ft_strdup(strs[1] + 2);
	}
	else
		exit_msg(1, "Too many arguments in line");
}
