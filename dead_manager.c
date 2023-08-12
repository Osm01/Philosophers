/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:15:40 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/12 13:57:11 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
				return (time_to_die(&philos[i]));
			pthread_mutex_unlock(&philos[i].last_meal_lock);
			i ++;
		}
		if (dead_by_number_tours(philos, nb_philos, nb_tours))
			return ;
	}
}

void	free_all(t_helper *helper)
{
	free(helper->print_lock);
	free(helper->forks);
	free(helper->tour_lock);
	free(helper->last_meal_lock);
	free(helper);
}
