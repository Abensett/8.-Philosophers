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

void	*ft_check(void *arg)
{
	long	time;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->can_eat && philo->times != 0)
	{
		time = ft_get_time();
		if (time - philo->last_ate > philo->lifetime)
		{
			ft_print_status(time, philo, "died");
			*philo->can_eat = 0;
			break ;
		}
		ft_usleep(500);
	}
	if (philo->hold_fork_1)
		pthread_mutex_unlock(philo->fork_1);
	if (philo->hold_fork_2)
		pthread_mutex_unlock(philo->fork_2);
	return (0);
}

void	*ft_live(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->can_eat && philo->times != 0)
	{
		philo->times -= 1;
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

void	ft_print_status(long time, t_philo *philo, char *status)
{
	if (!*philo->can_eat)
		return ;
	pthread_mutex_lock(philo->print);
	if (!time)
		time = ft_get_time();
	if (!ft_strncmp("is eating", status, ft_strlen(status)))
		philo->last_ate = time;
	else if (!ft_strncmp("is sleeping", status, ft_strlen(status)))
	{
		philo->hold_fork_1 = 0;
		philo->hold_fork_2 = 0;
	}
	else if (!ft_strncmp("has taken a fork", status, ft_strlen(status)))
	{
		if (!philo->hold_fork_1)
			++philo->hold_fork_1;
		else
			++philo->hold_fork_2;
	}
	if (*philo->can_eat)
		printf("%ld %d %s\n", time, philo->number, status);
	pthread_mutex_unlock(philo->print);
}
