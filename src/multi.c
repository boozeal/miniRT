/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:21:39 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 18:38:37 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/sysctl.h>
#include "minirt.h"
#include "ft_deque.h"

void	*rt_calc_multi(void *param)
{
	t_multi	*multi;
	size_t	i;

	multi = param;
	pthread_mutex_lock(&multi->task_stack_mutex);
	while (multi->task_stack->size)
	{
		i = (size_t)ft_vec_pop(multi->task_stack);
		pthread_mutex_unlock(&multi->task_stack_mutex);
		multi->data->viewport.pixels[i] = \
		rt_ray(multi->data, multi->data->viewport.rays + i);
		pthread_mutex_lock(&multi->task_stack_mutex);
	}
	pthread_mutex_unlock(&multi->task_stack_mutex);
	return (0);
}

void	rt_calc_single(t_data *data)
{
	ssize_t	i;

	i = -1;
	while (++i < data->viewport.w * data->viewport.h)
		data->viewport.pixels[i] = rt_ray(data, data->viewport.rays + i);
}

void	rt_pixels_multi(t_data *data)
{
	t_multi		multi;
	const long	available = sysconf(_SC_NPROCESSORS_ONLN) * 2;
	ssize_t		offset;
	int			i;

	if (available <= 2)
		return (rt_calc_single(data));
	multi.data = data;
	multi.task_stack = ft_vecnew();
	multi.threads = malloc(sizeof(pthread_t) * available);
	if (!multi.task_stack || !multi.threads)
		exit_msg(1, "Not enough memory");
	if (ft_vec_reserve(multi.task_stack, data->viewport.w * data->viewport.h))
		exit_msg(1, "Not enough memory");
	if (pthread_mutex_init(&multi.task_stack_mutex, 0))
		exit_msg(1, "pthread_mutex_init failed :(");
	offset = 0;
	while (offset < data->viewport.w * data->viewport.h)
		ft_vec_push(multi.task_stack, (void *)(offset++));
	i = -1;
	while (++i < available)
		pthread_create(multi.threads + i, 0, rt_calc_multi, &multi);
	while (i--)
		pthread_join(multi.threads[i], 0);
	del_multi(&multi);
}
