/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:44:41 by abensett          #+#    #+#             */
/*   Updated: 2022/01/15 19:44:41 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	ft_clear(t_rules *rules, char *str)
{
	if (rules->forks)
		free(rules->forks);
	if (rules->philos)
		free(rules->philos);
	printf("%s\n", str);
}

 int	ft_init(char **av, t_rules *rules, int i)
{
	rules->philos[i].number = i + 1;
	rules->philos[i].hold_fork_1 = 0;
	rules->philos[i].hold_fork_2 = 0;
	rules->philos[i].lifespan = ft_atoi(av[1]);
	rules->philos[i].serving = -1;
	if (av[4])
		rules->philos[i].serving = ft_atoi(av[4]);
	rules->philos[i].eat_time = ft_atoi(av[2]);
	rules->philos[i].sleep_time = ft_atoi(av[3]);
	rules->philos[i].can_eat = &rules->is_open;
	rules->philos[i].last_ate = ft_get_time();
	rules->philos[i].print = &rules->print;
	if (rules->philos[i].number == rules->nb_philo)
	{
		rules->philos[i].fork_1 = &rules->forks[0];
		rules->philos[i].fork_2 = &rules->forks[i];
	}
	else
	{
		rules->philos[i].fork_1 = &rules->forks[i];
		rules->philos[i].fork_2 = &rules->forks[i + 1];
	}
	return (1);
}

int	ft_p_thread(char **av, void *f, t_rules *rules)
{
	int	i;
	int	fail;
 
	i = -1;
	fail = 0;
	while (++i < rules->nb_philo)
	{
		if (f == pthread_mutex_init)
			fail = ((t_mutex_init)f)(&rules->forks[i], 0);
		else if (f == pthread_create && ft_init(av, rules, i))
			fail = (((t_create)f)(&rules->philos[i].philo_live, 0, ft_live, \
					&rules->philos[i]) \
					|| ((t_create)f)(&rules->philos[i].philo_die, 0, ft_die, \
					&rules->philos[i]));
		else if (f == pthread_join)
			fail = (((t_join)f)(rules->philos[i].philo_live, 0) \
					|| ((t_join)f)(rules->philos[i].philo_die, 0));
		else if (f == pthread_mutex_destroy)
			fail = ((t_mutex_destroy)f)(&rules->forks[i]);
		if (fail)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_rules rules;

	if (ac == 6 || ac == 5)
	{
		rules.nb_philo = ft_atoi(av[1]);
		rules.is_open = 1;
		rules.philos = malloc(sizeof(t_philo) * rules.nb_philo);
		rules.forks = malloc(sizeof(pthread_mutex_t) * rules.nb_philo);
		if (!rules.philos || !rules.forks)
		{
			ft_clear(&rules, "Error");
			return (1);
		}
		if (pthread_mutex_init(&rules.print, 0) \
				|| ft_p_thread(0, pthread_mutex_init, &rules) \
				|| ft_p_thread(av + 1, pthread_create, &rules) \
				|| ft_p_thread(0, pthread_join, &rules) \
				|| ft_p_thread(0, pthread_mutex_destroy, &rules))
		{
			ft_clear(&rules, "Error");
			return (1);
		}
	}
	return (0);
}
