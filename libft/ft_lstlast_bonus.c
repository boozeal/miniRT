/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:21:54 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/11 00:54:38 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*re;
	t_list	*tmp;

	re = lst;
	if (!re)
		return (re);
	while (re)
	{
		tmp = re;
		re = re->next;
	}
	return (tmp);
}
