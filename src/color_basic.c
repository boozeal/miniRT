/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:54:53 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/20 17:59:00 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_deque.h"

inline t_color	add_color(t_color a, t_color b)
{
	t_color	c;

	c.a = oper_color(a.a, b.a, E_PLUS);
	c.r = oper_color(a.r, b.r, E_PLUS);
	c.g = oper_color(a.g, b.g, E_PLUS);
	c.b = oper_color(a.b, b.b, E_PLUS);
	return (c);
}

inline t_color	mul_color(t_color a, float b)
{
	t_color	c;

	c.a = a.a;
	c.r = oper_color(a.r, b, E_MUL);
	c.g = oper_color(a.g, b, E_MUL);
	c.b = oper_color(a.b, b, E_MUL);
	return (c);
}

inline t_color	dot_color(t_color a, t_color b)
{
	t_color	c;

	c.a = oper_color(a.a, b.a, E_DOT);
	c.r = oper_color(a.r, b.r, E_DOT);
	c.g = oper_color(a.g, b.g, E_DOT);
	c.b = oper_color(a.b, b.b, E_DOT);
	return (c);
}

inline float	oper_color(unsigned char a, float b, int flag)
{
	float	temp;

	if (flag == E_PLUS)
		temp = a + b;
	else if (flag == E_SUB)
		temp = a - b;
	else if (flag == E_MUL)
		temp = a * b;
	else if (flag == E_DOT)
		temp = a * b / 255;
	else
		temp = a / b;
	if (temp >= 255)
		temp = 255;
	else if (temp < 0)
		temp = 0;
	return (temp);
}
