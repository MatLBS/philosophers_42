/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matle-br <matle-br@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:52:05 by matle-br          #+#    #+#             */
/*   Updated: 2024/08/01 15:51:03 by matle-br         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	lock;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;
	int				last_meal;
	int				nb_philo;
	long			first_action;
	int				*dead;
	int				meals_eaten;
	pthread_mutex_t	mutex_nb_eat;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	*mutex_dead;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	int				dead;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

/* actions_routine.c */
int		lock_forks(t_philo *philo);
int		ft_eat(t_philo	*philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);

/* error.c */
int		check_is_dead(t_philo *philo);
void	free_all(t_data *data);

/* init.c */
int		init_data(t_data *data, char **av, int ac);
void	init_philo(t_data *data, char **av);
void	init_mutex(t_data *data);

/* monitor.c */
int		philo_is_dead(t_philo *philo);
int		check_if_all_ate(t_philo *philo);
void	monitor_routine(t_data *data);

/* threads.c */
void	*philo_routine(t_philo *philo);
void	create_threads(t_data *data);
void	*philo_routine_one(t_philo *philo);
void	create_one_philo(t_data *data);

/* utils.c */
long	get_time(void);
long	ft_atol(const char *nptr);
int		check_input(char **buf, int ac);
void	print(t_philo *philo, int flag);
void	join_threads(t_data *data, int nbr);

#endif
