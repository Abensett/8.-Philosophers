/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:49:33 by abensett          #+#    #+#             */
/*   Updated: 2022/01/25 23:49:33 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				seat;
	int				has_fork_1;
	int				has_fork_2;
	int				lifespan;
	int				serving;
	int				eat_time;
	int				sleep_time;
	int				*can_eat;
	long			last_ate;
	pthread_t		philo_die;
	pthread_t		philo_live;
	pthread_mutex_t	*print;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
}					t_philo;


typedef struct s_table
{
	int				nb_philo;
	int				is_open;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}					t_table;

/*ft_philosophers*/
void	ft_clear(t_table *table, char *str);
int		init_philo(char **av, t_table *table, int i);
int		pthread_helper(char **argv, void *f, t_table *table);

/*ft_philosophers_utils.c*/
int		ft_strlen(char *s);
int		ft_strncmp(char *str_1, char *str_2, int n);
int		ft_atoi(const char *str);
void	ft_usleep(unsigned int n);

/*ft_philosophers_utils2.c*/
void	*die(void *arg);
void	*live(void *arg);
void	ft_print_status(long ts, t_philo *philo, char *status);
long	get_ts(void);

/*pointeurs sur fonction*/
typedef int	(*t_mutex_init)(pthread_mutex_t *, const pthread_mutexattr_t *);
typedef int	(*t_create)(pthread_t *, const pthread_attr_t *, \
	void *(*start_routine)(void *), void *);
typedef int	(*t_join)(pthread_t, void **value_ptr);
typedef int	(*t_mutex_destroy)(pthread_mutex_t *);

#endif