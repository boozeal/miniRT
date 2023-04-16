/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:55:46 by bok               #+#    #+#             */
/*   Updated: 2023/04/08 18:58:30 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

enum e_property	get_property(char *str);
t_obj			*parse_ambient(enum e_property property, char **strs);
t_obj			*parse_cam(enum e_property property, char **strs);
t_obj			*parse_plane(enum e_property property, char **strs, void *mlx);
t_obj			*parse_obj1(enum e_property property, char **strs, void *mlx);
t_obj			*parse_obj2(enum e_property property, char **strs, void *mlx);

t_obj	*str_to_obj(char *str, void *mlx)
{
	char			**strs;
	enum e_property	property;

	strs = ft_split(str, ' ');
	if (!strs)
		exit_msg(1, "malloc failed :(");
	free(str);
	property = get_property(strs[0]);
	if (property == E_AMBIENT)
		return (parse_ambient(property, strs));
	else if (property == E_CAM)
		return (parse_cam(property, strs));
	else if (property == E_PLANE)
		return (parse_plane(property, strs, mlx));
	else if (property == E_LIGHT || property == E_SPHERE)
		return (parse_obj1(property, strs, mlx));
	else if (property == E_CYLINDER || property == E_CONE)
		return (parse_obj2(property, strs, mlx));
	else
		exit_msg(1, "get_prop");
	return (0);
}

void	apply_objs(t_data *data, t_vector *vec)
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
