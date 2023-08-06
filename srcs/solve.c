/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:43:23 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/06 16:55:06 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/*
** calculates the remaining area to check if it is still possible
** for a larger rectangle to be found.
*/
t_bool	remaining_area_might_fit(t_bsq *bsq, t_coord coord)
{
	size_t	remaining_area;

	remaining_area = ((bsq->info.width - 1)) * ((bsq->info.height - coord.y));
	if (remaining_area <= bsq->best.area)
		return (false);
	return (true);
}

/*
** the algorythm is quite simple:
** at point x:0, y:0, supposing p is a ., probe for the right most step...
** at point x:0, y:1, probe for the right most step, and so on.
*/
void	probe(t_bsq *bsq, t_coord cd)
{
	cd.maxx_found = false;
	if (!bsq->best.area)
		bsq->best = cd;
	while (cd.ye < bsq->info.height)
	{
		cd.xe = cd.x;
		while (cd.xe < bsq->info.width - 1
			&& (!cd.maxx_found || cd.xe < cd.maxx))
		{
			if (bsq->ss[cd.ye][cd.xe] != bsq->info.key[EMPTY])
			{
				cd.maxx_found = true;
				cd.maxx = cd.xe;
				break ;
			}
			cd.area = (1 + (cd.xe - cd.x)) * (1 + (cd.ye - cd.y));
			if (cd.area > bsq->best.area)
				bsq->best = cd;
			debug(bsq, cd);
			if (!remaining_area_might_fit(bsq, cd))
				return ;
			cd.xe++;
		}
		cd.ye++;
	}
}

/*
** since we incremented X and Y by one, now we just check if this
** this new line and column we expanded into are "empty"
*/
t_bool	square_checkback(t_bsq *bsq, t_coord cd)
{
	size_t	x;
	size_t	y;

	x = cd.xe;
	y = cd.ye;
	while (x >= cd.x)
	{
		if (bsq->ss[cd.ye][x] != bsq->info.key[EMPTY])
			return (false);
		if (x == cd.x)
			break ;
		x--;
	}
	while (y >= cd.y)
	{
		if (bsq->ss[y][cd.xe] != bsq->info.key[EMPTY])
			return (false);
		if (y == cd.y)
			break ;
		y--;
	}
	return (true);
}

void	probesquare(t_bsq *bsq, t_coord cd)
{
	t_bool	ms;

	ms = false;
	if (!bsq->best.area)
		bsq->best = cd;
	while (cd.ye < bsq->info.height && cd.xe < bsq->info.width - 1)
	{
		if (!square_checkback(bsq, cd))
			return ;
		cd.area = (1 + (cd.xe - cd.x)) * (1 + (cd.ye - cd.y));
		if (cd.area > bsq->best.area)
			bsq->best = cd;
		debug(bsq, cd);
		if (!remaining_area_might_fit(bsq, cd))
			return ;
		cd.xe++;
		cd.ye++;
	}
}

void	solve(t_bsq *bsq)
{
	t_coord	coord;

	ft_bzero(&coord, sizeof(coord));
	while (coord.y < bsq->info.height)
	{
		coord.x = 0;
		while (coord.x < bsq->info.width - 1)
		{
			if (bsq->ss[coord.y][coord.x] == bsq->info.key[EMPTY])
			{
				coord.area = 1;
				coord.ye = coord.y;
				coord.xe = coord.x;
				if (ISRECT)
					probe(bsq, coord);
				else
					probesquare(bsq, coord);
			}
			if (!remaining_area_might_fit(bsq, coord))
				return ;
			coord.x++;
		}
		coord.y++;
	}
}
