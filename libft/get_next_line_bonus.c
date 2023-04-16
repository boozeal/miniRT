/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghyu <seonghyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:16:02 by seonghyu          #+#    #+#             */
/*   Updated: 2022/12/27 15:54:31 by seonghyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*find_enter(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n')
			return (str + i);
		i++;
	}
	return (NULL);
}

int	get_buffer(int fd, char *array[257])
{
	char	*buf;
	char	*tmp;
	int		read_size;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size <= 0)
	{
		free(buf);
		if (read_size == -1)
		{
			free(array[fd]);
			array[fd] = NULL;
		}
		return (read_size);
	}
	buf[read_size] = 0;
	tmp = gnl_strjoin(array[fd], buf);
	free(buf);
	if (array[fd] != NULL)
		free(array[fd]);
	array[fd] = tmp;
	return (read_size);
}

char	*devide(char **remain)
{
	int		idx;
	char	*re;
	char	*tmp;

	idx = gnl_strchr(*remain, '\n');
	re = (char *)malloc(sizeof(char) * (idx + 2));
	if (!re)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (gnl_strlen(*remain) - idx + 2));
	if (!tmp)
	{
		free(re);
		return (NULL);
	}
	gnl_strlcpy(re, *remain, idx + 2);
	gnl_strlcpy(tmp, *remain + idx + 1, gnl_strlen(*remain) - idx + 2);
	if (*remain != NULL)
		free(*remain);
	*remain = tmp;
	if (tmp[0] == 0)
	{
		free(tmp);
		*remain = NULL;
	}
	return (re);
}

char	*get_next_line(int fd)
{
	int				tmp;
	static char		*array[257];
	char			*re;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if ((fd > 2 || fd == 0) && fd <= 256)
	{
		while (find_enter(array[fd]) == NULL)
		{
			tmp = get_buffer(fd, array);
			if (tmp == -1 || (tmp == 0 && array[fd] == NULL))
				return (NULL);
			if (tmp < BUFFER_SIZE && find_enter(array[fd]) == NULL)
				return (handle_eof(&array[fd]));
		}
		re = devide(&array[fd]);
		return (re);
	}
	return (NULL);
}
