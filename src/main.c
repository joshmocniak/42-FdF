/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:25:52 by jmocniak          #+#    #+#             */
/*   Updated: 2018/06/20 00:07:38 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	int			fd;
	t_map		**raw_map;
	t_dim		dim;

	if (argc != 2)
	{
		ft_putendl("usage: ./fdf file");
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr(strerror(errno));
		return (1);
	}
	raw_map = parse(fd, &dim);
	if (close(fd) == -1)
	{
		ft_putstr(strerror(errno));
		return (1);
	}
	draw(raw_map, dim);
	return (0);
}
