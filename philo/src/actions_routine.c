/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:34:35 by matle-br          #+#    #+#             */
/*   Updated: 2024/07/30 11:52:07 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		if (check_is_dead(philo) == 1)
		{
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}
		print(philo, 0);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		if (check_is_dead(philo) == 1)
		{
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
		print(philo, 0);
		pthread_mutex_lock(philo->l_fork);
	}
	return (0);
}

int	ft_eat(t_philo	*philo)
{
	long	time;

	if (lock_forks(philo) != 0)
		return (2);
	if (check_is_dead(philo) == 1)
		return (1);
	print(philo, 0);
	time = get_time();
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = time - philo->first_action;
	pthread_mutex_unlock(&philo->mutex_last_meal);
	pthread_mutex_lock(&philo->mutex_nb_eat);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->mutex_nb_eat);
	if (check_is_dead(philo) == 1)
		return (1);
	print(philo, 1);
	if (philo->time_to_eat > philo->time_to_die)
		usleep(philo->time_to_die * 1000);
	else
		usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (check_is_dead(philo) == 1)
		return (1);
	print(philo, 2);
	if (philo->time_to_sleep > philo->time_to_die)
		usleep(philo->time_to_die * 1000);
	else if (philo->time_to_eat > philo->time_to_die)
		usleep(philo->time_to_die - philo->time_to_sleep);
	else
		usleep(philo->time_to_sleep * 1000);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (check_is_dead(philo) == 1)
		return (1);
	print(philo, 3);
	if (philo->time_to_eat > philo->time_to_die)
		usleep(philo->time_to_die * 1000);
	else if (philo->time_to_sleep > philo->time_to_die)
		usleep((philo->time_to_die - philo->time_to_eat) * 1000);
	else
		usleep(((philo->time_to_die - \
		(philo->time_to_eat + philo->time_to_sleep)) / 2) * 1000);
	return (0);
}
