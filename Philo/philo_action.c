/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:37:35 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/10 15:17:00 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_take_fork(t_philo *philo, int take_next_fork)
{
	pthread_mutex_lock(philo->print_lock);
	if (!take_next_fork)
	{
		printf("%lldms %d has taken a fork %d\n", \
		get_time_in_ms() - (*philo->start_timer), \
		philo->index_philo, (philo->index_philo % philo->nb_philos));
	}
	else
	{
		printf("%lldms %d has taken a fork %d\n", \
		get_time_in_ms() - (*philo->start_timer), \
		philo->index_philo, (philo->index_philo + 1) % philo->nb_philos);
	}
	pthread_mutex_unlock(philo->print_lock);
}

void	time_to_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	printf("%lldms %d is eating \n", \
	get_time_in_ms() - (*philo->start_timer), philo->index_philo);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_lock);
	my_usleep(philo->time_eat);
}

void	time_to_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	printf("%lldms %d is sleeping \n", \
	get_time_in_ms() - (*philo->start_timer), philo->index_philo);
	pthread_mutex_unlock(philo->print_lock);
	my_usleep(philo->time_sleep);
}

void	time_to_think(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	printf("%lldms %d is thinking \n", \
	get_time_in_ms() - (*philo->start_timer), philo->index_philo);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_lock(&philo->tour_lock);
	philo->nb_tours ++;
	pthread_mutex_unlock(&philo->tour_lock);
}

void	time_to_die(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	printf("%lldms %d died\n", \
	get_time_in_ms() - (*philo->start_timer), philo->index_philo);
}
