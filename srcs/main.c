/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:48:56 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/06 21:42:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

t_bool	run_bsq(t_bsq *bsq, int fd)
{
	if (!(loadfd(bsq, fd)))
		return (false);
	else if (!(validmap(bsq)))
		return (false);
	if (ISMULTITHREAD)
		mtsolve(bsq);
	else
		solve(bsq);
	print(bsq->ss, bsq->best, bsq->info.key[FULL]);
	return (true);
}

int	main(int argc, char **argv)
{
	t_bsq	bsq;
	int		fd;

	argv++;
	fd = 0;
	while ((argc > 1 && *(argv)) || argc == 1)
	{
		ft_bzero(&bsq, sizeof(t_bsq));
		if (argc > 1)
			fd = open(*argv, O_RDONLY);
		if (fd == -1 || !(run_bsq(&bsq, fd)))
			ft_putstr_fd(2, "map error\n");
		free_ss(bsq.ss);
		if (argc == 1)
			break ;
		argv++;
		if (*argv && argc > 1)
			ft_putstr("\n");
	}
}
