/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:14:43 by bok               #+#    #+#             */
/*   Updated: 2023/03/23 14:51:23 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEQUE_H
# define FT_DEQUE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

typedef struct s_deque
{
	t_dlist			*front;
	t_dlist			*rear;
	size_t			size;
}	t_deque;

//	deque.c
size_t	ft_pushback(t_deque *deque, void *content);
size_t	ft_pushfront(t_deque *deque, void *content);
void	*ft_popback(t_deque *deque);
void	*ft_popfront(t_deque *deque);

#endif
