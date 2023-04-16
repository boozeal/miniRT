/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:53:26 by seonghyu          #+#    #+#             */
/*   Updated: 2022/12/28 12:16:02 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		re;
	size_t	i;

	i = 0;
	if (s1 != NULL && s2 == NULL)
		return (s1[0]);
	if (s2 != NULL && s1 == NULL)
		return (s2[0]);
	while (((unsigned char)s1[i] == (unsigned char)s2[i]) && (s1[i]))
		i++;
	re = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (i < n)
		return (re);
	else
		return (0);
}
