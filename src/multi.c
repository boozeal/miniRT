/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bok <bok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:21:39 by jbok              #+#    #+#             */
/*   Updated: 2023/04/09 19:40:52 by bok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <pthread.h>
#include <sys/sysctl.h>
#include "ft_deque.h"

typedef struct s_multi
{
	pthread_t		*threads;
	t_data			*data;
	t_vector		*task_stack;
	pthread_mutex_t	task_stack_mutex;
}	t_multi;

t_color	rt_ray(t_data *data, t_ray *ray);

void	*rt_calc_multi(void *param)
{
	t_multi	*multi;
	t_color	color;
	size_t	i;

	multi = param;
	pthread_mutex_lock(&multi->task_stack_mutex);
	while (multi->task_stack->size)
	{
		i = (size_t)ft_vec_pop(multi->task_stack);
		pthread_mutex_unlock(&multi->task_stack_mutex);
		color = rt_ray(multi->data, multi->data->viewport.rays + i);
		*(t_color *)(multi->data->viewport.pixels + i) = color;
		pthread_mutex_lock(&multi->task_stack_mutex);
	}
	pthread_mutex_unlock(&multi->task_stack_mutex);
	return (0);
}

int	rt_pixels_multi(t_data *data)
{
	t_multi		multi;
	const long	available = sysconf(_SC_NPROCESSORS_ONLN) * 2;
	ssize_t		x;
	ssize_t		y;
	int			i;

	printf("core: %ld\n", available);
	multi.data = data;
	multi.task_stack = ft_vecnew();
	ft_vec_reserve(multi.task_stack, data->viewport.w * data->viewport.h);
	pthread_mutex_init(&multi.task_stack_mutex, 0);
	multi.threads = malloc(sizeof(pthread_t) * available);
	x = -1;
	while (++x < data->viewport.w)
	{
		y = -1;
		while (++y < data->viewport.h)
			ft_vec_push(multi.task_stack, (void *)(x + y * data->viewport.w));
	}
	i = -1;
	while (++i < available)
		pthread_create(multi.threads + i, 0, rt_calc_multi, &multi);
	while (i--)
		pthread_join(multi.threads[i], 0);
	free(multi.threads);
	pthread_mutex_destroy(&multi.task_stack_mutex);
	free(multi.task_stack->content);
	free(multi.task_stack);
	return (0);
}
