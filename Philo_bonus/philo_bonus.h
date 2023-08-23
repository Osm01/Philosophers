/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:39:54 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/22 15:49:34 by ouidriss         ###   ########.fr       */
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
# include <wait.h>
# include <fcntl.h>

typedef struct s_philo
{
	pthread_t		philo;
	sem_t			*forks;
	sem_t			*print_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	tour_lock;
	long long		start_timer;
	long long		last_meal;
	int				index_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_philos;
	int				nb_tours;
	int				pid;
	int				nb_eat;
}					t_philo;

int			ft_atoi(const char *str);
void		time_take_fork(t_philo *philo);
void		time_to_eat(t_philo *philo);
void		time_to_sleep(t_philo *philo);
void		time_to_think(t_philo *philo);
void		time_to_die(t_philo *philo);
void		philo_manager(t_philo *philos, int argc, char const *argv[]);
long long	get_time_in_ms(void);
void		my_usleep(long long target_time);
#endif
