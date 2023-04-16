/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:09:21 by jbok              #+#    #+#             */
/*   Updated: 2023/04/09 20:19:26 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_vec(char *str);
t_color	get_color(char *str);

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
			ptr = tmp->addr + i + (h - j - 1) * tmp->size_line / sizeof(t_color);
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

	file = ft_strtrim(file, " \n	");
	ret = ft_calloc(1, sizeof(t_normal));
	if (!ret)
		exit_msg(1, "malloc failed :(");
	tmp.img = mlx_xpm_file_to_image(mlx, file, &ret->w, &ret->h);
	if (!tmp.img)
		exit_msg(1, "xpm_to_image failed :(");
	free(file);
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

	file = ft_strtrim(file, " \n	");
	ret = ft_calloc(1, sizeof(t_texture));
	if (!ret)
		exit_msg(1, "malloc failed :(");
	// ret->img = mlx_png_file_to_image(mlx, file, &ret->w, &ret->h);
	tmp.img = mlx_xpm_file_to_image(mlx, file, &ret->w, &ret->h);
	if (!tmp.img)
		exit_msg(1, "xpm_to_image failed :(");
	free(file);
	tmp.addr = (t_color *)mlx_get_data_addr(tmp.img, \
	&tmp.bits_per_pixel, &tmp.size_line, &tmp.endian);
	if (!tmp.addr)
		exit_msg(1, "get_data_addr failed :(");
	ret->map = img_to_color(&tmp, ret->w, ret->h);
	mlx_destroy_image(mlx, tmp.img);
	return (ret);
}

void	parse_texture(t_obj *obj, char **strs, void *mlx)
{
	if (!strs[0])
		exit_msg(1, "invalid parse arg");
	else if (!ft_strncmp("T", strs[0], -1))
	{
		obj->property |= E_TEXTURE;
		obj->texture = get_texture(strs[1], mlx);
	}
	else
		obj->color = get_color(strs[0]);
	if (strs[1] && strs[2] && !ft_strncmp("N", strs[2], -1))
	{
		obj->property |= E_NORMAL;
		obj->normal = get_normal(strs[3], mlx);
	}
}

t_obj	*parse_ambient(enum e_property property, char **strs)
{
	t_obj	*obj;
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	if (i != 3)
		exit_msg(1, "ambient");
	obj = ft_calloc(1, sizeof(t_obj));
	if (!obj)
		exit_msg(1, "calloc");
	obj->property = property;
	obj->ratio = ft_atof(strs[1]);
	obj->color = get_color(strs[2]);
	while (i--)
		free(strs[i]);
	free(strs);
	return (obj);
}

t_obj	*parse_cam(enum e_property property, char **strs)
{
	t_obj	*obj;
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	if (i < 4 || i > 5)
		exit_msg(1, "cam");
	obj = ft_calloc(1, sizeof(t_obj));
	if (!obj)
		exit_msg(1, "calloc");
	obj->property = property;
	obj->origin = get_vec(strs[1]);
	obj->dir = vec_norm(get_vec(strs[2]));
	obj->fov = ft_atof(strs[3]);
	if (i == 5)
		obj->aa = ft_atoi(strs[4]);
	else
		obj->aa = 1;
	while (i--)
		free(strs[i]);
	free(strs);
	return (obj);
}

t_obj	*parse_plane(enum e_property property, char **strs, void *mlx)
{
	t_obj	*obj;
	size_t	i;

	obj = ft_calloc(1, sizeof(t_obj));
	if (!obj)
		exit_msg(1, "calloc");
	obj->property = property;
	obj->origin = get_vec(strs[1]);
	obj->dir = vec_norm(get_vec(strs[2]));
	parse_texture(obj, strs + 3, mlx);
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (obj);
}

t_obj	*parse_obj1(enum e_property property, char **strs, void *mlx)
{
	t_obj	*obj;
	size_t	i;

	obj = ft_calloc(1, sizeof(t_obj));
	if (!obj)
		exit_msg(1, "calloc");
	obj->property = property;
	obj->origin = get_vec(strs[1]);
	obj->rad = ft_atof(strs[2]);
	obj->dir = (t_vec){0, 1, 0};
	parse_texture(obj, strs + 3, mlx);
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (obj);
}

t_obj	*parse_obj2(enum e_property property, char **strs, void *mlx)
{
	t_obj	*obj;
	size_t	i;

	obj = ft_calloc(1, sizeof(t_obj));
	if (!obj)
		exit_msg(1, "calloc");
	obj->property = property;
	obj->origin = get_vec(strs[1]);
	obj->dir = vec_norm(get_vec(strs[2]));
	obj->rad = ft_atof(strs[3]);
	obj->height = ft_atof(strs[4]);
	parse_texture(obj, strs + 5, mlx);
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (obj);
}
