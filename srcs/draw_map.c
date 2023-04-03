/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:40:09 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 22:30:58 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x < 0 || y < 0 || y > Y_WIN || x > X_WIN)
		return ;
	i = data->image.bpp - 8;
	pixel = data->image.addr + (y * data->image.line_length) + (x
			* (data->image.bpp / 8));
	*(int *)pixel = color;
	while (i >= 0)
	{
		if (data->image.endian)
			*(int *)pixel++ = (color >> i) & 0xFF;
		else
			*(int *)pixel++ = (color >> (data->image.bpp - 8 - i));
		i -= 8;
	}
}

static void	line_numerous_y(t_data *data, t_point u1, t_point u2)
{
	int				x;
	int				y;
	t_gradient_data	grad_data;

	if (u2.y < u1.y)
		line_numerous_y(data, u2, u1);
	else
	{
		initialise_gradient_data(&grad_data, u1, u2);
		y = u1.y;
		while (y <= u2.y)
		{
			x = u1.x;
			if (u1.y != u2.y)
				x = u1.x + (u2.x - u1.x) * (y - u1.y) / (u2.y - u1.y);
			grad_data.pixel_pos = sqrt((abs(u2.x - x) * abs(u2.x - x))
					+ (abs(u2.y - y) * abs(u2.y - y)));
			img_pixel_put(data, x, y, pixel_color(grad_data, u1, u2));
			y++;
		}
	}
}

static void	line_numerous_x(t_data *data, t_point u1, t_point u2)
{
	int				x;
	int				y;
	t_gradient_data	grad_data;

	if (u2.x < u1.x)
		line_numerous_x(data, u2, u1);
	else
	{
		initialise_gradient_data(&grad_data, u1, u2);
		x = u1.x;
		while (x <= u2.x)
		{
			y = u1.y;
			if (u1.x != u2.x)
				y = u1.y + (u2.y - u1.y) * (x - u1.x) / (u2.x - u1.x);
			grad_data.pixel_pos = sqrt((abs(u2.x - x) * abs(u2.x - x))
					+ (abs(u2.y - y) * abs(u2.y - y)));
			img_pixel_put(data, x, y, pixel_color(grad_data, u1, u2));
			x++;
		}
	}
}

void	draw_line(t_data *data, t_point *u1, t_point *u2)
{
	if (!valid_point(*u1) && !valid_point(*u2))
		return ;
	if (abs(u1->x - u2->x) >= abs(u1->y - u2->y))
		line_numerous_x(data, *u1, *u2);
	else
		line_numerous_y(data, *u1, *u2);
	free(u1);
	free(u2);
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	set_extremums(&data->maps);
	while (x < data->maps.xs)
	{
		y = 0;
		while (y < data->maps.ys)
		{
			if (x < data->maps.xs - 1)
				draw_line(data, set_point(data, x, y), set_point(data, x + 1,
						y));
			if (y < data->maps.ys - 1)
				draw_line(data, set_point(data, x, y), set_point(data, x, y
						+ 1));
			y++;
		}
		x++;
	}
}
