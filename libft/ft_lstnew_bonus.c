/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:47:57 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/11 10:04:01 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*re;

	re = (t_list *)malloc(sizeof(t_list));
	if (!re)
		return (NULL);
	re->content = content;
	re->next = NULL;
	return (re);
}
