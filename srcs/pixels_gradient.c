/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_gradient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:52:08 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 03:29:31 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	gradient_pixels(int start_color, int end_color, int abs_z,
		int line_length)
{
	int		i;
	int		pixel_color;
	double	increment[3];
	int		color[3];

	i = 0;
	if (start_color == end_color)
		return (start_color);
	increment[0] = (double)((end_color >> 16) - (start_color >> 16))
		/ (double)line_length;
	increment[1] = ((double)((end_color >> 8) & 0xFF)
			- (double)((start_color >> 8) & 0xFF)) / (double)line_length;
	increment[2] = ((double)(end_color & 0xFF) - (double)(start_color & 0xFF))
		/ (double)line_length;
	while (++i < 3)
		color[i] = (start_color >> (16 - 8 * i)) + (int)round(abs_z
				* increment[i]);
	pixel_color = (color[0] >> 16) + (color[1] >> 8) + color[2];
	return (pixel_color);
}

int	pixel_color(t_gradient_data grad_data, t_point u1, t_point u2)
{
	if (!PIX_GRADIENT)
		return (u1.color * (u1.z >= u2.z) + u2.color * (u2.z > u1.z));
	else
		return (gradient_pixels(grad_data.start_color, grad_data.end_color,
				grad_data.line_length, grad_data.pixel_pos));
}

void	initialise_gradient_data(t_gradient_data *grad_data, t_point u1,
		t_point u2)
{
	grad_data->pixel_pos = 0;
	grad_data->line_length = sqrt((u1.x * u1.x) + (u2.x * u2.x));
	if (u1.z < u2.z)
	{
		grad_data->start_color = u1.color;
		grad_data->end_color = u2.color;
	}
	else
	{
		grad_data->start_color = u2.color;
		grad_data->end_color = u1.color;
	}
}
