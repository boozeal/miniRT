/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbok <jbok@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:25:59 by jbok              #+#    #+#             */
/*   Updated: 2023/04/20 18:45:14 by jbok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	t_mlx	mlx;

	if (argc != 2 || ft_strncmp(".rt", argv[1] + ft_strlen(argv[1]) - 3, -1))
	{
		printf("usage: %s *.rt\n", argv[0]);
		return (1);
	}
	ft_memset(&mlx, 0, sizeof(mlx));
	init_mlx(&mlx, argv[0] + 2);
	ft_memset(&data, 0, sizeof(data));
	data.mlx = mlx.mlx;
	init_data(&data, argv[1]);
	init_viewport(&data.viewport);
	mlx_hook(mlx.win, 2, 0, key_press, &mlx);
	mlx_hook(mlx.win, 17, 0, window_closed, &mlx);
	mlx_refresh(&mlx, &data);
	del_unnecessary(&data);
	mlx_destroy_image(mlx.mlx, mlx.image);
	mlx_loop(mlx.mlx);
}
