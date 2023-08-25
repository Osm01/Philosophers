/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:25:35 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/24 14:12:38 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	tour_lock;
	long long		*start_timer;
	long long		last_meal;
	int				index_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_philos;
	int				nb_tours;
}					t_philo;

int			ft_atoi(const char *str);
void		time_take_fork(t_philo *philo, int take_next_fork);
void		time_to_eat(t_philo *philo);
void		time_to_sleep(t_philo *philo);
void		time_to_think(t_philo *philo);
void		time_to_die(t_philo *philo);
void		philo_manager(t_philo *philos, char const *argv[], int argc);
long long	get_time_in_ms(void);
void		my_usleep(long long target_time);
void		dead_manager(t_philo *philos, int nb_philos, \
			char const *argv[], int argc);
void		*forks_priority(t_philo *philo, int left_fork, int right_fork);
#endif
