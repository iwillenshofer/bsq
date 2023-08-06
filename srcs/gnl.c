/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:49:11 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/05 20:46:33 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

char	*ft_strjoin(char *s, const char *s1)
{
	size_t	sa;
	char	*new;
	size_t	i;

	sa = 0;
	if (s)
		sa = ft_strlen(s);
	new = malloc(sa + ft_strlen(s1) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < sa)
	{
		new[i] = s[i];
		i++;
	}
	while (*s1)
	{
		new[i] = *s1;
		s1++;
		i++;
	}
	new[i] = 0;
	free(s);
	return (new);
}

void	ft_bzero(void *v, size_t size)
{
	size_t	i;
	char	*s;

	s = (char *)(v);
	i = 0;
	while (i < size)
	{
		s[i] = 0;
		i++;
	}
}

char	*read_line(char **s, int fd)
{
	int		ret;
	char	buf[BUFFER_SIZE + 1];
	char	*pos;
	char	*line;
	char	*tmp;

	if (!*s)
		*s = ft_strjoin(NULL, "");
	while (!(ft_strchr(*s, '\n')))
	{
		ft_bzero(buf, sizeof(buf));
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
			return (NULL);
		*s = ft_strjoin(*s, buf);
	}
	pos = ft_strchr(*s, '\n');
	*pos = 0;
	line = ft_strjoin(NULL, *s);
	line = ft_strjoin(line, "\n");
	tmp = *s;
	*s = ft_strjoin(NULL, ++pos);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s = NULL;
	char		*line;

	line = read_line(&s, fd);
	if (!line)
	{
		if (ft_strlen(s))
			line = ft_strjoin(NULL, s);
		free(s);
		s = NULL;
	}
	return (line);
}
