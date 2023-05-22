/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treemap_traversal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:05:10 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 16:40:31 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_treemap.h"

void	treemap_preorder(t_treemap_node *node, void (*f)(t_treemap_node *node))
{
	if (!node)
		return ;
	f(node);
	treemap_preorder(node->left, f);
	treemap_preorder(node->right, f);
}

void	treemap_inorder(t_treemap_node *node, void (*f)(t_treemap_node *node))
{
	if (!node)
		return ;
	treemap_inorder(node->left, f);
	f(node);
	treemap_inorder(node->right, f);
}

void	treemap_postorder(t_treemap_node *node, void (*f)(t_treemap_node *node))
{
	if (!node)
		return ;
	treemap_postorder(node->left, f);
	treemap_postorder(node->right, f);
	f(node);
}

size_t	treemap_get_size(t_treemap_node *node)
{
	if (!node)
		return (0);
	return (treemap_get_size(node->left) + treemap_get_size(node->right) + 1);
}
