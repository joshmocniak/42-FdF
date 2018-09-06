/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:52:02 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/05 17:38:18 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_current_color_3(t_dim q, t_map_i p0, t_map_i p1)
{
	float	percent;
	t_rgb	c;

	c.r0 = (0xFF0000 & p0.color) >> 16;
	c.g0 = (0xFF00 & p0.color) >> 8;
	c.b0 = 0xFF & p0.color;
	c.r1 = (0xFF0000 & p1.color) >> 16;
	c.g1 = (0xFF00 & p1.color) >> 8;
	c.b1 = 0xFF & p1.color;
	c.rd = c.r1 - c.r0;
	c.gd = c.g1 - c.g0;
	c.bd = c.b1 - c.b0;
	q.x = abs(p0.x - q.x);
	q.y = abs(p0.y - q.y);
	p0.x = abs(p1.x - p0.x);
	p0.y = abs(p1.y - p0.y);
	if (p0.x > p0.y)
		percent = (float)q.x / (float)p0.x;
	else
		percent = (float)q.y / (float)p0.y;
	c.r0 = round(percent * c.rd + c.r0);
	c.g0 = round(percent * c.gd + c.g0);
	c.b0 = round(percent * c.bd + c.b0);
	return (c.r0 << 16 | c.g0 << 8 | c.b0);
}

int		get_current_color_2(t_loop_data w, t_dim q, t_map_i p0, t_map_i p1)
{
	if (p1.color == -1)
	{
		if (w.gradient == 2)
			p1.color = DEFAULT_COLOR;
		else if (w.gradient == 3)
			p1.color = get_zcolor(p1.z, w.max_z);
	}
	else if (p0.color == -1)
	{
		if (w.gradient == 2)
			p0.color = DEFAULT_COLOR;
		else if (w.gradient == 3)
			p0.color = get_zcolor(p0.z, w.max_z);
	}
	return (get_current_color_3(q, p0, p1));
}

int		get_current_color(t_loop_data w, t_dim q, t_map_i p0, t_map_i p1)
{
	if (w.gradient == 0)
		return (DEFAULT_COLOR);
	else if (w.gradient == 1)
		return (generic_gradient(q, p0, p1, w.max_z));
	if (p0.color == -1 && p1.color == -1)
	{
		if (w.gradient == 2)
			return (DEFAULT_COLOR);
		else if (w.gradient == 3)
			return (generic_gradient(q, p0, p1, w.max_z));
	}
	return (get_current_color_2(w, q, p0, p1));
}
