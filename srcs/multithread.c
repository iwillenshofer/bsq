/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:32:40 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/07 14:06:32 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/*
** just send probes to each point on the line belonging to this particular
** thread.
*/
static void	*multithreading(void *vbsq)
{
	t_coord	coord;
	t_bsq	*bsq;

	bsq = (t_bsq *)vbsq;
	coord = bsq->finder;
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
			return (NULL);
		coord.x++;
	}
	return (NULL);
}

/*
** waits for all the threads to finish and compare results.
*/
void	collectthreads(t_bsq *bsq, pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < bsq->info.height)
	{
		pthread_join((threads[i]), NULL);
		if (bsq->bsq[i].best.area > bsq->best.area)
			bsq->best = bsq->bsq[i].best;
		else if (bsq->bsq[i].best.area
			== bsq->best.area && bsq->best.y > bsq->bsq[i].best.y)
			bsq->best = bsq->bsq[i].best;
		i++;
	}
}

/*
** just like the original solve(), but for each y (each line of the map),
** we start a different thread.
** The multithreading() function will be responsible to call the probes
** on each point of the line belonging to that thread.
*/
void	mtsolve(t_bsq *bsq)
{
	t_coord		coord;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * bsq->info.height);
	bsq->bsq = malloc(sizeof(t_bsq) * bsq->info.height);
	pthread_mutex_init(&(bsq->mtxdebug), NULL);
	if (!(threads) || !(bsq->bsq))
		return ;
	ft_bzero(&coord, sizeof(coord));
	while (coord.y < bsq->info.height)
	{
		coord.x = 0;
		bsq->finder = coord;
		bsq->bsq[coord.y] = *bsq;
		pthread_create(&(threads[coord.y]), NULL, multithreading, (void *)bsq);
		coord.y++;
	}
	collectthreads(bsq, threads);
	free(bsq->bsq);
	free(threads);
	pthread_mutex_destroy(&(bsq->mtxdebug));
}
