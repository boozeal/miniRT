/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treemap_insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:11:29 by bok               #+#    #+#             */
/*   Updated: 2023/02/03 16:52:47 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_treemap.h"

static t_treemap_node	*__treemap_insert(t_treemap_node *node, void *key, \
void *val, int (*key_cmp)(void *, void *));

void	treemap_insert(t_treemap *map, void *key, void *val)
{
	map->root = __treemap_insert(map->root, key, val, map->key_cmp);
}

static t_treemap_node	*__treemap_insert(t_treemap_node *node, void *key, \
void *val, int (*key_cmp)(void *, void *))
{
	int	cmp;

	if (!node)
		return (treemap_new_node(key, val));
	cmp = key_cmp(key, node->key);
	if (!cmp)
	{
		free(key);
		if (!val)
			return (node);
		free(node->val);
		node->val = val;
		return (node);
	}
	if (cmp < 0)
		node->left = __treemap_insert(node->left, key, val, key_cmp);
	else if (cmp > 0)
		node->right = __treemap_insert(node->right, key, val, key_cmp);
	return (treemap_ballance(node));
}
