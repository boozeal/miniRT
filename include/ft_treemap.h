/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treemap.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:50:16 by jbok              #+#    #+#             */
/*   Updated: 2023/02/04 23:08:34 by bok              ###   ########.fr       */
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
void (*f)(void *, void *));
void			treemap_inorder(t_treemap_node *node, \
void (*f)(void *, void *));
void			treemap_postorder(t_treemap_node *node, \
void (*f)(void *, void *));

#endif
