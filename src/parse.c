/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:55:46 by bok               #+#    #+#             */
/*   Updated: 2023/04/19 17:39:42 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_normal	*get_normal(char *file, void *mlx);
t_texture	*get_texture(char *file, void *mlx);

t_obj	*str_to_obj(char *str)
{
	t_obj	*obj;
	char	**strs;

	obj = ft_calloc(1, sizeof(t_obj));
	strs = ft_split2(str, "\n 	");
	if (!obj || !strs)
		exit_msg(1, "Not enough memory");
	free(str);
	obj->property = get_property(strs[0]);
	if (obj->property == E_AMBIENT)
		parse_ambient(obj, strs);
	else if (obj->property == E_CAM)
		parse_cam(obj, strs);
	else if (obj->property == E_PLANE)
		parse_plane(obj, strs);
	else if (obj->property == E_LIGHT || obj->property == E_SPHERE)
		parse_obj1(obj, strs);
	else if (obj->property == E_CYLINDER || obj->property == E_CONE)
		parse_obj2(obj, strs);
	else
		exit_msg(1, "Invalid element identifier");
	free_split(strs);
	return (obj);
}

void	set_objs(t_data *data, t_vector *vec)
{
	t_obj	*obj;

	while (vec->size)
	{
		obj = ft_vec_pop(vec);
		if (obj->property == E_AMBIENT)
		{
			if (data->ambient)
				exit_msg(1, "multiple ambient :(");
			data->ambient = obj;
		}
		else if (obj->property == E_LIGHT)
			ft_vec_push(data->lights, obj);
		else if (obj->property == E_CAM)
		{
			if (data->viewport.cam)
				exit_msg(1, "multiple cam :( ");
			data->viewport.cam = obj;
		}
		else
			ft_vec_push(data->objs, obj);
	}
	free(vec->content);
	free(vec);
}

void	set_images(t_data *data)
{
	t_obj		*obj;
	ssize_t		i;

	data->texture.key_cmp = (int (*)(void *, void *))ft_strcmp;
	data->normal.key_cmp = (int (*)(void *, void *))ft_strcmp;
	i = 0;
	while (i < data->objs->size)
	{
		obj = data->objs->content[i++];
		if (obj->property & E_TEXTURE)
			set_texture(data, obj);
		if (obj->property & E_NORMAL)
			set_normal(data, obj);
	}
}

void	set_texture(t_data *data, t_obj *obj)
{
	char	*name;

	name = obj->texture_name;
	obj->texture = treemap_get(data->texture.root, name, data->normal.key_cmp);
	if (!obj->texture)
	{
		obj->texture = get_texture(name, data->mlx);
		treemap_insert(&data->texture, name, obj->texture);
	}
	else
		free(name);
}

void	set_normal(t_data *data, t_obj *obj)
{
	char	*name;

	name = obj->normal_name;
	obj->normal = treemap_get(data->normal.root, name, data->normal.key_cmp);
	if (!obj->normal)
	{
		obj->normal = get_normal(name, data->mlx);
		treemap_insert(&data->normal, name, obj->normal);
	}
	else
		free(name);
}
