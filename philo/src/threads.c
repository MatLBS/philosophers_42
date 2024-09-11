/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:32:01 by matle-br          #+#    #+#             */
/*   Updated: 2024/07/30 16:15:49 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_routine(t_philo *philo)
{
	int	flag;

	if (philo->id % 2 == 0)
		ft_think(philo);
	while (1)
	{
		flag = ft_eat(philo);
		if (flag == 1)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			break ;
		}
		if (flag == 2)
			break ;
		flag = ft_sleep(philo);
		if (flag == 1)
			break ;
		flag = ft_think(philo);
		if (flag == 1)
			break ;
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->philos[0].nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, \
		(void *(*)(void *))philo_routine, &data->philos[i]) != 0)
		{
			printf("Error creating philosopher thread %d\n", i);
			free_all(data);
			return ;
		}
	}
}

void	*philo_routine_one(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print(philo, 0);
	usleep(philo->time_to_die * 1000);
	print(philo, 4);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	create_one_philo(t_data *data)
{
	if (pthread_create(&data->philos[0].thread, NULL, \
	(void *(*)(void *))philo_routine_one, &data->philos[0]) != 0)
	{
		printf("Error creation thread with one philo.\n");
		free_all(data);
		return ;
	}
	pthread_join(data->philos[0].thread, NULL);
	free_all(data);
	return ;
}
