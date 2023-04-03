/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:55:21 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 22:35:57 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(t_data *data)
{
	if (!mlx_loop_end(data->mlx_ptr))
	{
		write(2, "Error when closing window\n", 26);
		return (0);
	}
	return (1);
}

static void	translate(t_data *data, int keycode)
{
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		data->maps.x0 += (2 * (keycode == KEY_RIGHT) - 1) * TR_SHIFT;
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		data->maps.y0 += (2 * (keycode == KEY_DOWN) - 1) * TR_SHIFT;
}

static void	set_angle(t_data *data, int keycode)
{
	if (keycode == KEY_U || keycode == KEY_D)
		data->maps.x_angle += (2 * (keycode == KEY_D) - 1) * ANGLE_INCR;
	else if (keycode == KEY_Q || keycode == KEY_W)
		data->maps.y_angle += (2 * (keycode == KEY_W) - 1) * ANGLE_INCR;
	else if (keycode == KEY_L || keycode == KEY_R)
		data->maps.z_angle += (2 * (keycode == KEY_R) - 1) * ANGLE_INCR;
}

static void	handle_keypress(t_data *data, int keycode)
{
	if (keycode == KEY_ORTHO)
		param_init(&data->maps, OG);
	if (keycode == KEY_ISO)
		param_init(&data->maps, ISO);
	if (keycode == KEY_Z_INCR || keycode == KEY_Z_DECR)
		set_altitude(data, keycode);
	if (keycode == KEY_L || keycode == KEY_R || keycode == KEY_U
		|| keycode == KEY_D || keycode == KEY_Q || keycode == KEY_W)
		set_angle(data, keycode);
	if (keycode == KEY_IN || keycode == KEY_OUT)
		set_zoom(data, keycode);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT || keycode == KEY_UP
		|| keycode == KEY_DOWN)
		translate(data, keycode);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		if (!mlx_loop_end(data->mlx_ptr))
		{
			write(2, "Error when closing window\n", 26);
			return (MLX_ERROR);
		}
		return (0);
	}
	erase_and_new_img(data);
	handle_keypress(data, keycode);
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0,
		0);
	return (0);
}
