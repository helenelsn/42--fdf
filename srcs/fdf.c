/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:01:54 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 21:26:48 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "hooks.h"

static int	check_fd(char *input)
{
	int	i;

	i = 0;
	if (!input || input[0] == '.')
		return (INPUT_ERROR);
	while (input[i] && input[i] != '.')
		i++;
	if (!input[i] || (input[i - 1] == '/'))
		return (INPUT_ERROR);
	i++;
	if (!input[i] || input[i] != 'f')
		return (INPUT_ERROR);
	i++;
	if (!input[i] || input[i] != 'd')
		return (INPUT_ERROR);
	i++;
	if (!input[i] || input[i] != 'f')
		return (INPUT_ERROR);
	i++;
	if (input[i])
		return (INPUT_ERROR);
	return (1);
}

static int	initialise_mlx_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, X_WIN, Y_WIN, "Fdf");
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (MLX_ERROR);
	}
	data->image.img = mlx_new_image(data->mlx_ptr, X_WIN, Y_WIN);
	data->image.addr = mlx_get_data_addr(data->image.img, &(data->image.bpp),
			&(data->image.line_length), &(data->image.endian));
	return (1);
}

static int	fdf_get_started(t_data *data, int fd)
{
	if (!initialise_mlx_data(data))
	{
		write(2, "Error : something went wrong in the mlx-data initialisation\n",
			62);
		return (MLX_ERROR);
	}
	get_coord(fd, data);
	draw_map(data);
	close(fd);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0,
		0);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->win_ptr, 33, 1L << 17, ft_close, data);
	mlx_loop(data->mlx_ptr);
	destroy_and_free(data);
	return (1);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*fd_check;
	t_data	data;

	if (argc != 2)
	{
		write(2, "Error : not enough/too many arguments in command line\n", 54);
		return (-1);
	}
	fd_check = ft_strchr(argv[1], '.');
	if (!fd_check || !check_fd(argv[1]))
	{
		write(2, "Error : not a .fdf file\n", 25);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	if (!fdf_get_started(&data, fd))
		return (-1);
	return (0);
}
