/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:41:33 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 22:31:20 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_point(t_point *u, int x, int y, char *z)
{
	char	**s;

	u->x = x;
	u->y = y;
	u->color_z = 0;
	u->hex_color = 0;
	if (!strchr(z, ','))
		u->z = ft_atoi(z, NULL);
	else
	{
		s = ft_split(z, ',');
		u->z = ft_atoi(s[0], NULL);
		u->hex_color = atoi_base(s[1]);
		free_tab(&s);
	}
}

static void	fill_row(char *row, t_maps *maps, int x, int *width)
{
	char	**row_data;
	int		i;

	i = -1;
	row_data = ft_split(row, ' ');
	if (!*width)
	{
		while (row_data[*width])
			(*width)++;
	}
	maps->map[x] = ft_calloc(sizeof(t_point), *width + 1);
	maps->map_2d[x] = ft_calloc(sizeof(t_point), *width + 1);
	while (row_data[++i])
	{
		get_point(&maps->map[x][i], x, i, row_data[i]);
		get_point(&maps->map_2d[x][i], x, i, row_data[i]);
		if (maps->color_map.z_min > maps->map[x][i].z)
			maps->color_map.z_min = maps->map[x][i].z;
		if (maps->color_map.z_max < maps->map[x][i].z)
			maps->color_map.z_max = maps->map[x][i].z;
	}
	free_tab(&row_data);
}

static void	fill_map(t_maps *maps, char *input, int height)
{
	int			i;
	static int	width;
	char		**m;

	i = -1;
	m = ft_split(input, '\n');
	maps->map = ft_calloc(sizeof(t_point *), height + 1);
	maps->map_2d = ft_calloc(sizeof(t_point *), height + 1);
	maps->color_map.z_max = 0;
	maps->color_map.z_min = 0;
	while (m[++i])
		fill_row(m[i], maps, i, &width);
	maps->xs = height;
	maps->ys = width;
	maps->z_min_0 = maps->color_map.z_min;
	maps->z_max_0 = maps->color_map.z_max;
	free_tab(&m);
}

void	param_init(t_maps *maps, int proj)
{
	int	max_len;

	max_len = ft_max(maps->xs, maps->ys);
	maps->x0 = (X_WIN - (maps->ys - 1) * maps->zoom) / 2;
	maps->y0 = (Y_WIN - (maps->xs - 1) * maps->zoom) / 2;
	maps->iso = (proj == 1);
	maps->altitude = ((float)max_len / 9.5);
	if (max_len > 300)
		maps->altitude = 0.5;
	maps->x_angle = 0;
	maps->y_angle = 0;
	maps->z_angle = 0;
}

void	get_coord(int fd, t_data *data)
{
	char	*row;
	char	*input;
	int		height;

	row = get_next_line(fd);
	height = 0;
	input = NULL;
	while (row)
	{
		height++;
		input = ft_strncat(input, row, 0);
		free(row);
		row = get_next_line(fd);
	}
	fill_map(&data->maps, input, height);
	free(input);
	initialise_zoom(&data->maps);
	param_init(&data->maps, OG);
	set_map_center(&data->maps);
	initialise_shifts(data);
}
