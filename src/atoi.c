/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:51:19 by jmocniak          #+#    #+#             */
/*   Updated: 2018/09/05 17:34:08 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** fdf_atoi
**
** (With OSX gcc) casting an int to float has unextected behavior 
** >= 16777217
** <= -16777217
*/

float	fdf_atoi(const char *str, int *i)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	if (!(str[*i] >= '0' && str[*i] <= '9'))
		ft_error("error: invalid map");
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + ((int)str[*i] - 48);
		if (result >= 16777217 || result <= -16777217)
			ft_error("error: map z cordinate(s) cannot be larger \
than 16777216 or less than -16777216");
		(*i)++;
	}
	return ((float)(sign * result));
}

int		fdf_atoi_hex(const char *s, int *i)
{
	int	j;
	int	result;

	if (!(s[*i] && s[*i] == '0' && s[++(*i)] && s[(*i)++] == 'x'))
		ft_error("error: invalid map");
	j = 0;
	result = 0;
	while (j < 6 && s[*i + j] && ((s[*i + j] >= '0' && s[*i + j] <= '9') || \
		(s[*i + j] >= 'A' && s[*i + j] <= 'F') || (s[*i + j] >= 'a' && \
		s[*i + j] <= 'f')))
	{
		if (s[*i + j] >= '0' && s[*i + j] <= '9')
			result = result * 16 + (s[*i + j] - '0');
		else if (s[*i + j] >= 'A' && s[*i + j] <= 'F')
			result = result * 16 + (s[*i + j] - 'A' + 10);
		else if (s[*i + j] >= 'a' && s[*i + j] <= 'f')
			result = result * 16 + (s[*i + j] - 'a' + 10);
		j++;
	}
	*i += j;
	if (!ft_isspace(s[*i]) && s[*i] != '\0')
		ft_error("error: invalid map");
	return (result);
}
