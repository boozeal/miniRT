/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:01:39 by seonghyu          #+#    #+#             */
/*   Updated: 2022/11/11 10:39:06 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordlen(const char *str, int i, char c)
{
	int	tmp;

	tmp = i;
	while (str[i] && str[i] != c)
		i++;
	return (i - tmp);
}

static int	cnt(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*putword(const char *str, int i, char c)
{
	char	*re;
	int		len;
	int		j;

	len = wordlen(str, i, c);
	re = (char *)malloc(sizeof(char) * (len + 1));
	if (!re)
		return (0);
	re[len] = 0;
	j = 0;
	while (j < len)
	{
		re[j] = str[i];
		j++;
		i++;
	}
	return (re);
}

static int	free_chk(char	**re, int j)
{
	int	i;

	i = 0;
	if (!re[j])
	{
		while (i < j)
		{
			free(re[i]);
			i++;
		}
		free(re);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**re;
	int		i;
	int		j;

	re = (char **)malloc(sizeof(char *) * (cnt(s, c) + 1));
	if (!re)
		return (0);
	i = 0;
	j = -1;
	while (++j < cnt(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			re[j] = putword(s, i, c);
			if (free_chk(re, j))
				return (NULL);
		}
		while (s[i] && s[i] != c)
			i++;
	}
	re[cnt(s, c)] = 0;
	return (re);
}
