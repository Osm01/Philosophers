/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:40:09 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/24 16:47:59 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->last_meal_lock);
		if (get_time_in_ms() - philo->last_meal > philo->time_die)
		{
			time_to_die(philo);
			exit(EXIT_SUCCESS);
		}
		pthread_mutex_unlock(&philo->last_meal_lock);
		pthread_mutex_lock(&philo->tour_lock);
		if (philo->nb_eat != -1 && philo->nb_tours == philo->nb_eat)
			exit(EXIT_FAILURE);
		pthread_mutex_unlock(&philo->tour_lock);
	}
}

void	philo_routine(t_philo *philo)
{
	if (philo->index_philo % 2)
		usleep(40);
	philo->last_meal = get_time_in_ms();
	if (pthread_create(&philo->philo, NULL, check_death, (void *)philo))
		return ;
	while (1)
	{
		if (time_take_fork(philo) == NULL)
			break ;
		time_to_eat(philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		time_to_sleep(philo);
		time_to_think(philo);
	}
	pthread_join(philo->philo, NULL);
}

void	create_philos(t_philo *philos, int nb_philos)
{
	int			i;
	long long	start_timer;

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
			philo_routine(&philos[i]);
		}
		i ++;
	}
	return ;
}

void	global_init(t_philo *philos, int n_p)
{
	sem_t			*forks;
	sem_t			*print_lock;
	pthread_mutex_t	*last_meal_lock;
	pthread_mutex_t	*tour_lock;
	int				i;

	i = 0;
	forks = sem_open("forks_sem", O_CREAT | O_EXCL, 0666, n_p);
	print_lock = sem_open("print_sem", O_CREAT | O_EXCL, 0666, 1);
	last_meal_lock = (pthread_mutex_t *) malloc(sizeof (pthread_mutex_t) * n_p);
	tour_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * n_p);
	if (forks == SEM_FAILED || print_lock == SEM_FAILED)
		exit(EXIT_FAILURE);
	while (i < n_p)
	{
		pthread_mutex_init(&last_meal_lock[i], NULL);
		pthread_mutex_init(&tour_lock[i], NULL);
		philos[i].last_meal_lock = last_meal_lock[i];
		philos[i].tour_lock = tour_lock[i];
		philos[i].forks = forks;
		philos[i ++].print_lock = print_lock;
	}
	free(last_meal_lock);
	free(tour_lock);
}

void	philo_manager(t_philo *philos, int argc, char const *argv[])
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
		philos[i].nb_eat = -1;
		if (argc == 6)
			philos[i].nb_eat = ft_atoi(argv[5]);
		philos[i].nb_tours = 0;
		i ++;
	}
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	global_init(philos, nb_philos);
	create_philos(philos, nb_philos);
}
