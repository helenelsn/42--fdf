/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 02:02:44 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 21:26:19 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	erase_and_new_img(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->image.img);
	data->image.img = mlx_new_image(data->mlx_ptr, X_WIN, Y_WIN);
	data->image.addr = mlx_get_data_addr(data->image.img, &(data->image.bpp),
			&(data->image.line_length), &(data->image.endian));
}

void	set_altitude(t_data *data, int keycode)
{
	float	prev_alt;

	prev_alt = data->maps.altitude;
	if (keycode == KEY_Z_INCR)
		data->maps.altitude += ALT_SHIFT;
	else
		data->maps.altitude -= ALT_SHIFT;
	if ((prev_alt < 0.0 && data->maps.altitude > 0.0) || (prev_alt > 0.0
			&& data->maps.altitude < 0.0))
		data->maps.altitude = 0.0;
}

static void	compute_alt(t_data *data, int new_zoom_value)
{
	float	prev_alt;

	prev_alt = data->maps.altitude;
	if (data->maps.zoom == 0)
	{
		if (ft_max(data->maps.xs, data->maps.ys) < 300)
			data->maps.altitude = 2.0;
		else
			data->maps.altitude = 0.5;
	}
	else
		data->maps.altitude = (prev_alt * (float)new_zoom_value
				/ (float)data->maps.zoom);
}

static void	reset_xc_shift(t_data *data, float prev_zoom)
{
	int	xc_additional_shift;
	int	yc_additional_shift;

	xc_additional_shift = (data->maps.xs * prev_zoom - data->maps.xs
			* data->maps.zoom) / 2;
	yc_additional_shift = (data->maps.ys * prev_zoom - data->maps.ys
			* data->maps.zoom) / 2;
	data->maps.x0 += xc_additional_shift;
	data->maps.y0 += yc_additional_shift;
}

void	set_zoom(t_data *data, int keycode)
{
	float	prev_zoom;

	prev_zoom = data->maps.zoom;
	if (keycode == KEY_IN)
	{
		compute_alt(data, data->maps.zoom + data->maps.zoom_incr);
		data->maps.zoom += data->maps.zoom_incr;
	}
	else
	{
		if (data->maps.zoom <= data->maps.zoom_incr)
		{
			compute_alt(data, data->maps.zoom_incr);
			data->maps.zoom = data->maps.zoom_incr;
		}
		else
		{
			compute_alt(data, data->maps.zoom - data->maps.zoom_incr);
			data->maps.zoom -= data->maps.zoom_incr;
		}
	}
	reset_xc_shift(data, prev_zoom);
}
