/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:08:20 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/06 16:40:39 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <time.h>

static void	ft_putnbr(unsigned long number)
{
	char	c;

	if ((number / 10) > 0)
		ft_putnbr(number / 10);
	c = (number % 10) + '0';
	write(1, &c, 1);
}

char	**copy_original(t_bsq *bsq)
{
	char	**ss;
	size_t	size;
	size_t	i;

	size = ft_sslen(bsq->ss);
	ss = malloc(sizeof(char **) * (size + 1));
	if (!ss)
		return (NULL);
	ss[size] = NULL;
	i = 0;
	while (i < size)
	{
		ss[i] = ft_strjoin(NULL, bsq->ss[i]);
		i++;
	}
	return (ss);
}

void	debug(t_bsq *bsq, t_coord coord)
{
	char	**ss;

	if (!ISDEBUG)
		return ;
	ss = copy_original(bsq);
	ft_putstr("\033[2J\033[Hsolving. area: ");
	ft_putnbr(coord.area);
	ft_putstr("\n");
	print(ss, coord, bsq->info.key[FULL]);
	ft_putstr("best. area: ");
	ft_putnbr(bsq->best.area);
	ft_putstr("\n");
	free_ss(ss);
	ss = copy_original(bsq);
	print(ss, bsq->best, bsq->info.key[FULL]);
	free_ss(ss);
	usleep(50000);
}
