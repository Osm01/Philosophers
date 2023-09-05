/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:39:39 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/30 21:23:35 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*time_take_fork(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->print_lock);
	printf("%lldms %d has taken a fork\n", \
	get_time_in_ms() - philo->start_timer, philo->index_philo);
	sem_post(philo->print_lock);
	sem_wait(philo->forks);
	sem_wait(philo->print_lock);
	printf("%lldms %d has taken a fork\n", \
	get_time_in_ms() - philo->start_timer, philo->index_philo);
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
	gettimeofday(&philo->last_meal, NULL);
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
}
