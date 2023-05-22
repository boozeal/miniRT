/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:09:21 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 17:58:07 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(t_obj *obj, char **strs)
{
	if (!strs[1] || !strs[2])
		exit_msg(1, "Not enough arguments");
	obj->ratio = ft_atof(strs[1]);
	if (obj->ratio < 0.0f || obj->ratio > 1.0f)
		exit_msg(1, "Ambient lighting ratio must be in range [0.0,1.0]");
	obj->color = get_color(strs[2]);
	if (strs[3])
		exit_msg(1, "Too many arguments");
}

void	parse_cam(t_obj *obj, char **strs)
{
	if (!strs[1] || !strs[2] || !strs[3])
		exit_msg(1, "Not enough arguments");
	obj->origin = get_vec(strs[1]);
	obj->dir = get_vec(strs[2]);
	obj->fov = ft_atof(strs[3]);
	if (strs[4])
	{
		obj->aa = ft_atoi(strs[4]);
		if (strs[5])
			exit_msg(1, "Too many arguments");
	}
	else
		obj->aa = 1;
	is_valid_cam(obj);
}

void	parse_plane(t_obj *obj, char **strs)
{
	if (!strs[1] || !strs[2] || !strs[3])
		exit_msg(1, "Not enough arguments");
	obj->origin = get_vec(strs[1]);
	obj->dir = get_vec(strs[2]);
	if (vec_len(obj->dir) < 0.999 || vec_len(obj->dir) > 1.001)
	{
		_vec_norm(&obj->dir);
		printf("Invalid orientation vector: try with \
%f,%f,%f\n", obj->dir.x, obj->dir.y, obj->dir.z);
		exit(1);
	}
	_vec_norm(&obj->dir);
	parse_extra(obj, strs + 3);
}

void	parse_obj1(t_obj *obj, char **strs)
{
	if (!strs[1] || !strs[2] || !strs[3])
		exit_msg(1, "Not enough arguments");
	obj->origin = get_vec(strs[1]);
	obj->rad = ft_atof(strs[2]);
	if (obj->property == E_LIGHT && (obj->ratio < 0.0f || obj->ratio > 1.0f))
		exit_msg(1, "Light brightness ratio must be in range [0.0,1.0]");
	else if (obj->property == E_SPHERE && obj->rad <= 0.0f)
		exit_msg(1, "Diameter must be a non zero positive number");
	obj->dir = (t_vec){0, 1, 0};
	parse_extra(obj, strs + 3);
}

void	parse_obj2(t_obj *obj, char **strs)
{
	if (!strs[1] || !strs[2] || !strs[3])
		exit_msg(1, "Not enough arguments");
	obj->origin = get_vec(strs[1]);
	obj->dir = get_vec(strs[2]);
	if (vec_len(obj->dir) < 0.999 || vec_len(obj->dir) > 1.001)
	{
		_vec_norm(&obj->dir);
		printf("Invalid orientation vector: try with \
%f,%f,%f\n", obj->dir.x, obj->dir.y, obj->dir.z);
		exit(1);
	}
	_vec_norm(&obj->dir);
	obj->rad = ft_atof(strs[3]);
	obj->height = ft_atof(strs[4]);
	if (obj->height < 0.0f || obj->rad <= 0.0f)
		exit_msg(1, "Diameter and height must be a non zero positive number");
	parse_extra(obj, strs + 5);
}
