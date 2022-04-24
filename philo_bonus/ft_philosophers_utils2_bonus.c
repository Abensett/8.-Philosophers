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

#include "ft_philosophers_bonus.h"

void	*ft_check(void *arg)
{
	long	time;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->times != 0)
	{
		time = ft_get_time();
		if (time - philo->last_ate > philo->lifetime)
		{
			ft_print_status(time, philo, "died");
			exit(philo->number);
		}
		ft_usleep(1000);
	}
	return (0);
}

void	*ft_live(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->times != 0)
	{
		philo->times -= 1;
		ft_print_status(0, philo, "is thinking");
		sem_wait(philo->forks);
		ft_print_status(0, philo, "has taken a fork");
		sem_wait(philo->forks);
		ft_print_status(0, philo, "has taken a fork");
		ft_print_status(0, philo, "is eating");
		ft_usleep(philo->eat_time * 1000);
		ft_print_status(0, philo, "is sleeping");
		sem_post(philo->forks);
		sem_post(philo->forks);
		ft_usleep(philo->sleep_time * 1000);
	}
	return (0);
}

void	ft_print_status(long time, t_philo *philo, char *status)
{
	if (!philo->times)
		return ;
	sem_wait(philo->print);
	if (!time)
		time = ft_get_time();
	if (!ft_strncmp("is eating", status, ft_strlen(status)))
		philo->last_ate = time;
	printf("%ld %d %s\n", time, philo->number, status);
	if (ft_strncmp("died", status, ft_strlen(status)))
		sem_post(philo->print);
}
