/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 02:21:15 by abensett          #+#    #+#             */
/*   Updated: 2022/01/25 02:21:15 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"


void	*die(void *arg)
{
	long	ts;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->can_eat && philo->serving != 0)
	{
		ts = get_ts();
		if (ts - philo->last_ate > philo->lifespan)
		{
			ft_print_status(ts, philo, "has died");
			*philo->can_eat = 0;
			break ;
		}
		ft_usleep(500);
	}
	if (philo->has_fork_1)
		pthread_mutex_unlock(philo->fork_1);
	if (philo->has_fork_2)
		pthread_mutex_unlock(philo->fork_2);
	return (0);
}

void	*live(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->can_eat && philo->serving != 0)
	{
		philo->serving -= 1;
		ft_print_status(0, philo, "is thinking");
		pthread_mutex_lock(philo->fork_1);
		ft_print_status(0, philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_2);
		ft_print_status(0, philo, "has taken a fork");
		ft_print_status(0, philo, "is eating");
		ft_usleep(philo->eat_time * 1000);
		ft_print_status(0, philo, "is sleeping");
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(philo->fork_2);
		ft_usleep(philo->sleep_time * 1000);
	}
	return (0);
}

void	ft_print_status(long ts, t_philo *philo, char *status)
{
	if (!*philo->can_eat)
		return ;
	pthread_mutex_lock(philo->print);
	if (!ts)
		ts = get_ts();
	if (!ft_strncmp("is eating", status, ft_strlen(status)))
		philo->last_ate = ts;
	else if (!ft_strncmp("has taken a fork", status, ft_strlen(status)))
	{
		if (!philo->has_fork_1)
			++philo->has_fork_1;
		else
			++philo->has_fork_2;
	}
	else if (!ft_strncmp("is sleeping", status, ft_strlen(status)))
	{
		philo->has_fork_1 = 0;
		philo->has_fork_2 = 0;
	}
	if (*philo->can_eat)
		printf("%ld %d %s\n", ts, philo->seat, status);
	pthread_mutex_unlock(philo->print);
}

long	get_ts(void)
{
	long			ts;
	struct timeval	s_tv;

	gettimeofday(&s_tv, 0);
	ts = s_tv.tv_sec * 1000 + s_tv.tv_usec / 1000;
	return (ts);
}