/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:24:53 by ouidriss          #+#    #+#             */
/*   Updated: 2023/07/28 19:34:58 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time_in_ms()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
}

void	my_usleep(long long target_time)
{
	long long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < target_time)
		usleep(100);
}

void    time_take_fork(t_philo *philo)
{
    pthread_mutex_lock(&(*philo->com));
    printf("%lld %d has taken a fork \n", philo->start_time, philo->index_philo);
    pthread_mutex_unlock(&(*philo->com));
}

void	time_to_eat(t_philo *philo)
{
    pthread_mutex_lock(&(*philo->com));
	printf("%lld %d is eating \n", philo->start_time, philo->index_philo);
    pthread_mutex_unlock(&(*philo->com));
	philo->current_time = get_time_in_ms();
	my_usleep(philo->time_eat);
	philo->start_time += (get_time_in_ms() - philo->current_time);
}

void	time_to_sleep(t_philo *philo)
{
    pthread_mutex_lock(&(*philo->com));
	printf("%lld %d is sleeping \n", philo->start_time, philo->index_philo);
    pthread_mutex_unlock(&(*philo->com));
    philo->current_time = get_time_in_ms();
    my_usleep(philo->time_sleep);
	philo->start_time += (get_time_in_ms() - philo->current_time);
}

void	time_to_think(t_philo *philo)
{
    pthread_mutex_lock(&(*philo->com));
	printf("%lld %d is thinking \n", philo->start_time, philo->index_philo);
    pthread_mutex_unlock(&(*philo->com));
    philo->current_time = get_time_in_ms();
    my_usleep(philo->time_die - (philo->time_eat + philo->time_sleep));
	philo->start_time += (get_time_in_ms() - philo->current_time);
}

void	time_to_die(t_philo *philo)
{
    pthread_mutex_lock(&(*philo->com));
    printf("%lld %d died\n", philo->start_time, philo->index_philo);
    pthread_mutex_unlock(&(*philo->com));
}

void	*philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if ((philo->index_philo + 1) % 2)
        my_usleep(philo->time_eat);
    pthread_mutex_lock(&philo->forks[(philo->index_philo + 1) % philo->nb_philos]);
    pthread_mutex_lock(&philo->forks[philo->index_philo % philo->nb_philos]);
    time_take_fork(philo);
    time_to_eat(philo);
    pthread_mutex_unlock(&philo->forks[(philo->index_philo + 1) % philo->nb_philos]);
    pthread_mutex_unlock(&philo->forks[philo->index_philo % philo->nb_philos]);
    time_to_sleep(philo);
    time_to_think(philo);
	return (NULL);
}

void	create_philos(t_philo *philos, int nb_philos)
{
	int	i;
    int y;

    i = 0;
    y = 1;
  
        while (i < nb_philos)
        {
            if (pthread_create(&philos[i].philo, NULL, philo_routine, (void *) &philos[i]))
                return ;
            i ++;
        }
        while(1){
            
        }
        
    return ;
}

void	philo_manager(t_philo *philos, char const *argv[], pthread_mutex_t *forks, pthread_mutex_t *com)
{
	int i;
	int nb_philos;

	i = 0;
	nb_philos = ft_atoi(argv[1]);
	while (i < nb_philos)
		pthread_mutex_init(&forks[i ++], NULL);
	i = 0;
	while (i < nb_philos)
	{
		philos[i].index_philo = i;
		philos[i].start_time = 0;
		philos[i].nb_philos = nb_philos;
		philos[i].time_die = ft_atoi(argv[2]);
        philos[i].time_eat = ft_atoi(argv[3]);
        philos[i].time_sleep = ft_atoi(argv[4]);
        philos[i].forks = forks;
        philos[i].com = com;
        if (philos[i].time_eat + philos[i].time_sleep >= philos[i].time_die)
            philos[i].should_die = 1;
        philos[i].should_die = 0;
        i ++;
	}
	return (create_philos(philos, nb_philos));
}

int	main(int argc, char const *argv[])
{
	t_philo 	    *philos;
    pthread_mutex_t *forks;
	pthread_mutex_t *com;

	if (argc >= 5)
	{
        philos = (t_philo *) malloc(sizeof (t_philo) * ft_atoi(argv[1]));
        forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
        com = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		if (argc == 5)
            return (philo_manager(philos, argv, forks,  com), EXIT_SUCCESS);
	}
}
