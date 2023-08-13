/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 21:40:11 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/14 01:43:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	ft_atoi(char *s)
{
	long long int	nb;

	nb = 0;
	while (*s)
	{
		if (!ft_isnumeric(*s))
			return (0);
		nb = nb * 10;
		nb += (*s - '0');
		s++;
	}
	return (nb);
}

t_bool	validchar(t_bsq *bsq, char c)
{
	if (c != bsq->info.key[EMPTY]
		&& c != bsq->info.key[OBSTACLE])
		return (false);
	return (true);
}

/*
** checks if line is /n ended
** checks if lines have same size
** checks if characters are valid
** checks if there's at least one empty spot
*/
t_bool	checklines(t_bsq *bsq)
{
	char	**tmp;
	size_t	width;

	tmp = bsq->ss;
	while (*tmp)
	{
		width = ft_strlen(*tmp);
		if (!bsq->info.width)
			bsq->info.width = width;
		if (!width || width != bsq->info.width || (*tmp)[width - 1] != '\n')
			return (false);
		width = 0;
		while (width < bsq->info.width - 1)
		{
			if (!(validchar(bsq, (*tmp)[width])))
				return (false);
			width++;
		}
		tmp++;
	}
	return (true);
}

t_bool	validmap(t_bsq *bsq)
{
	char	*first;
	char	*chars;

	/*
	** this changes are specific for the DASH00 project
	** which does not validate the map nor has the first line.
	*/
	bsq->info.height = ft_sslen(bsq->ss) - 1;
	bsq->info.key[EMPTY] = '.';
	bsq->info.key[OBSTACLE] = 'o';
	bsq->info.key[FULL] = 'x';
	return (true);
	/*
	** original validation starts below
	*/
	first = *(bsq->ss);
	if (ft_strlen(first) < 5)
		return (false);
	chars = first + ft_strlen(first) - 4;
	ft_strcpy(bsq->info.key, chars);
	*chars = 0;
	bsq->info.height = ft_atoi(first);
	if (!bsq->info.height || bsq->info.height != ft_sslen(bsq->ss) - 1)
		return (false);
	if (bsq->info.key[EMPTY] == bsq->info.key[OBSTACLE]
		|| bsq->info.key[EMPTY] == bsq->info.key[FULL]
		|| bsq->info.key[OBSTACLE] == bsq->info.key[FULL])
		return (false);
	popfirst(bsq->ss);
	return (checklines(bsq));
}
