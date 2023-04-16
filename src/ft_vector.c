/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:33:45 by jbok              #+#    #+#             */
/*   Updated: 2023/04/03 18:12:26 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	*ft_realloc(void *src, size_t src_size, size_t dst_size)
{
	void	*ptr;

	if (src_size >= dst_size)
		return (src);
	ptr = malloc(dst_size);
	if (!ptr)
		return (0);
	ptr = ft_memcpy(ptr, src, src_size);
	free(src);
	return (ptr);
}

t_vector	*ft_vecnew(void)
{
	t_vector	*ptr;

	ptr = malloc(sizeof(t_vector));
	if (!ptr)
		return (0);
	ptr->content = malloc(sizeof(void *) * VEC_RESERVE_SIZE);
	if (!(ptr->content))
	{
		free(ptr);
		return (0);
	}
	ptr->size = 0;
	ptr->capacity = VEC_RESERVE_SIZE;
	return (ptr);
}

ssize_t	ft_vec_push(t_vector *vec, void *content)
{
	ssize_t	cap;

	if (vec->size == vec->capacity)
	{
		cap = vec->capacity + vec->capacity / 2;
		vec->content = ft_realloc(vec->content, sizeof(void *) * vec->size, \
		sizeof(void *) * (vec->capacity + vec->capacity / 2));
		if (!(vec->content))
			return (-1);
		vec->capacity = cap;
	}
	(vec->content)[vec->size++] = content;
	return (vec->size);
}

int	ft_vec_reserve(t_vector *vec, ssize_t size)
{
	vec->content = ft_realloc(vec->content, sizeof(void *) * vec->size, \
	sizeof(void *) * size);
	if (!(vec->content))
		return (-1);
	vec->capacity = size;
	return (0);
}

void	*ft_vec_pop(t_vector *vec)
{
	if (vec->size == 0)
		return (0);
	else
		return ((vec->content)[--(vec->size)]);
}
