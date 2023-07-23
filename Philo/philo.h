/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:25:35 by ouidriss          #+#    #+#             */
/*   Updated: 2023/07/22 19:20:44 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	forks;
	int 			time_die;
	int				time_eat;
	int				time_sleep;
	int				prio;
}					t_philo;

typedef struct s_philosophers
{
	t_philo	*philos;
}			t_philosopher;

int	ft_atoi(const char *str);

#endif
