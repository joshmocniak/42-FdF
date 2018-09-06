/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 19:25:19 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/05 17:36:04 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_max_z(t_map **map, t_dim dim)
{
	int	x;
	int	y;
	int	max;

	y = -1;
	max = abs((int)map[0][0].z);
	while (++y < dim.y && (x = -1))
		while (++x < dim.x)
			if (abs((int)map[y][x].z) > max)
				max = abs((int)map[y][x].z);
	return (max);
}

/*
** contains_color return values:
**  1 - map has color for some coordinates but not all
**  0 - map has no color information
** -1 - map has color for all coordinates
*/

int		contains_color(t_map **map, t_dim dim)
{
	int	x;
	int	y;
	int	has_color;
	int	has_empty;

	has_color = 0;
	has_empty = 0;
	y = -1;
	while (++y < dim.y && (x = -1))
		while (++x < dim.x)
		{
			if (map[y][x].color == -1)
				has_empty = 1;
			else
				has_color = 1;
			if (has_color && has_empty)
				return (1);
		}
	if (!has_color)
		return (0);
	return (-1);
}

t_map	**make_empty_map(t_dim dim)
{
	t_map	**xy;
	int		y;

	y = 0;
	xy = (t_map **)malloc(sizeof(t_map *) * dim.y);
	while (y < dim.y)
	{
		xy[y] = (t_map *)malloc(sizeof(t_map) * dim.x);
		y++;
	}
	return (xy);
}

void	free_map(t_map **map, int rows)
{
	int		y;

	y = 0;
	while (y < rows)
	{
		free(map[y]);
		y++;
	}
	free(map);
}
