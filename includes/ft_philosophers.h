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
	int				number;
	int				hold_fork_1;
	int				hold_fork_2;
	int				lifespan;
	int				eat_time;
	int				sleep_time;
	int				serving;
	int				*can_eat;
	long			last_ate;
	pthread_t		philo_live;
	pthread_mutex_t	*print;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_t		philo_die;
}					t_philo;


typedef struct s_rules
{
	int				nb_philo;
	int				is_open;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}					t_rules;

/*ft_philosophers*/
void	ft_clear(t_rules *rules, char *str);
int		ft_init(char **av, t_rules *rules, int i);
int		ft_p_thread(char **argv, void *f, t_rules *rules);

/*ft_philosophers_utils.c*/
int		ft_strlen(char *s);
int		ft_strncmp(char *str_1, char *str_2, int n);
int		ft_atoi(const char *str);
void	ft_usleep(unsigned int n);
long	ft_get_time(void);

/*ft_philosophers_utils2.c*/
void	*ft_die(void *arg);
void	*ft_live(void *arg);
void	ft_print_status(long ts, t_philo *philo, char *status);

/*pointeurs sur fonctions*/
typedef int	(*t_mutex_init)(pthread_mutex_t *, const pthread_mutexattr_t *);
typedef int	(*t_mutex_destroy)(pthread_mutex_t *);
typedef int	(*t_create)(pthread_t *, const pthread_attr_t *, \
	void *(*start_routine)(void *), void *);
typedef int	(*t_join)(pthread_t, void **value_ptr);
#endif