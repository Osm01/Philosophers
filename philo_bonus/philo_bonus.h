/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:19:12 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/12 18:02:51 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_philo
{
	pthread_t		philo;
	sem_t			*forks;
	long long		*start_timer;
	long long		last_meal;
	int				index_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_philos;
	int				nb_tours;
}					t_philo;

#endif PHILO_BONUS_H