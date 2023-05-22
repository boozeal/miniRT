/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treemap.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:50:16 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 16:42:55 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREEMAP_H
# define FT_TREEMAP_H

# include <stdlib.h>

typedef struct s_treemap_node	t_treemap_node;

typedef struct s_treemap_node
{
	void			*key;
	void			*val;
	t_treemap_node	*left;
	t_treemap_node	*right;
}	t_treemap_node;

typedef struct s_treemap
{
	t_treemap_node	*root;
	int				(*key_cmp)(void *, void *);
}	t_treemap;

t_treemap_node	*treemap_new_node(void *key, void *val);
void			treemap_del_node(t_treemap_node	*node);
int				treemap_get_depth(t_treemap_node *node);
size_t			treemap_get_size(t_treemap_node *node);
int				treemap_get_balancefactor(t_treemap_node *node);
t_treemap_node	*treemap_ballance(t_treemap_node *node);

void			treemap_insert(t_treemap *map, void *key, void *val);
void			treemap_del(t_treemap *map, void *key);
void			*treemap_get(t_treemap_node *node, void *key, \
int (*key_cmp)(void *, void *));

void			treemap_preorder(t_treemap_node *node, \
void (*f)(t_treemap_node *node));
void			treemap_inorder(t_treemap_node *node, \
void (*f)(t_treemap_node *node));
void			treemap_postorder(t_treemap_node *node, \
void (*f)(t_treemap_node *node));

#endif
