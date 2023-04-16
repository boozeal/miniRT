/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:00:25 by jbok              #+#    #+#             */
/*   Updated: 2023/04/06 19:10:47 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

enum e_property	get_property(char *str)
{
	if (!ft_strncmp("A", str, -1))
		return (E_AMBIENT);
	else if (!ft_strncmp("C", str, -1))
		return (E_CAM);
	else if (!ft_strncmp("L", str, -1))
		return (E_LIGHT);
	else if (!ft_strncmp("sp", str, -1))
		return (E_SPHERE);
	else if (!ft_strncmp("pl", str, -1))
		return (E_PLANE);
	else if (!ft_strncmp("cy", str, -1))
		return (E_CYLINDER);
	else if (!ft_strncmp("co", str, -1))
		return (E_CONE);
	else
		return (E_ERROR);
}

t_vec	get_vec(char *str)
{
	char	**strs;
	t_vec	vec;
	size_t	i;

	if (!check_valid_str(str))
		exit_msg(1, "invalid parse arg");
	strs = ft_split(str, ',');
	if (!strs)
		exit_msg(1, "malloc failed :(");
	i = 0;
	while (strs[i])
		i++;
	if (i != 3)
		exit_msg(1, "invalid parse arg");
	vec.x = ft_atof(strs[0]);
	free(strs[0]);
	vec.y = ft_atof(strs[1]);
	free(strs[1]);
	vec.z = ft_atof(strs[2]);
	free(strs[2]);
	free(strs);
	return (vec);
}

t_color	get_color(char *str)
{
	char	**strs;
	t_color	color;
	size_t	i;

	if (!check_valid_str(str))
		exit_msg(1, "invalid parse arg");
	strs = ft_split(str, ',');
	if (!strs)
		exit_msg(1, "malloc failed :(");
	i = 0;
	while (strs[i])
		i++;
	if (i != 3)
		exit_msg(1, "invalid parse arg");
	color.a = 0;
	color.r = ft_atoi(strs[0]);
	free(strs[0]);
	color.g = ft_atoi(strs[1]);
	free(strs[1]);
	color.b = ft_atoi(strs[2]);
	free(strs[2]);
	free(strs);
	return (color);
}
