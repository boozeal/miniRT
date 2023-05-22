/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:48:32 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 18:38:07 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	del_unnecessary(t_data *data)
{
	ssize_t	i;

	del_viewport(&data->viewport);
	free(data->ambient);
	i = 0;
	while (i < data->objs->size)
		free(data->objs->content[i++]);
	free(data->objs->content);
	free(data->objs);
	i = 0;
	while (i < data->lights->size)
		free(data->lights->content[i++]);
	free(data->lights->content);
	free(data->lights);
	treemap_postorder(data->texture.root, &del_texture);
	treemap_postorder(data->normal.root, &del_normal);
}

void	del_viewport(t_viewport *viewport)
{
	free(viewport->cam);
	free(viewport->rays);
	free(viewport->pixels);
}

void	del_texture(t_treemap_node *node)
{
	t_texture	*texture;

	texture = node->val;
	free(node->key);
	free(texture->map);
	free(texture);
}

void	del_normal(t_treemap_node *node)
{
	t_normal	*normal;

	normal = node->val;
	free(node->key);
	free(normal->map);
	free(normal);
	free(node);
}

void	del_multi(t_multi *multi)
{
	free(multi->threads);
	pthread_mutex_destroy(&multi->task_stack_mutex);
	free(multi->task_stack->content);
	free(multi->task_stack);
}
