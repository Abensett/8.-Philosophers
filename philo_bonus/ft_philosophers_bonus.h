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

#ifndef FT_PHILOSOPHERS_BONUS_H
# define FT_PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h> 

typedef struct s_philo
{
	int				number;
	int				lifetime;
	int				eat_time;
	int				sleep_time;
	int				times;
	int				pid;
	long			last_ate;
	sem_t			*forks;
	sem_t			*print;
	pthread_t		philo;
	pthread_t		check;
}					t_philo;

typedef struct s_rules
{
	int				nb_philos;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*print;
}					t_rules;

/*ft_philosophers_bonus.c*/
void	ft_clear(t_rules *rules, char *str);
void	ft_init(char **av, t_rules *rules, int i);
void	ft_waipid(t_rules *rules);
int		ft_p_thread(char **argv, t_rules *rules);

/*ft_philosophers_utils_bonus.c*/
int		ft_strlen(char *s);
int		ft_strncmp(char *str_1, char *str_2, int n);
int		ft_atoi(const char *str);
void	ft_usleep(unsigned int n);
long	ft_get_time(void);

/*ft_philosophers_utils2_bonus.c*/
void	*ft_check(void *arg);
void	*ft_live(void *arg);
void	ft_print_status(long ts, t_philo *philo, char *status);

#endif