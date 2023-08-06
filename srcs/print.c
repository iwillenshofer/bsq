/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:20:45 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/06 13:55:55 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	placefull(char **ss, t_coord coord, char full)
{
	size_t	x;
	size_t	y;

	y = coord.y;
	if (!coord.area)
		return ;
	while (y <= coord.ye)
	{
		x = coord.x;
		while (x <= coord.xe)
		{
			ss[y][x] = full;
			x++;
		}
		y++;
	}
}

void	print(char **ss, t_coord coord, char full)
{
	size_t	size;
	size_t	i;

	if (!ss)
		return ;
	size = ft_sslen(ss);
	placefull(ss, coord, full);
	i = 0;
	while (i < size)
	{
		ft_putstr(ss[i]);
		i++;
	}
}
