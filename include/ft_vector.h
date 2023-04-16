/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:29:00 by jbok              #+#    #+#             */
/*   Updated: 2023/04/09 18:48:59 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include "libft.h"
# include "sys/types.h"
# include <unistd.h>

# ifndef VEC_RESERVE_SIZE
#  define VEC_RESERVE_SIZE 16
# endif

typedef struct s_vector
{
	void	**content;
	ssize_t	size;
	ssize_t	capacity;
}	t_vector;

t_vector	*ft_vecnew(void);
ssize_t		ft_vec_push(t_vector *vec, void *content);
void		*ft_vec_pop(t_vector *vec);
int			ft_vec_reserve(t_vector *vec, ssize_t size);

#endif
