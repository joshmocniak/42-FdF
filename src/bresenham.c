/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 18:06:04 by jmocniak          #+#    #+#             */
/*   Updated: 2018/06/19 22:30:21 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	tmap_to_tmapi(t_map *map, t_map_i *mapi)
{
	mapi->y = map->y;
	mapi->x = map->x;
	mapi->z = map->z;
	mapi->color = map->color;
}

void	line_deltax_greater(t_loop_data w, t_line_data l)
{
	int	err;
	int	err_new;

	err = l.d.y + l.d.y - l.d.x;
	err_new = l.d.y + l.d.y;
	while (l.q.x != l.p1.x)
	{
		mlx_pixel_put(w.mlx, w.win, l.q.x, l.q.y, \
				get_current_color(w, l.q, l.p0, l.p1));
		err += err_new;
		if (err >= 0)
		{
			l.q.y += l.s.y;
			err -= l.d.x + l.d.x;
		}
		l.q.x += l.s.x;
	}
}

void	line_deltay_greater(t_loop_data w, t_line_data l)
{
	int	err;
	int	err_new;

	err = l.d.x + l.d.x - l.d.y;
	err_new = l.d.x + l.d.x;
	while (l.q.y != l.p1.y)
	{
		mlx_pixel_put(w.mlx, w.win, l.q.x, l.q.y, \
				get_current_color(w, l.q, l.p0, l.p1));
		err += err_new;
		if (err >= 0)
		{
			l.q.x += l.s.x;
			err -= l.d.y + l.d.y;
		}
		l.q.y += l.s.y;
	}
}

void	line(t_loop_data w, t_map p0_float, t_map p1_float)
{
	t_line_data	l;

	tmap_to_tmapi(&p0_float, &l.p0);
	tmap_to_tmapi(&p1_float, &l.p1);
	l.s.y = l.p0.y < l.p1.y ? 1 : -1;
	l.s.x = l.p0.x < l.p1.x ? 1 : -1;
	l.d.y = abs(l.p0.y - l.p1.y);
	l.d.x = abs(l.p0.x - l.p1.x);
	l.q.x = l.p0.x;
	l.q.y = l.p0.y;
	if (l.d.x > l.d.y)
		line_deltax_greater(w, l);
	else
		line_deltay_greater(w, l);
	l.q.x = l.p1.x;
	l.q.y = l.p1.y;
	mlx_pixel_put(w.mlx, w.win, l.p1.x, l.p1.y, \
			get_current_color(w, l.q, l.p0, l.p1));
}
