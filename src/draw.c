/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 02:45:55 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/05 17:37:44 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_menu(t_loop_data *w)
{
	int		c;
	int		x;
	int		y;

	x = 50;
	y = 50;
	c = 0xff1fff;
	mlx_string_put(w->mlx, w->win, x, y, c, "<ESC> to quit");
	y += 20;
	if (w->to_projection == to_isometric)
		mlx_string_put(w->mlx, w->win, x, y, c, "<p> Projection: Isometric");
	else if (w->to_projection == to_generic_iso)
		mlx_string_put(w->mlx, w->win, x, y, c, \
				"<p> Projection: Generic Rotate");
	if ((y += 20) && w->gradient == 1)
		mlx_string_put(w->mlx, w->win, x, y, c, "<g> Gradient: Generic");
	else if (w->gradient == 0)
		mlx_string_put(w->mlx, w->win, x, y, c, "<g> Gradient: Off");
	else if (w->gradient == 2)
		mlx_string_put(w->mlx, w->win, x, y, c, "<g> Gradient: File");
	else if (w->gradient == 3)
		mlx_string_put(w->mlx, w->win, x, y, c, "<g> Gradient: File + Generic");
	y += 20;
	mlx_string_put(w->mlx, w->win, x, y, c, \
			"<up-arrow, down-arrow> to scale z axis");
}

void	draw_map(t_loop_data *w)
{
	int		x;
	int		y;
	t_map	**map;

	mlx_clear_window(w->mlx, w->win);
	map = make_empty_map(w->dim);
	w->to_projection(w->raw_map, map, w->dim, w->zscale_tilt);
	scale_to_fit_rectangle(map, w->dim, WIN_HEIGHT - (MARGIN * 2), \
			WIN_WIDTH - (MARGIN * 2));
	translate(map, w->dim, MARGIN, MARGIN);
	y = -1;
	while (++y < w->dim.y && (x = -1))
		while (++x < w->dim.x - 1)
			line(*w, map[y][x], map[y][x + 1]);
	x = -1;
	while (++x < w->dim.x && (y = -1))
		while (++y < w->dim.y - 1)
			line(*w, map[y][x], map[y + 1][x]);
	free_map(map, w->dim.y);
	draw_menu(w);
}

int		loop_hook(t_loop_data *w)
{
	if (w->to_projection == to_generic_iso && w->rotate)
	{
		if (w->zscale_tilt.tilt == 360)
			w->zscale_tilt.tilt = 0;
		w->zscale_tilt.tilt += 1;
		draw_map(w);
	}
	return (0);
}

void	draw(t_map **map, t_dim dim)
{
	t_loop_data	w;

	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	w.zscale_tilt.z_scale = Z_SCALE;
	w.zscale_tilt.tilt = TILT;
	w.dim = dim;
	w.raw_map = map;
	w.rotate = 1;
	w.max_z = get_max_z(map, dim);
	w.contains_color = contains_color(map, dim);
	if (w.contains_color)
		w.gradient = 2;
	else
		w.gradient = 1;
	w.to_projection = to_isometric;
	draw_map(&w);
	mlx_loop_hook(w.mlx, loop_hook, &w);
	mlx_key_hook(w.win, key_hook, &w);
	mlx_loop(w.mlx);
}
