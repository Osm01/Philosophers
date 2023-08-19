/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:46:34 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/19 18:21:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time_in_ms() - philo->last_meal > philo->time_die)
		{
			time_to_die(philo);
			exit(EXIT_SUCCESS);
		}
	}
}

void	philo_routine(t_philo *philo)
{
	if(pthread_create(&philo->philo, NULL, check_death, (void *)philo))
		return ;
	if (philo->index_philo % 2)
		usleep(100);
	while (1)
	{
		if (philo->index_philo % 2)
		{
			sem_wait(philo->forks);
			time_take_fork(philo, 0);
			if (philo->nb_philos <= 1)
				break ;
			sem_wait(philo->forks);
			time_take_fork(philo, 1);
		} 
		else
		{
			sem_wait(philo->forks);
			time_take_fork(philo, 1);
			if (philo->nb_philos <= 1)
				break ;
			sem_wait(philo->forks);
			time_take_fork(philo, 0);
		}
        time_to_eat(philo);
        sem_post(philo->forks);
        sem_post(philo->forks);
        time_to_sleep(philo);
		time_to_think(philo);
	}
}

void	create_philos(t_philo *philos, int nb_philos)
{
	long long	start_timer;
	int	i;

	i = 0;
	start_timer = get_time_in_ms();
	while (i < nb_philos)
    {
        philos[i].pid = fork();
		if (philos[i].pid < 0)
			exit(EXIT_FAILURE);
		if (philos[i].pid == 0)
		{
			philos[i].start_timer = start_timer;
			philos[i].last_meal = start_timer;
			philo_routine(&philos[i]);
		}
		i ++;
	}
}

void	global_init(t_philo *philos, int nb_philos)
{
	sem_t			*forks;
	sem_t			*print_lock;
	pthread_mutex_t	*last_meal_lock;
	pthread_mutex_t	*tour_lock;
	int				i;

	i = 0;
	forks = (sem_t *) malloc(sizeof(sem_t));
	print_lock = (sem_t *) malloc(sizeof(sem_t));
	last_meal_lock = (pthread_mutex_t *) malloc(sizeof (pthread_mutex_t) * nb_philos);
	tour_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nb_philos);
	sem_unlink("forks");
	sem_unlink("Print");
	forks = sem_open("print,", O_CREAT , 0644, nb_philos);
	print_lock = sem_open("print,", O_CREAT , 0644, 1);
	while (i < nb_philos)
	{
		pthread_mutex_init(&last_meal_lock[i], NULL);
		pthread_mutex_init(&tour_lock[i], NULL);
		philos[i].last_meal_lock = last_meal_lock[i];
		philos[i].tour_lock = tour_lock[i];
		philos[i].forks = forks;
		philos[i].print_lock = print_lock;
		i ++;
	}
}

void	philo_manager(t_philo *philos, char const *argv[])
{
	int			i;
	int			nb_philos;

	nb_philos = ft_atoi(argv[1]);
	i = 0;
	while (i < nb_philos)
	{
		philos[i].index_philo = i;
		philos[i].nb_philos = nb_philos;
		philos[i].time_die = ft_atoi(argv[2]);
		philos[i].time_eat = ft_atoi(argv[3]);
		philos[i].time_sleep = ft_atoi(argv[4]);
		philos[i ++].nb_tours = 0;
	}
	global_init(philos, nb_philos);
	return (create_philos(philos, nb_philos));
}