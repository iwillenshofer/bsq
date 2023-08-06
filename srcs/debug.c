/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:08:20 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/06 03:08:34 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdio.h>
#include <time.h>

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

	ss = copy_original(bsq);
	printf("solving. maxx: %lu, area: %lu\n", coord.maxx, coord.area);
	print(ss, coord, bsq->info.key[FULL]);
	printf("best. area: %lu\n", bsq->best.area);
	free_ss(ss);
	ss = copy_original(bsq);
	print(ss, bsq->best, bsq->info.key[FULL]);
	free_ss(ss);
	usleep(50000);
}
