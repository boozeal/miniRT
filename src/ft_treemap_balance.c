/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treemap_balance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:23:43 by bok               #+#    #+#             */
/*   Updated: 2023/02/03 21:25:19 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_treemap.h"

static t_treemap_node	*treemap_ll(t_treemap_node *node);
static t_treemap_node	*treemap_rr(t_treemap_node *node);
static t_treemap_node	*treemap_lr(t_treemap_node *node);
static t_treemap_node	*treemap_rl(t_treemap_node *node);

t_treemap_node	*treemap_ballance(t_treemap_node *node)
{
	int	bf;

	if (!node)
		return (0);
	bf = treemap_get_balancefactor(node);
	if (bf > 1)
	{
		bf = treemap_get_balancefactor(node->left);
		if (bf > 0)
			node = treemap_ll(node);
		else
			node = treemap_lr(node);
	}
	else if (bf < -1)
	{
		bf = treemap_get_balancefactor(node->right);
		if (bf < 0)
			node = treemap_rr(node);
		else
			node = treemap_rl(node);
	}
	return (node);
}

static t_treemap_node	*treemap_ll(t_treemap_node *node)
{
	t_treemap_node	*child;

	if (!node)
		return (0);
	child = node->left;
	node->left = child->right;
	child->right = node;
	return (child);
}

t_treemap_node	*treemap_rr(t_treemap_node *node)
{
	t_treemap_node	*child;

	if (!node)
		return (0);
	child = node->right;
	node->right = child->left;
	child->left = node;
	return (child);
}

t_treemap_node	*treemap_lr(t_treemap_node *node)
{
	if (!node)
		return (0);
	node->left = treemap_rr(node->left);
	return (treemap_ll(node));
}

t_treemap_node	*treemap_rl(t_treemap_node *node)
{
	if (!node)
		return (0);
	node->right = treemap_ll(node->right);
	return (treemap_rr(node));
}
