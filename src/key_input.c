/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 18:07:16 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/05 15:25:01 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_projection(t_loop_data *w)
{
	if (w->to_projection == to_generic_iso)
		w->to_projection = to_isometric;
	else if (w->to_projection == to_isometric)
		w->to_projection = to_generic_iso;
}

void	change_gradient(t_loop_data *w)
{
	if (w->gradient == 0 && w->contains_color)
		w->gradient = 2;
	else if (w->gradient == 0)
		w->gradient = 1;
	else if (w->gradient == 1)
		w->gradient = 0;
	else if (w->gradient == 2 && w->contains_color == 1)
		w->gradient = 3;
	else if (w->gradient == 2)
		w->gradient = 1;
	else if (w->gradient == 3)
		w->gradient = 1;
}

int		key_hook(int keycode, t_loop_data *w)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(w->mlx, w->win);
		free_map(w->raw_map, w->dim.y);
		exit(0);
	}
	if (keycode == UP_ARROW && w->zscale_tilt.z_scale < 5)
		w->zscale_tilt.z_scale += .05;
	else if (keycode == DOWN_ARROW && w->zscale_tilt.z_scale >= .05)
		w->zscale_tilt.z_scale -= .05;
	if (keycode == 35)
		change_projection(w);
	if (keycode == 5)
		change_gradient(w);
	draw_map(w);
	return (0);
}
