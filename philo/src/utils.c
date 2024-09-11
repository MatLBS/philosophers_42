/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:39:13 by matle-br          #+#    #+#             */
/*   Updated: 2024/08/01 15:51:45 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error with gettimeofday");
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	ft_atol(const char *nptr)
{
	int		i;
	long	valeur;
	int		sign;

	i = 0;
	valeur = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		valeur = valeur * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * valeur);
}

int	check_input(char **buf, int ac)
{
	int		i;
	int		j;
	long	value;

	i = 0;
	if (ac != 5 && ac != 6)
		return (0);
	while (buf[++i])
	{
		value = ft_atol(buf[i]);
		if (value > 2147483647 || value < -2147483648)
			return (0);
		j = 0;
		if (buf[i][0] == '-' || buf[i][0] == '+')
			return (0);
		while (buf[i][j])
		{
			if (buf[i][j] < '0' || buf[i][j] > '9')
				return (0);
			j++;
		}
	}
	return (1);
}

void	print(t_philo *philo, int flag)
{
	long	time;

	pthread_mutex_lock(philo->mutex_print);
	time = get_time();
	if (flag == 0)
	{
		printf("%ld %d has taken a fork\n", \
		(time - philo->first_action), philo->id);
	}
	else if (flag == 1)
		printf("%ld %d is eating\n", (time - philo->first_action), philo->id);
	else if (flag == 2)
	{
		printf("%ld %d is sleeping\n", \
		(time - philo->first_action), philo->id);
	}
	else if (flag == 3)
	{
		printf("%ld %d is thinking\n", \
		(time - philo->first_action), philo->id);
	}
	else if (flag == 4)
		printf("%ld %d died\n", (time - philo->first_action), philo->id);
	pthread_mutex_unlock(philo->mutex_print);
}

void	join_threads(t_data *data, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
	}
	return ;
}
