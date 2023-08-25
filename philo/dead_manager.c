/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:15:40 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/22 15:30:07 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*forks_priority(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->index_philo % 2)
	{
		pthread_mutex_lock(&philo->forks[left_fork]);
		time_take_fork(philo, 0);
		if (philo->nb_philos <= 1)
			return (pthread_mutex_unlock(&philo->forks[left_fork]), \
			(void *) NULL);
		pthread_mutex_lock(&philo->forks[right_fork]);
		time_take_fork(philo, 1);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[right_fork]);
		time_take_fork(philo, 1);
		if (philo->nb_philos <= 1)
			return (pthread_mutex_unlock(&philo->forks[left_fork]), \
			(void *) NULL);
		pthread_mutex_lock(&philo->forks[left_fork]);
		time_take_fork(philo, 0);
	}
	return ((void *) 1);
}

void	detach_all(t_philo *philos, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		pthread_detach(philos[i].philo);
		i ++;
	}
}

void	*dead_by_number_tours(t_philo *philos, int nb_philos, int nb_tours)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (nb_tours >= 0)
	{
		while (i < nb_philos)
		{
			pthread_mutex_lock(&philos[i].tour_lock);
			if (philos[i].nb_tours >= nb_tours)
				count ++;
			pthread_mutex_unlock(&philos[i].tour_lock);
			i ++;
		}
		if (count == nb_philos)
			return (pthread_mutex_lock(philos[i - 1].print_lock), (void *) 1);
	}
	return ((void *) NULL);
}

void	dead_manager(t_philo *philos, int nb_philos, \
char const *argv[], int argc)
{
	int	i;
	int	nb_tours;

	nb_tours = -1;
	if (argc == 6)
		nb_tours = ft_atoi(argv[5]);
	while (1)
	{
		i = 0;
		while (i < nb_philos)
		{
			pthread_mutex_lock(&philos[i].last_meal_lock);
			if (get_time_in_ms() - philos[i].last_meal > philos[i].time_die)
				return (time_to_die(&philos[i]), detach_all(philos, nb_philos));
			pthread_mutex_unlock(&philos[i].last_meal_lock);
			i ++;
		}
		if (dead_by_number_tours(philos, nb_philos, nb_tours))
			return (detach_all(philos, nb_philos));
	}
}
