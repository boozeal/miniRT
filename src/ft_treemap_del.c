/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treemap_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 00:00:52 by bok               #+#    #+#             */
/*   Updated: 2023/02/03 21:40:43 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_treemap.h"
#include "libft.h"

static t_treemap_node	*__treemap_del(t_treemap_node *node, void *key, \
int (*key_cmp)(void *, void *));
static t_treemap_node	*__treemap_del_2child(t_treemap_node *node, \
int (*key_cmp)(void *, void *));

void	treemap_del(t_treemap *map, void *key)
{
	map->root = __treemap_del(map->root, key, map->key_cmp);
}

static t_treemap_node	*__treemap_del(t_treemap_node *node, void *key, \
int (*key_cmp)(void *, void *))
{
	int				cmp;

	if (!node)
		return (0);
	cmp = key_cmp(key, node->key);
	if (cmp < 0)
		node->left = __treemap_del(node->left, key, key_cmp);
	else if (cmp > 0)
		node->right = __treemap_del(node->right, key, key_cmp);
	else
		node = __treemap_del_2child(node, key_cmp);
	return (treemap_ballance(node));
}

static t_treemap_node	*__treemap_del_2child(t_treemap_node *node, \
int (*key_cmp)(void *, void *))
{
	t_treemap_node	*tmp;

	tmp = node;
	if (!(node->left))
	{
		node = node->right;
		treemap_del_node(tmp);
	}
	else if (!(node->right))
	{
		node = node->left;
		treemap_del_node(tmp);
	}
	else
	{
		tmp = node->right;
		while (tmp->left)
			tmp = tmp->left;
		free(node->key);
		node->key = ft_strdup(tmp->key);
		free(node->val);
		node->val = ft_strdup(tmp->val);
		node->right = __treemap_del(node->right, tmp->key, key_cmp);
	}
	return (node);
}
