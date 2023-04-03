/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points_gradient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:33:38 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 20:23:07 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	gradient_points(t_point *u, int d_z, int start_color, int end_color)
{
	int		i;
	double	increment[3];
	int		new_color[3];

	if (start_color == end_color)
	{
		(u->color = start_color);
		return ;
	}
	i = -1;
	increment[0] = (double)((end_color >> 16) - (start_color >> 16))
		/ (double)d_z;
	increment[1] = ((double)((end_color >> 8) & 0xFF)
			- (double)((start_color >> 8) & 0xFF)) / (double)d_z;
	increment[2] = ((double)(end_color & 0xFF) - (double)(start_color & 0xFF))
		/ (double)d_z;
	new_color[0] = (start_color >> 16) + (int)round((abs(u->color_z))
			* increment[0]);
	new_color[1] = (start_color >> 8 & 0xFF) + (int)round((abs(u->color_z))
			* increment[1]);
	new_color[2] = (start_color & 0xFF) + (int)round((abs(u->color_z))
			* increment[2]);
	u->color = (new_color[0] << 16) + (new_color[1] << 8) + new_color[2];
}

void	get_color(t_maps *maps, t_point *u)
{
	u->color = DEFAULT_COLOR;
	if (u->hex_color)
	{
		u->color = u->hex_color;
		return ;
	}
	if (!GRADIENT)
		return ;
	if (u->color_z == maps->color_map.z_max && u->color_z != 0)
		u->color = TOP_COLOR;
	else if (u->color_z == 0)
		u->color = FLOOR_COLOR;
	else if (u->color_z == maps->color_map.z_min && u->color_z != 0)
		u->color = BOTTOM_COLOR;
	else if (u->color_z < 0)
		gradient_points(u, -maps->color_map.z_min, BOTTOM_COLOR, FLOOR_COLOR);
	else
		gradient_points(u, maps->color_map.z_max, FLOOR_COLOR, TOP_COLOR);
}
