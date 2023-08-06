/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:40:41 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/06 03:05:36 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

size_t	ft_sslen(char **ss)
{
	size_t	i;

	i = 0;
	while (ss[i])
		i++;
	return (i);
}

void	popfirst(char **ss)
{
	if (!ss || !(*ss))
		return ;
	free(*ss);
	while (*ss)
	{
		*ss = *(ss + 1);
		++ss;
	}
}

void	free_ss(char **ss)
{
	while (ss && ft_sslen(ss))
		popfirst(ss);
	free(ss);
}

char	**pushback(char **ss, char *s)
{
	size_t	slen;
	char	**new;
	size_t	i;

	i = 0;
	slen = 0;
	if (ss)
		slen = ft_sslen(ss);
	new = malloc(sizeof(char *) * (slen + 2));
	if (!new)
	{
		free_ss(ss);
		return (NULL);
	}
	while (i < slen)
	{
		new[i] = ss[i];
		i++;
	}
	new[i] = s;
	new[i + 1] = NULL;
	free(ss);
	return (new);
}

t_bool	loadfd(t_bsq *bsq, int fd)
{
	char	*s;

	bsq->ss = NULL;
	s = get_next_line(fd);
	while (s)
	{
		bsq->ss = pushback(bsq->ss, s);
		s = get_next_line(fd);
	}
	if (!(bsq->ss) || !ft_sslen(bsq->ss))
		return (false);
	return (true);
}
