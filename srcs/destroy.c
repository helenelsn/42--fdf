/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:50:13 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 03:26:27 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_maps(t_maps *maps)
{
	int	i;

	i = -1;
	while (++i < maps->xs)
	{
		free(maps->map[i]);
		free(maps->map_2d[i]);
	}
	free(maps->map);
	free(maps->map_2d);
}

void	destroy_and_free(t_data *data)
{
	free_maps(&data->maps);
	mlx_destroy_image(data->mlx_ptr, data->image.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
