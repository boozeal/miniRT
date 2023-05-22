/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:00:25 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 18:11:50 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_num(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	get_property(char *str)
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

	if (!check_valid_str(str))
		exit_msg(1, "Invalid vector element");
	strs = ft_split(str, ',');
	if (!strs)
		exit_msg(1, "Not enough memory");
	if (!strs[0] || !strs[1] || !strs[2] || strs[3])
		exit_msg(1, "Invalid vector element");
	vec.x = ft_atof(strs[0]);
	vec.y = ft_atof(strs[1]);
	vec.z = ft_atof(strs[2]);
	free_split(strs);
	return (vec);
}

t_color	get_color(char *str)
{
	char			**strs;
	t_color			color;
	unsigned int	tmp[3];

	if (!check_valid_str(str))
		exit_msg(1, "Invalid color element");
	strs = ft_split(str, ',');
	if (!strs)
		exit_msg(1, "Not enough memory");
	if (!strs[0] || !strs[1] || !strs[2] || strs[3])
		exit_msg(1, "Invalid color element");
	if (!is_num(strs[0]) || !is_num(strs[1]) || !is_num(strs[2]))
		exit_msg(1, "Invalid color element");
	color.a = 0;
	tmp[0] = ft_atoi(strs[0]);
	tmp[1] = ft_atoi(strs[1]);
	tmp[2] = ft_atoi(strs[2]);
	if (tmp[0] > 255 || tmp[1] > 255 || tmp[2] > 255)
		exit_msg(1, "Invalid color element");
	color.r = tmp[0];
	color.g = tmp[1];
	color.b = tmp[2];
	free_split(strs);
	return (color);
}
