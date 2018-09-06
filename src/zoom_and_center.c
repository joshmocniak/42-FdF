/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_and_center.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 21:24:17 by jmocniak          #+#    #+#             */
/*   Updated: 2018/06/19 21:45:46 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			translate(t_map **map, t_dim dim, int offset_y, int offset_x)
{
	int	y;
	int	x;

	y = -1;
	while (++y < dim.y)
	{
		x = -1;
		while (++x < dim.x)
		{
			map[y][x].y += offset_y;
			map[y][x].x += offset_x;
		}
	}
}

void			zoom_and_center(t_map **map, t_dim dim, t_scale_data s)
{
	int		y;
	int		x;

	y = -1;
	while (++y < dim.y)
	{
		x = -1;
		while (++x < dim.x)
		{
			map[y][x].x = round(map[y][x].x * s.scale + s.pad_x);
			map[y][x].y = round(map[y][x].y * s.scale + s.pad_y);
		}
	}
}

t_scale_data	get_scale(float rect_h, float rect_w, float max_y, float max_x)
{
	t_scale_data	s;

	s.pad_y = 0;
	s.pad_x = 0;
	if ((max_x / max_y) >= (rect_w / rect_h))
	{
		s.scale = rect_w / max_x;
		s.pad_y = (rect_h - (s.scale * max_y)) / 2.0;
	}
	else
	{
		s.scale = rect_h / max_y;
		s.pad_x = (rect_w - (s.scale * max_x)) / 2.0;
	}
	return (s);
}

void			scale_to_fit_rectangle(t_map **map, t_dim dim, float rect_h, \
		float rect_w)
{
	float			max_x;
	float			max_y;
	int				x;
	int				y;

	max_x = map[0][0].x;
	max_y = map[0][0].y;
	x = -1;
	while (++x < dim.x && (y = -1))
		while (++y < dim.y)
		{
			max_x = map[y][x].x > max_x ? map[y][x].x : max_x;
			max_y = map[y][x].y > max_y ? map[y][x].y : max_y;
		}
	zoom_and_center(map, dim, get_scale(rect_h, rect_w, max_y, max_x));
}
