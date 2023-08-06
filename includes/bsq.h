/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:48:59 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/06 03:04:43 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 1024
# define EMPTY		0
# define OBSTACLE	1
# define FULL		2
# define BREAK		4

typedef enum e_bool { false, true }	t_bool;

typedef struct s_coord
{
	size_t	x;
	size_t	y;
	size_t	xe;
	size_t	ye;
	size_t	maxx;
	size_t	area;
}	t_coord;

/*
** keys are: empty, obstacle, full, \n, \0
*/
typedef struct t_info
{
	size_t	height;
	size_t	width;
	char	key[5];
}	t_info;

typedef struct s_bsq
{
	char	**ss;
	t_info	info;
	t_coord	best;
}	t_bsq;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *v, size_t size);
char	*ft_strchr(char *s, int c);
void	ft_putstr(char *s);
t_bool	validmap(t_bsq *bsq);
size_t	ft_sslen(char **ss);
void	popfirst(char **ss);
void	ft_strcpy(char *dst, char *src);
t_bool	ft_isnumeric(char c);
void	solve(t_bsq *bsq);
char	*ft_strjoin(char *s, const char *s1);

/*
** parser
*/
t_bool	loadfd(t_bsq *bsq, int fd);
char	**pushback(char **ss, char *s);
size_t	ft_sslen(char **ss);
void	popfirst(char **ss);
void	free_ss(char **ss);

/*
** debug
*/
void	debug(t_bsq *bsq, t_coord coord);
void	print(char **ss, t_coord coord, char full);

#endif
