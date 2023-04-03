/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:51:05 by hlesny            #+#    #+#             */
/*   Updated: 2023/03/22 22:30:32 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_rotate(t_point *p, double angle)
{
	int	y_new;
	int	z_new;

	if (!angle)
		return ;
	y_new = cos(angle) * p->y + sin(angle) * p->z;
	z_new = -sin(angle) * p->y + cos(angle) * p->z;
	p->y = y_new;
	p->z = z_new;
}

void	y_rotate(t_point *p, double angle)
{
	int	x_new;
	int	z_new;

	if (!angle)
		return ;
	x_new = cos(angle) * p->x + sin(angle) * p->z;
	z_new = -sin(angle) * p->x + cos(angle) * p->z;
	p->x = x_new;
	p->z = z_new;
}

void	z_rotate(t_point *p, double angle)
{
	int	x_new;
	int	y_new;

	if (!angle)
		return ;
	x_new = -sin(angle) * p->y + cos(angle) * p->x;
	y_new = cos(angle) * p->y + sin(angle) * p->x;
	p->x = x_new;
	p->y = y_new;
}

void	iso(t_point *p)
{
	int	x_new;
	int	y_new;

	x_rotate(p, M_PI);
	x_new = (p->x - p->y) * cos(ISO_ANGLE);
	y_new = (p->x + p->y) * sin(ISO_ANGLE) + p->z;
	p->x = x_new;
	p->y = y_new;
}

void	ortho(t_point *p)
{
	x_rotate(p, ORTHO_X);
	z_rotate(p, ORTHO_Z);
}
