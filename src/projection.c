/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:22:20 by jmocniak          #+#    #+#             */
/*   Updated: 2018/06/19 21:42:33 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	normalize_helper(t_map **map, t_dim dim, float min_y, float min_x)
{
	int	y;
	int	x;

	y = 0;
	while (y < dim.y)
	{
		x = 0;
		while (x < dim.x)
		{
			map[y][x].x += -min_x;
			map[y][x].y += -min_y;
			x++;
		}
		y++;
	}
}

void	normalize_coords(t_map **map, t_dim dim)
{
	float	lowest_x;
	float	lowest_y;
	int		y;
	int		x;

	y = 0;
	x = 0;
	lowest_x = map[y][x].x;
	lowest_y = map[y][x].y;
	while (y < dim.y)
	{
		x = 0;
		while (x < dim.x)
		{
			if (map[y][x].x < lowest_x)
				lowest_x = map[y][x].x;
			if (map[y][x].y < lowest_y)
				lowest_y = map[y][x].y;
			x++;
		}
		y++;
	}
	normalize_helper(map, dim, lowest_y, lowest_x);
}

void	to_isometric(t_map **in, t_map **out, t_dim dim, t_projdat zscale_tilt)
{
	int		i;
	int		j;
	double	rad;
	float	tmp_x;

	rad = -60.0 * M_PI / 180.0;
	j = -1;
	while (++j < dim.y)
	{
		i = -1;
		while (++i < dim.x)
		{
			out[j][i].x = (in[j][i].x + (in[j][i].z * zscale_tilt.z_scale)) \
					/ sqrt(2.0);
			out[j][i].y = (in[j][i].x + 2.0 * in[j][i].y - \
					(in[j][i].z * zscale_tilt.z_scale)) / sqrt(6.0);
			tmp_x = out[j][i].x;
			out[j][i].x = out[j][i].x * cos(rad) - out[j][i].y * sin(rad);
			out[j][i].y = out[j][i].y * cos(rad) + tmp_x * sin(rad);
			out[j][i].z = in[j][i].z;
			out[j][i].color = in[j][i].color;
		}
	}
	normalize_coords(out, dim);
}

void	to_generic_iso(t_map **in, t_map **out, t_dim dim, \
		t_projdat zscale_tilt)
{
	int		y;
	int		x;
	double	rad;

	rad = zscale_tilt.tilt * M_PI / 180.0;
	y = 0;
	while (y < dim.y)
	{
		x = 0;
		while (x < dim.x)
		{
			out[y][x].x = in[y][x].x * cos(rad) - in[y][x].y * sin(rad);
			out[y][x].y = in[y][x].y * cos(rad) + in[y][x].x * sin(rad) \
					- (in[y][x].z * zscale_tilt.z_scale);
			out[y][x].z = in[y][x].z;
			out[y][x].color = in[y][x].color;
			x++;
		}
		y++;
	}
	normalize_coords(out, dim);
}
