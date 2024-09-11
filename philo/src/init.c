/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:59:05 by matle-br          #+#    #+#             */
/*   Updated: 2024/08/01 15:55:01 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_data(t_data *data, char **av, int ac)
{
	(void)ac;
	data->dead = 0;
	pthread_mutex_init(&data->mutex_dead, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	data->philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (data->philos == NULL)
	{
		free_all(data);
		return (0);
	}
	return (1);
}

void	init_philo(t_data *data, char **av)
{
	int	i;

	i = -1;
	while (++i < ft_atol(av[1]))
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].first_action = get_time();
		data->philos[i].time_to_die = ft_atol(av[2]);
		data->philos[i].time_to_eat = ft_atol(av[3]);
		data->philos[i].time_to_sleep = ft_atol(av[4]);
		data->philos[i].nb_philo = ft_atol(av[1]);
		data->philos[i].dead = &data->dead;
		data->philos[i].mutex_dead = &data->mutex_dead;
		data->philos[i].mutex_print = &data->mutex_print;
		if (av[5])
			data->philos[i].nb_times_to_eat = ft_atol(av[5]);
		else
			data->philos[i].nb_times_to_eat = -1;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos[0].nb_philo);
	if (data->forks == NULL)
	{
		free(data->philos);
		return ;
	}
	i = -1;
	while (++i < data->philos[0].nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->philos->nb_philo];
		pthread_mutex_init(&data->philos[i].lock, NULL);
		pthread_mutex_init(&data->philos[i].mutex_nb_eat, NULL);
		pthread_mutex_init(&data->philos[i].mutex_last_meal, NULL);
	}
}
