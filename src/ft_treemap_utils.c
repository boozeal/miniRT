/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treemap_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:28:41 by bok               #+#    #+#             */
/*   Updated: 2023/02/03 20:35:33 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_treemap.h"

t_treemap_node	*treemap_new_node(void *key, void *val)
{
	t_treemap_node	*node;

	node = malloc(sizeof(t_treemap_node));
	if (!node)
		exit(1);
	*node = (t_treemap_node){key, val, 0, 0};
	return (node);
}

void	treemap_del_node(t_treemap_node	*node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->val);
	free(node);
}

int	treemap_get_depth(t_treemap_node *node)
{
	int	left;
	int	right;

	if (!node)
		return (0);
	left = treemap_get_depth(node->left);
	right = treemap_get_depth(node->right);
	if (left < right)
		return (right + 1);
	return (left + 1);
}

int	treemap_get_balancefactor(t_treemap_node *node)
{
	if (!node)
		return (0);
	return (treemap_get_depth(node->left) - treemap_get_depth(node->right));
}

void	*treemap_get(t_treemap_node *node, void *key, \
int (*key_cmp)(void *, void *))
{
	int	cmp;

	if (!node)
		return (0);
	cmp = key_cmp(key, node->key);
	if (!cmp)
		return (node->val);
	else if (cmp < 0)
		return (treemap_get(node->left, key, key_cmp));
	else
		return (treemap_get(node->right, key, key_cmp));
}
