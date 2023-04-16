/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:10:42 by jbok              #+#    #+#             */
/*   Updated: 2023/03/23 14:51:26 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_deque.h"

static t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*ptr;

	ptr = (t_dlist *)malloc(sizeof(t_dlist));
	if (!ptr)
		exit(1);
	ptr -> content = content;
	ptr -> prev = 0;
	ptr -> next = 0;
	return (ptr);
}

size_t	ft_pushback(t_deque *deque, void *content)
{
	if (!(deque->size) || !(deque->rear))
	{
		deque->rear = ft_dlstnew(content);
		deque->front = deque->rear;
		if (deque->front)
			deque->size += 1;
		else
			exit(1);
	}
	else
	{
		deque->rear->next = ft_dlstnew(content);
		if (deque->rear->next)
		{
			deque->rear->next->prev = deque->rear;
			deque->rear = deque->rear->next;
			deque->size += 1;
		}
		else
			exit(1);
	}
	return (deque->size);
}

size_t	ft_pushfront(t_deque *deque, void *content)
{
	if (!(deque->size) || !(deque->front))
	{
		deque->front = ft_dlstnew(content);
		deque->rear = deque->front;
		if (deque->front)
			deque->size += 1;
		else
			exit(1);
	}
	else
	{
		deque->front->prev = ft_dlstnew(content);
		if (deque->front->prev)
		{
			deque->front->prev->next = deque->front;
			deque->front = deque->front->prev;
			deque->size += 1;
		}
		else
			exit(1);
	}
	return (deque->size);
}

void	*ft_popback(t_deque *deque)
{
	void	*content;
	t_dlist	*tmp;

	if (!(deque->size) || !(deque->rear))
		return (content = 0);
	else
	{
		tmp = deque->rear;
		content = tmp->content;
		deque->rear = deque->rear->prev;
		if (deque->rear)
			deque->rear->next = 0;
		free(tmp);
		deque->size -= 1;
	}
	return (content);
}

void	*ft_popfront(t_deque *deque)
{
	void	*content;
	t_dlist	*tmp;

	if (!(deque->size) || !(deque->front))
		return (content = 0);
	else
	{
		tmp = deque->front;
		content = tmp->content;
		deque->front = tmp->next;
		if (deque->front)
			deque->front->prev = 0;
		free(tmp);
		deque->size -= 1;
	}
	return (content);
}
