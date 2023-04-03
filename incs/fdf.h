/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:02:04 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 22:37:54 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "colors.h"
# include "hooks.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INPUT_ERROR 0
# define MLX_ERROR 0
# define FILE_ERROR 0
# define X_WIN 1900
# define Y_WIN 900
# define AXIS_FACTOR 20
# define OG 0
# define ISO 1
# define ISO_ANGLE 0.523599
# define ORTHO_X -3.14
# define ORTHO_Z 1.57
# define PARA_ANGLE 0.261667
# define ALT_SHIFT 0.5
# define TR_SHIFT 20
# define ZOOM_COEF 20.0
# define ANGLE_INCR 0.02
# define ZOOM_INCR 2.0
# define ZOOM_INCR_BIG 0.1

typedef struct s_gradient_data
{
	int				pixel_pos;
	int				line_length;
	int				start_color;
	int				end_color;
}					t_gradient_data;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_image;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color_z;
	unsigned int	color;
	unsigned int	hex_color;
}					t_point;

typedef struct s_center
{
	float			x;
	float			y;
	float			z;
}					t_center;

typedef struct s_color_map
{
	int				z_min;
	int				z_max;
	int				color_min;
	int				color_mid;
	int				color_max;
}					t_color_map;

typedef struct s_maps
{
	int				x0;
	int				y0;
	int				xs;
	int				ys;
	int				z_min_0;
	int				z_max_0;
	int				iso;
	int				para;
	int				shift_2d[2];
	int				shift_iso[2];
	float			zoom;
	float			zoom_incr;
	float			altitude;
	float			x_angle;
	float			y_angle;
	float			z_angle;
	t_center		center;
	t_color_map		color_map;
	t_point			**map;
	t_point			**map_2d;
}					t_maps;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_image			image;
	t_maps			maps;
}					t_data;

char				*get_next_line(int fd);
char				*ft_strncat(char *line, char *buffer, int len);
void				get_coord(int fd, t_data *data);
void				param_init(t_maps *maps, int proj);
void				initialise_zoom(t_maps *maps);
void				set_map_center(t_maps *maps);
void				initialise_shifts(t_data *data);
void				free_tab(char ***tab);
unsigned int		atoi_base(const char *s);
long long			ft_atoi(const char *nptr, int *j);
void				draw_map(t_data *data);
t_point				*set_point(t_data *data, int x, int y);
void				set_extremums(t_maps *maps);
int					valid_point(t_point u);
void				x_rotate(t_point *p, double angle);
void				y_rotate(t_point *p, double angle);
void				z_rotate(t_point *p, double angle);
void				iso(t_point *p);
void				ortho(t_point *p);
void				get_color(t_maps *maps, t_point *u);
void				initialise_gradient_data(t_gradient_data *grad_data,
						t_point u1, t_point u2);
int					pixel_color(t_gradient_data grad_data, t_point u1,
						t_point u2);
int					ft_max(int a, int b);
int					ft_min(int a, int b);
int					key_press(int keycode, t_data *data);
int					ft_close(t_data *data);
void				set_zoom(t_data *data, int keycode);
void				set_altitude(t_data *data, int keycode);
void				erase_and_new_img(t_data *data);
void				destroy_and_free(t_data *data);

#endif
