/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:10:54 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/04 19:20:32 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_deque.h"

t_color	add_color(t_color a, t_color b)
{
	t_color	c;

	c.a = oper_color(a.a, b.a, E_PLUS);
	c.r = oper_color(a.r, b.r, E_PLUS);
	c.g = oper_color(a.g, b.g, E_PLUS);
	c.b = oper_color(a.b, b.b, E_PLUS);
	return (c);
}

t_color	*_add_color(t_color *a, t_color b)
{
	(*a).a = oper_color((*a).a, b.a, E_PLUS);
	(*a).r = oper_color((*a).r, b.r, E_PLUS);
	(*a).g = oper_color((*a).g, b.g, E_PLUS);
	(*a).b = oper_color((*a).b, b.b, E_PLUS);
	return (a);
}

t_color	mul_color(t_color a, float b)
{
	t_color	c;

	c.a = a.a;
	c.r = oper_color(a.r, b, E_MUL);
	c.g = oper_color(a.g, b, E_MUL);
	c.b = oper_color(a.b, b, E_MUL);
	return (c);
}

t_color	*_mul_color(t_color *a, float b)
{
	(*a).r = oper_color((*a).r, b, E_MUL);
	(*a).g = oper_color((*a).g, b, E_MUL);
	(*a).b = oper_color((*a).b, b, E_MUL);
	return (a);
}

t_color	*_sub_color(t_color *a, t_color b)
{
	(*a).a = oper_color((*a).a, b.a, E_SUB);
	(*a).r = oper_color((*a).r, b.r, E_SUB);
	(*a).g = oper_color((*a).g, b.g, E_SUB);
	(*a).b = oper_color((*a).b, b.b, E_SUB);
	return (a);
}

t_color	dot_color(t_color a, t_color b)
{
	t_color	c;

	c.a = oper_color(a.a, b.a, E_DOT);
	c.r = oper_color(a.r, b.r, E_DOT);
	c.g = oper_color(a.g, b.g, E_DOT);
	c.b = oper_color(a.b, b.b, E_DOT);
	return (c);
}

t_color	*_dot_color(t_color *a, t_color b)
{
	(*a).a = oper_color((*a).a, b.a, E_DOT);
	(*a).r = oper_color((*a).r, b.r, E_DOT);
	(*a).g = oper_color((*a).g, b.g, E_DOT);
	(*a).b = oper_color((*a).b, b.b, E_DOT);
	return (a);
}

float	oper_color(unsigned char a, float b, int flag)
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
