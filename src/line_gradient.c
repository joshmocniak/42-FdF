/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_gradient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:55:19 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/05 17:39:46 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		color_from_gradient(float percent, int c_idx0, int c_idx1)
{
	t_rgb	c;
	int		grad[COLORS_IN_GRADIENT];

	grad[0] = 0x4400ff;
	grad[1] = 0x17571a;
	grad[2] = 0x3651ff;
	grad[3] = 0xff0000;
	grad[4] = 0xff1fff;
	c.r0 = (0xFF0000 & grad[c_idx0]) >> 16;
	c.g0 = (0xFF00 & grad[c_idx0]) >> 8;
	c.b0 = 0xFF & grad[c_idx0];
	c.r1 = (0xFF0000 & grad[c_idx1]) >> 16;
	c.g1 = (0xFF00 & grad[c_idx1]) >> 8;
	c.b1 = 0xFF & grad[c_idx1];
	c.rd = c.r1 - c.r0;
	c.gd = c.g1 - c.g0;
	c.bd = c.b1 - c.b0;
	c.r0 = (c.rd * percent) + c.r0;
	c.g0 = (c.gd * percent) + c.g0;
	c.b0 = (c.bd * percent) + c.b0;
	return (c.r0 << 16 | c.g0 << 8 | c.b0);
}

/*
** get_zcolor
** finds the percentage of a given z coordinate of the largest/max
** z coordinate in the map.  then determines between which 2 colors
** in the gradient the color the point in the line will be.
** then determines the percent between these 2 colors that the
** returned color should be.
*/

int		get_zcolor(float z, int max_z)
{
	float	percent;
	int		c_idx0;
	int		c_idx1;

	percent = (fabsf(z) / (float)max_z) * (COLORS_IN_GRADIENT - 1);
	c_idx0 = floor(percent);
	c_idx1 = ceil(percent);
	percent = percent - c_idx0;
	return (color_from_gradient(percent, c_idx0, c_idx1));
}

/*
** generic_gradient
** finds the z coordinate of a point in a line from one z coordinate
** to another z coordinate.
*/

int		generic_gradient(t_dim q, t_map_i p0, t_map_i p1, int max_z)
{
	float	percent;
	float	z;

	q.x = abs(p0.x - q.x);
	q.y = abs(p0.y - q.y);
	p0.x = abs(p1.x - p0.x);
	p0.y = abs(p1.y - p0.y);
	if (p0.x > p0.y && p0.x != 0)
		percent = (float)q.x / (float)p0.x;
	else if (p0.y != 0)
		percent = (float)q.y / (float)p0.y;
	else
		percent = 0;
	z = (p1.z - p0.z) * percent + p0.z;
	return (get_zcolor(z, max_z));
}
