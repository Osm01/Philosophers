/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:40:09 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/31 16:38:40 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time_in_ms() - get_time(philo->last_meal) > philo->time_die)
		{
			sem_wait(philo->print_lock);
			printf("%lldms %d died\n", \
			get_time_in_ms() - philo->start_timer, philo->index_philo);
			sem_post(philo->forks);
			sem_post(philo->forks);
			exit(EXIT_SUCCESS);
		}
	}
}

void	philo_routine(t_philo *philo)
{
	if (pthread_create(&philo->philo, NULL, check_death, (void *)philo))
		return ;
	while (1)
	{
		time_take_fork(philo);
		time_to_eat(philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		if (philo->nb_eat != -1)
		{
			sem_wait(philo->tour_lock);
			philo->nb_tours ++;
			if (philo->nb_eat == philo->nb_tours)
			{
				sem_post(philo->tour_lock);
				exit(EXIT_FAILURE);
			}
			sem_post(philo->tour_lock);
		}
		time_to_sleep(philo);
		time_to_think(philo);
	}
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
		usleep(80);
		i ++;
	}
	return ;
}

void	global_init(t_philo *philos, int n_p)
{
	int		i;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*tour;

	forks = sem_open("forks_sem", O_CREAT | O_EXCL, 0644, n_p);
	print = sem_open("print_sem", O_CREAT | O_EXCL, 0644, 1);
	tour = sem_open("tour_lock", O_CREAT | O_EXCL, 0644, 1);
	i = 0;
	while (i < n_p)
	{
		philos[i].forks = forks;
		philos[i].print_lock = print;
		philos[i].tour_lock = tour;
		i++;
	}
	if (philos->nb_philos % 2 && philos[0].time_eat * 3 < philos[0].time_die \
	&& philos[0].nb_philos > 1)
		sem_post(philos[0].forks);
}

void	philo_manager(t_philo *philos, int argc, char const *argv[])
{
	int			i;
	int			nb_philos;

	nb_philos = ft_atoi(argv[1]);
	i = 0;
	while (i < nb_philos)
	{
		philos[i].index_philo = i + 1;
		philos[i].nb_philos = nb_philos;
		philos[i].time_die = ft_atoi(argv[2]);
		philos[i].time_eat = ft_atoi(argv[3]);
		philos[i].time_sleep = ft_atoi(argv[4]);
		gettimeofday(&philos[i].last_meal, NULL);
		philos[i].nb_eat = -1;
		if (argc == 6)
			philos[i].nb_eat = ft_atoi(argv[5]);
		philos[i].nb_tours = 0;
		i ++;
	}
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	sem_unlink("tour_lock");
	global_init(philos, nb_philos);
	return (create_philos(philos, nb_philos));
}
