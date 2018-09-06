/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:22:58 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/06 01:00:04 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_realloc(char ***lines, int allocated)
{
	char	**tmplines;

	allocated += STR_INCR;
	tmplines = (char **)ft_memalloc(sizeof(char *) * allocated);
	ft_memcpy(tmplines, *lines, sizeof(char *) * (allocated - STR_INCR));
	free(*lines);
	*lines = tmplines;
	return (allocated);
}

int		read_color_code(const char *s, int *i)
{
	int j;

	j = 0;
	if (!ft_isspace(s[*i]) && s[*i] != ',' && s[*i])
		ft_error("error: invalid map");
	else if (ft_isspace(s[*i]) || !s[*i])
		return (-1);
	(*i)++;
	return (fdf_atoi_hex(s, i));
}

t_map	**store(char **lines, t_map **map, int ints_per_row)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	while (lines[i] && !(j = 0))
	{
		x = 0;
		while (lines[i][j])
		{
			map[i][x].z = fdf_atoi(lines[i], &j);
			map[i][x].color = read_color_code(lines[i], &j);
			map[i][x].y = i;
			map[i][x].x = x;
			while (ft_isspace(lines[i][j]))
				j++;
			x++;
		}
		free(lines[i]);
		if (x != ints_per_row)
			ft_error("error: invalid map");
		i++;
	}
	free(lines);
	return (map);
}

t_map	**create_map(char **lines, int rows, t_dim *dim)
{
	t_map		**map;
	int			x;
	int			y;

	y = 0;
	if (!(x = ft_wordcount(lines[0])))
		ft_error("error: invalid map");
	map = (t_map **)malloc(sizeof(t_map *) * rows);
	while (y < rows)
		map[y++] = (t_map *)malloc(sizeof(t_map) * x);
	dim->x = x;
	dim->y = y;
	return (store(lines, map, x));
}

t_map	**parse(int fd, t_dim *dim)
{
	char	**lines;
	int		i;
	int		allocated;
	int		gnl_err;

	i = 0;
	allocated = STR_INCR;
	lines = (char **)ft_memalloc(sizeof(char *) * allocated);
	while ((gnl_err = get_next_line(fd, lines + i)))
	{
		if (gnl_err == -1)
		{
			ft_putstr(strerror(errno));
			return (NULL);
		}
		if (i == (allocated - 1))
			allocated = ft_realloc(&lines, allocated);
		i++;
	}
	return (create_map(lines, i, dim));
}
