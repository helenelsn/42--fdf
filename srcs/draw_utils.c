/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:55:02 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 22:24:27 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	valid_point(t_point u)
{
	if (u.x < 0 || u.x > X_WIN)
		return (0);
	if (u.y < 0 || u.y > Y_WIN)
		return (0);
	return (1);
}

void	set_extremums(t_maps *maps)
{
	int	z1;
	int	z2;

	z1 = maps->z_min_0 * maps->altitude;
	z2 = maps->z_max_0 * maps->altitude;
	if (maps->altitude > 0)
	{
		maps->color_map.z_min = z1;
		maps->color_map.z_max = z2;
	}
	else
	{
		maps->color_map.z_min = -ft_max(-z1, -z2);
		maps->color_map.z_max = ft_max(z1, z2);
	}
}

static void	x0_to_xc(t_maps *maps, t_point *p)
{
	p->x -= maps->center.x;
	p->y -= maps->center.y;
	p->z -= maps->center.z;
}

t_point	*set_point(t_data *data, int x, int y)
{
	t_point	*p;

	p = malloc(sizeof(t_point));
	if (!p)
		return (NULL);
	p->x = x * data->maps.zoom;
	p->y = y * data->maps.zoom;
	p->z = (int)((float)data->maps.map[x][y].z * data->maps.altitude);
	p->color_z = p->z;
	p->hex_color = data->maps.map[x][y].hex_color;
	x0_to_xc(&data->maps, p);
	x_rotate(p, data->maps.x_angle);
	y_rotate(p, data->maps.y_angle);
	z_rotate(p, data->maps.z_angle);
	if (data->maps.iso)
		iso(p);
	else
		ortho(p);
	p->x += data->maps.x0 + (!data->maps.iso) * data->maps.shift_2d[0]
		+ (data->maps.iso) * data->maps.shift_iso[0];
	p->y += data->maps.y0 + (!data->maps.iso) * data->maps.shift_2d[1]
		+ (data->maps.iso) * data->maps.shift_iso[1];
	get_color(&(data->maps), p);
	return (p);
}
