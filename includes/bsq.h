/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:48:59 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/07 13:53:52 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>

# define BUFFER_SIZE 1024
# define EMPTY		0
# define OBSTACLE	1
# define FULL		2
# define BREAK		4

# ifndef DEBUG
#  define ISDEBUG 0
# else
#  define ISDEBUG 1
# endif

# ifndef RECTANGLE
#  define ISRECT 0
# else
#  define ISRECT 1
# endif

# ifndef MULTITHREAD
#  define ISMULTITHREAD 0
# else
#  define ISMULTITHREAD 1
# endif

# define DEBUG_SPEED 50000

typedef enum e_bool { false, true }	t_bool;

typedef struct s_coord
{
	size_t	x;
	size_t	y;
	size_t	xe;
	size_t	ye;
	size_t	maxx;
	size_t	area;
	t_bool	maxx_found;
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

/*
** the pointer to bsq inside the structure is used ffor
** multithreading, to pass a copy of each self for each
** thread, preventing data races (specially on t_coord best)
** and preventing the use of mutexes, which would slow the
** process down.
** On multithreading, each thread stores its own best,
** which is compared when threads are over.
*/
typedef struct s_bsq
{
	char			**ss;
	t_info			info;
	t_coord			finder;
	t_coord			best;
	pthread_mutex_t	mtxdebug;
	struct s_bsq	*bsq;
}	t_bsq;

/*
** libbft/gnl
*/
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *v, size_t size);
char	*ft_strchr(char *s, int c);
void	ft_putstr(char *s);
size_t	ft_sslen(char **ss);
void	ft_strcpy(char *dst, char *src);
t_bool	ft_isnumeric(char c);
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
** validate
*/
t_bool	validmap(t_bsq *bsq);

/*
** debug
*/
void	debug(t_bsq *bsq, t_coord coord);
void	print(char **ss, t_coord coord, char full);
void	ft_putstr_fd(int fd, char *s);

/*
** solve
*/
t_bool	remaining_area_might_fit(t_bsq *bsq, t_coord coord);
t_bool	square_checkback(t_bsq *bsq, t_coord cd);
void	solve(t_bsq *bsq);
void	probe(t_bsq *bsq, t_coord cd);
void	probesquare(t_bsq *bsq, t_coord cd);

/*
** multithreading
*/
void	mtsolve(t_bsq *bsq);

#endif
