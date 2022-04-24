/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 02:21:09 by abensett          #+#    #+#             */
/*   Updated: 2022/01/25 02:21:09 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (*s1 && *s2 && i < n)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		++s1;
		++s2;
		i++;
	}
	if (i == n)
	{
		--s1;
		--s2;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long		nb;

	sign = 1;
	nb = 0;
	i = 0;
	while ((str[i] > 6 && str[i] < 14) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * sign);
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	ft_usleep(unsigned int n)
{
	long	start_time;
	long	one_time;

	start_time = ft_get_time();
	while (1)
	{
		one_time = ft_get_time();
		if ((one_time - start_time) * 1000 >= n)
			break ;
		usleep(500);
	}
}

long	ft_get_time(void)
{
	long			time;
	struct timeval	timestruct;

	gettimeofday(&timestruct, 0);
	time = timestruct.tv_sec * 1000 + timestruct.tv_usec / 1000;
	return (time);
}
