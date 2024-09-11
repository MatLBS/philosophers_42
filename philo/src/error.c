/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:59:26 by matle-br          #+#    #+#             */
/*   Updated: 2024/08/01 15:52:33 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_dead);
	if (*philo->dead != 0)
	{
		pthread_mutex_unlock(philo->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->mutex_dead);
	return (0);
}

void	free_all(t_data *data)
{
	int	i;
	int	nbr;

	nbr = data->philos[0].nb_philo;
	if (data->philos)
	{
		i = -1;
		while (++i < nbr)
		{
			pthread_mutex_destroy(&data->philos[i].mutex_nb_eat);
			pthread_mutex_destroy(&data->philos[i].mutex_last_meal);
		}
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		i = -1;
		while (++i < nbr)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->mutex_dead);
	pthread_mutex_destroy(&data->mutex_print);
}
