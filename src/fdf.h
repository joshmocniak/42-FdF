/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:28:44 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/06 01:15:16 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../42-libft/libft.h"
# include "../42-get_next_line/get_next_line.h"
# include "../libmlx/mlx.h"
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

# define STR_INCR 100
# define TILT 45
# define WIN_HEIGHT 768.0
# define WIN_WIDTH 1024.0
# define MARGIN 100
# define Z_SCALE .2
# define DEFAULT_COLOR 0xFF7F00
# define COLORS_IN_GRADIENT 5
# define UP_ARROW 126
# define DOWN_ARROW 125
# define ESC 53

typedef struct	s_rgb
{
	int			r0;
	int			g0;
	int			b0;
	int			r1;
	int			g1;
	int			b1;
	int			rd;
	int			bd;
	int			gd;
}				t_rgb;

typedef struct	s_map
{
	float		x;
	float		y;
	float		z;
	int			color;
}				t_map;

typedef struct	s_map_i
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_map_i;

typedef struct	s_dim
{
	int			x;
	int			y;
}				t_dim;

typedef struct	s_projdat
{
	float		z_scale;
	int			tilt;
}				t_projdat;

typedef struct	s_loop_data
{
	void		*mlx;
	void		*win;
	t_map		**raw_map;
	t_dim		dim;
	void		(*to_projection)(t_map **raw_map, t_map **map, t_dim dim, \
			t_projdat zscale_tilt);
	t_projdat	zscale_tilt;
	int			max_z;
	int			contains_color;
	int			gradient;
	int			rotate;
}				t_loop_data;

typedef struct	s_map_ptrs
{
	t_map		map;
	t_map		iso;
}				t_map_ptrs;

typedef struct	s_scale_data
{
	float		scale;
	float		pad_x;
	float		pad_y;
}				t_scale_data;

typedef struct	s_line_data
{
	t_dim		d;
	t_dim		s;
	t_map_i		p0;
	t_map_i		p1;
	t_dim		q;
}				t_line_data;

t_map			**parse(int fd, t_dim *dim);
void			ft_error(const char *str);
void			draw(t_map **map, t_dim dim);
void			line(t_loop_data mlx, t_map p0, t_map p1);
t_map			**make_empty_map(t_dim dim);
void			to_isometric(t_map **in, t_map **out, t_dim dim, t_projdat dat);
void			to_generic_iso(t_map **in, t_map **out, t_dim dim, \
		t_projdat dat);
void			free_map(t_map **map, int rows);
void			scale_to_fit_rectangle(t_map **map, t_dim dim, float rect_h, \
		float rect_w);
void			translate(t_map**map, t_dim dim, int offset_y, int offset_x);
int				get_max_z(t_map **map, t_dim dim);
int				contains_color(t_map **map, t_dim dim);
int				key_hook(int keycode, t_loop_data *w);
int				get_current_color(t_loop_data w, t_dim q, t_map_i p0, \
		t_map_i p1);
int				generic_gradient(t_dim q, t_map_i p0, t_map_i p1, int max_z);
float			fdf_atoi(const char *str, int *i);
int				fdf_atoi_hex(const char *s, int *i);
int				get_zcolor(float z, int max_z);
void			draw_map(t_loop_data *w);

#endif
