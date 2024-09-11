/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:27:56 by matle-br          #+#    #+#             */
/*   Updated: 2024/07/30 19:37:40 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	int		i;
	long	time;

	i = -1;
	while (++i < philo[0].nb_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_last_meal);
		time = get_time() - philo[i].first_action;
		if ((time - philo[i].last_meal) >= philo[i].time_to_die)
		{
			pthread_mutex_unlock(&philo[i].mutex_last_meal);
			print(&philo[i], 4);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
	}
	return (0);
}

int	check_if_all_ate(t_philo *philo)
{
	int	i;
	int	nbr;

	i = -1;
	nbr = 0;
	while (++i < philo[0].nb_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_nb_eat);
		if (philo[0].nb_times_to_eat != -1 && \
		philo[i].meals_eaten >= philo[0].nb_times_to_eat)
		{
			nbr++;
		}
		pthread_mutex_unlock(&philo[i].mutex_nb_eat);
	}
	if (nbr == philo[0].nb_philo)
	{
		return (1);
	}
	return (0);
}

void	monitor_routine(t_data *data)
{
	while (1)
	{
		if (philo_is_dead(data->philos) == 1 \
		|| check_if_all_ate(data->philos) == 1)
		{
			pthread_mutex_lock(&data->mutex_dead);
			data->dead = 1;
			pthread_mutex_unlock(&data->mutex_dead);
			return ;
		}
		usleep(500);
	}
}
