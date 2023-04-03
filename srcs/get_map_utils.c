/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 02:11:13 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 22:32:32 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab(char ***tab)
{
	int	i;

	if (!(*tab))
		return ;
	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	set_map_center(t_maps *maps)
{
	maps->center.x = (((float)(maps->xs) * maps->zoom) / 2.0);
	maps->center.y = (((float)(maps->ys) * maps->zoom) / 2.0);
	maps->center.z = (((float)(maps->color_map.z_max) * maps->altitude) / 2.0);
}

void	initialise_zoom(t_maps *maps)
{
	int	max_len;

	max_len = ft_max(maps->xs, maps->ys);
	maps->zoom = ZOOM_COEF;
	maps->zoom_incr = ZOOM_INCR;
	if (max_len >= 100)
		maps->zoom_incr = ZOOM_INCR_BIG;
	while ((float)maps->xs * maps->zoom > ((float)X_WIN) || (float)maps->ys
		* maps->zoom > ((float)Y_WIN))
		maps->zoom -= maps->zoom_incr;
	while (((float)maps->xs * maps->zoom) < ((float)X_WIN / 3.0)
		|| (float)maps->ys * maps->zoom < ((float)Y_WIN / 3.0))
		maps->zoom += maps->zoom_incr;
}

static void	set_shift(t_data *data, int *shift_x, int *shift_y, int proj)
{
	t_point	*x0;
	t_point	*xf;
	float	xc_map;
	float	yc_map;

	data->maps.iso = (proj == 1);
	x0 = set_point(data, 0, 0);
	xf = set_point(data, data->maps.xs - 1, data->maps.ys - 1);
	xc_map = ((float)(xf->x - x0->x) / 2.0) + (float)x0->x;
	yc_map = ((float)(xf->y - x0->y) / 2.0) + (float)x0->y;
	*shift_x = (int)((float)X_WIN / 2.0) - xc_map;
	*shift_y = (int)((float)Y_WIN / 2.0) - yc_map;
	free(x0);
	free(xf);
}

void	initialise_shifts(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		data->maps.shift_2d[i] = 0;
		data->maps.shift_iso[i] = 0;
	}
	set_shift(data, &data->maps.shift_2d[0], &data->maps.shift_2d[1], 0);
	set_shift(data, &data->maps.shift_iso[0], &data->maps.shift_iso[1], 1);
	data->maps.iso = 1;
}
