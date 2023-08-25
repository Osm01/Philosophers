/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:39:39 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/22 15:44:08 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*time_take_fork(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->print_lock);
	printf("%lldms %d has taken a fork %d\n", \
	get_time_in_ms() - philo->start_timer, philo->index_philo, \
	(philo->index_philo % philo->nb_philos));
	sem_post(philo->print_lock);
	if (philo->nb_philos <= 1)
		return ((void *) NULL);
	sem_wait(philo->forks);
	sem_wait(philo->print_lock);
	printf("%lldms %d has taken a fork %d\n", \
	get_time_in_ms() - philo->start_timer, philo->index_philo, \
	((philo->index_philo + 1) % philo->nb_philos));
	sem_post(philo->print_lock);
	return ((void *) 1);
}

void	time_to_eat(t_philo *philo)
{
	sem_wait(philo->print_lock);
	printf("%lldms %d is eating \n", \
	get_time_in_ms() - philo->start_timer, philo->index_philo);
	sem_post(philo->print_lock);
	my_usleep(philo->time_eat);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_lock);
}

void	time_to_sleep(t_philo *philo)
{
	sem_wait(philo->print_lock);
	printf("%lldms %d is sleeping \n", \
	get_time_in_ms() - philo->start_timer, philo->index_philo);
	sem_post(philo->print_lock);
	my_usleep(philo->time_sleep);
}

void	time_to_think(t_philo *philo)
{
	sem_wait(philo->print_lock);
	printf("%lldms %d is thinking \n", \
	get_time_in_ms() - philo->start_timer, philo->index_philo);
	sem_post(philo->print_lock);
	pthread_mutex_lock(&philo->tour_lock);
	philo->nb_tours ++;
	pthread_mutex_unlock(&philo->tour_lock);
}

void	time_to_die(t_philo *philo)
{
	sem_wait(philo->print_lock);
	printf("%lldms %d died\n", \
	get_time_in_ms() - philo->start_timer, philo->index_philo);
}
