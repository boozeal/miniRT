/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:35:27 by jbok              #+#    #+#             */
/*   Updated: 2023/04/19 17:01:12 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_split(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

int	is_set(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	sepnum(char *str, char *charset)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (i == 0 || (!is_set(str[i], charset) && is_set(str[i - 1], charset)))
			cnt++;
		i++;
	}
	return (cnt);
}

char	*ftstrdup(char *str, char *charset)
{
	int		i;
	int		j;
	char	*arr;

	i = 0;
	j = 0;
	while (str[i] && !is_set(str[i], charset))
		i++;
	arr = ft_substr(str, 0, i);
	return (arr);
}

char	**ft_split2(char *str, char *charset)
{
	int		i;
	int		j;
	int		cnt;
	char	**split;

	i = 0;
	cnt = sepnum(str, charset);
	while (is_set(*str, charset))
		str++;
	split = malloc(sizeof(char *) * (cnt + 1));
	if (!split)
		exit_msg(1, "Not enough memory");
	j = 0;
	while (str[i])
	{
		if (i == 0 || (!is_set(str[i], charset) && is_set(str[i - 1], charset)))
		{
			split[j++] = ftstrdup(str + i, charset);
			if (!split[j - 1])
				exit_msg(1, "Not enough memory");
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
