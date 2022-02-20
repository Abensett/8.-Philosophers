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

void	ft_clear(t_table *table, char *str)
{
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	printf("%s\n", str);
}

 int	init_philo(char **av, t_table *table, int i)
{
	table->philos[i].seat = i + 1;
	table->philos[i].has_fork_1 = 0;
	table->philos[i].has_fork_2 = 0;
	table->philos[i].lifespan = ft_atoi(av[1]);
	table->philos[i].serving = -1;
	if (av[4])
		table->philos[i].serving = ft_atoi(av[4]);
	table->philos[i].eat_time = ft_atoi(av[2]);
	table->philos[i].sleep_time = ft_atoi(av[3]);
	table->philos[i].can_eat = &table->is_open;
	table->philos[i].last_ate = get_ts();
	table->philos[i].print = &table->print;
	if (table->philos[i].seat == table->nb_philo)
	{
		table->philos[i].fork_1 = &table->forks[0];
		table->philos[i].fork_2 = &table->forks[i];
	}
	else
	{
		table->philos[i].fork_1 = &table->forks[i];
		table->philos[i].fork_2 = &table->forks[i + 1];
	}
	return (1);
}

int	pthread_helper(char **av, void *f, t_table *table)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (++i < table->nb_philo)
	{
		if (f == pthread_mutex_init)
			error = ((t_mutex_init)f)(&table->forks[i], 0);
		else if (f == pthread_create && init_philo(av, table, i))
			error = (((t_create)f)(&table->philos[i].philo_live, 0, live, \
					&table->philos[i]) \
					|| ((t_create)f)(&table->philos[i].philo_die, 0, die, \
					&table->philos[i]));
		else if (f == pthread_join)
			error = (((t_join)f)(table->philos[i].philo_live, 0) \
					|| ((t_join)f)(table->philos[i].philo_die, 0));
		else if (f == pthread_mutex_destroy)
			error = ((t_mutex_destroy)f)(&table->forks[i]);
		if (error)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table table;

	if (ac == 5 || ac == 6)
	{
		table.is_open = 1;
		table.nb_philo = ft_atoi(av[1]);
		table.philos = malloc(sizeof(t_philo) * table.nb_philo);
		table.forks = malloc(sizeof(pthread_mutex_t) * table.nb_philo);
		if (!table.philos || !table.forks)
		{
			ft_clear(&table, "Error");
			return (1);
		}
		if (pthread_mutex_init(&table.print, 0) \
				|| pthread_helper(0, pthread_mutex_init, &table) \
				|| pthread_helper(av + 1, pthread_create, &table) \
				|| pthread_helper(0, pthread_join, &table) \
				|| pthread_helper(0, pthread_mutex_destroy, &table))
		{
			ft_clear(&table, "Error");
			return (1);
		}
	}
	return (0);
}
