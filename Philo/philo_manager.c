/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:46:34 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/10 15:26:29 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index_philo % 2)
		my_usleep(100);
	while (1)
	{
		time_take_fork(philo, 0);
		pthread_mutex_lock(&philo->forks[philo->index_philo % \
		philo->nb_philos]);
		pthread_mutex_lock(&philo->forks[(philo->index_philo + 1) \
		% philo->nb_philos]);
		time_take_fork(philo, 1);
		time_to_eat(philo);
		pthread_mutex_unlock(&philo->forks[philo->index_philo \
		% philo->nb_philos]);
		pthread_mutex_unlock(&philo->forks[(philo->index_philo + 1) \
		% philo->nb_philos]);
		time_to_sleep(philo);
		time_to_think(philo);
	}
	return (NULL);
}

void	create_philos(t_philo *philos, int nb_philos, \
char const *argv[], int argc)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		philos[i].last_meal = get_time_in_ms();
		if (pthread_create(&philos[i].philo, NULL, \
		philo_routine, (void *) &philos[i]))
			return ;
		i ++;
	}
	return (dead_manager(philos, nb_philos, argv, argc));
}

void	affect_common_mutex(t_philo *philos, int nb_philos, \
pthread_mutex_t	*forks, pthread_mutex_t	*print_lock)
{
	int	i;

	i = 0;
	i = 0;
	while (i < nb_philos)
	{
		philos[i].forks = forks;
		philos[i].print_lock = print_lock;
		i ++;
	}
}

void	mutex_init(t_philo *philos, int nb_philos)
{
	pthread_mutex_t	*last_meal_lock;
	pthread_mutex_t	*tour_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
	int				i;

	i = 0;
	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nb_philos);
	last_meal_lock = (pthread_mutex_t *) \
	malloc(sizeof (pthread_mutex_t) * nb_philos);
	tour_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nb_philos);
	print_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print_lock, NULL);
	while (i < nb_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&last_meal_lock[i], NULL);
		pthread_mutex_init(&tour_lock[i], NULL);
		philos[i].last_meal_lock = last_meal_lock[i];
		philos[i].tour_lock = tour_lock[i];
		i ++;
	}
	affect_common_mutex(philos, nb_philos, forks, print_lock);
}

void	philo_manager(t_philo *philos, char const *argv[], int argc)
{
	int			i;
	int			nb_philos;
	long long	start_timer;

	nb_philos = ft_atoi(argv[1]);
	mutex_init(philos, nb_philos);
	start_timer = get_time_in_ms();
	i = 0;
	while (i < nb_philos)
	{
		philos[i].index_philo = i;
		philos[i].nb_philos = nb_philos;
		philos[i].time_die = ft_atoi(argv[2]);
		philos[i].time_eat = ft_atoi(argv[3]);
		philos[i].time_sleep = ft_atoi(argv[4]);
		philos[i].start_timer = &start_timer;
		philos[i ++].nb_tours = 0;
	}
	return (create_philos(philos, nb_philos, argv, argc));
}
