/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_self.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:10:54 by seonghyu          #+#    #+#             */
/*   Updated: 2023/04/20 14:28:40 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_deque.h"

inline t_color	*_add_color(t_color *a, t_color b)
{
	(*a).a = oper_color((*a).a, b.a, E_PLUS);
	(*a).r = oper_color((*a).r, b.r, E_PLUS);
	(*a).g = oper_color((*a).g, b.g, E_PLUS);
	(*a).b = oper_color((*a).b, b.b, E_PLUS);
	return (a);
}

inline t_color	*_mul_color(t_color *a, float b)
{
	(*a).r = oper_color((*a).r, b, E_MUL);
	(*a).g = oper_color((*a).g, b, E_MUL);
	(*a).b = oper_color((*a).b, b, E_MUL);
	return (a);
}

inline t_color	*_sub_color(t_color *a, t_color b)
{
	(*a).a = oper_color((*a).a, b.a, E_SUB);
	(*a).r = oper_color((*a).r, b.r, E_SUB);
	(*a).g = oper_color((*a).g, b.g, E_SUB);
	(*a).b = oper_color((*a).b, b.b, E_SUB);
	return (a);
}

inline t_color	*_dot_color(t_color *a, t_color b)
{
	(*a).a = oper_color((*a).a, b.a, E_DOT);
	(*a).r = oper_color((*a).r, b.r, E_DOT);
	(*a).g = oper_color((*a).g, b.g, E_DOT);
	(*a).b = oper_color((*a).b, b.b, E_DOT);
	return (a);
}
