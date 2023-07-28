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
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo;
    pthread_mutex_t	*forks;
    pthread_mutex_t	*com;
    int             index_philo;
    int 			time_die;
    int				time_eat;
    int				time_sleep;
    int             nb_philos;
    int             should_die;
    long long       start_time;
	long long       current_time;
}					t_philo;

typedef struct s_node
{
    void    *node;
    struct s_node *next;
}               t_node;
int	ft_atoi(const char *str);

#endif
