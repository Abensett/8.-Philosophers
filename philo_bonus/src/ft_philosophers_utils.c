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

int	ft_strncmp(char *str_1, char *str_2, int n)
{
	int	i;

	i = 0;
	while (*str_1 && *str_2 && i < n)
	{
		if (*str_1 != *str_2)
			return (*(unsigned char *)str_1 - *(unsigned char *)str_2);
		++str_1;
		++str_2;
		++i;
	}
	if (i == n)
	{
		--str_1;
		--str_2;
	}
	return (*(unsigned char *)str_1 - *(unsigned char *)str_2);
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
	int	ret;

	ret = 0;
	while (*s++)
		++ret;
	return (ret);
}

void	ft_usleep(unsigned int n)
{
	long	start_ts;
	long	step_ts;

	start_ts = get_ts();
	while (1)
	{
		step_ts = get_ts();
		if ((step_ts - start_ts) * 1000 >= n)
			break ;
		usleep(500);
	}
}