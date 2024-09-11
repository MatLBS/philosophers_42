/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:53:01 by matle-br          #+#    #+#             */
/*   Updated: 2024/08/01 15:54:01 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_data			data;

	if (!check_input(av, ac))
	{
		printf("Invalid input. The correct input is of type <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (!init_data(&data, av, ac))
		return (0);
	init_philo(&data, av);
	init_mutex(&data);
	if (ft_atol(av[1]) == 1)
	{
		create_one_philo(&data);
		return (0);
	}
	else
		create_threads(&data);
	monitor_routine(&data);
	join_threads(&data, ft_atol(av[1]));
	free_all(&data);
	return (0);
}
