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

#include "ft_philosophers_bonus.h"

void	ft_clear(t_rules *rules, char *str)
{
	if (rules->forks)
		free(rules->forks);
	if (rules->philos)
		free(rules->philos);
	printf("%s\n", str);
}

void	ft_init(char **av, t_rules *rules, int i)
{
	rules->philos[i].number = i + 1;
	rules->philos[i].lifetime = ft_atoi(av[1]);
	rules->philos[i].times = -1;
	rules->philos[i].eat_time = ft_atoi(av[2]);
	rules->philos[i].sleep_time = ft_atoi(av[3]);
	rules->philos[i].last_ate = ft_get_time();
	rules->philos[i].forks = rules->forks;
	rules->philos[i].print = rules->print;
	if (av[4])
		rules->philos[i].times = ft_atoi(av[4]);
}

void	ft_waitpid(t_rules *rules)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < rules->nb_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && (WEXITSTATUS(status) > 0))
		{
			while (i < rules->nb_philos)
				if (++i != WEXITSTATUS(status))
					kill(rules->philos[i - 1].pid, SIGKILL);
			return ;
		}
	}
	return ;
}

int	ft_p_thread(char **av, t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philos)
	{
		ft_init(av, rules, i);
		rules->philos[i].pid = fork();
		if (!rules->philos[i].pid)
		{
			if (pthread_create(&rules->philos[i].philo, 0, ft_live, \
					&rules->philos[i]) \
					|| pthread_create(&rules->philos[i].check, 0, ft_check, \
					&rules->philos[i]) \
					|| pthread_join(rules->philos[i].philo, 0)
				|| pthread_join(rules->philos[i].check, 0))
				return (1);
			free(rules->philos);
			exit(0);
		}
		else if (rules->philos[i].pid < 0)
			return (1);
	}
	ft_waitpid(rules);
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac == 6 || ac == 5)
	{
		rules.nb_philos = ft_atoi(av[1]);
		rules.philos = malloc(sizeof(t_philo) * rules.nb_philos);
		sem_unlink("forks");
		sem_unlink("print");
		rules.forks = sem_open("forks", O_CREAT, S_IRWXU, rules.nb_philos);
		rules.print = sem_open("print", O_CREAT, S_IRWXU, 1);
		if (rules.forks == SEM_FAILED || rules.print == SEM_FAILED
			|| !rules.philos || ft_p_thread(av + 1, &rules))
		{
			if (rules.philos)
				free(rules.philos);
			printf("Error\n");
			return (1);
		}
		sem_close(rules.print);
		sem_close(rules.forks);
		sem_unlink("print");
		sem_unlink("forks");
		free(rules.philos);
	}
	return (0);
}
