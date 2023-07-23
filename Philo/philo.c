/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:24:53 by ouidriss          #+#    #+#             */
/*   Updated: 2023/07/22 20:11:28 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (!philo->prio)
		usleep((*philo).time_eat * 1000000);
	printf("\nPHILO IS RUNNING\n");
	return (NULL);
}

void	create_philos(t_philosopher *p_philo, char const *argv[])
{
	int	i;
	int nb_philos;

	i = 0;
	nb_philos = ft_atoi(argv[1]);
	while (i < nb_philos)
	{
		if (i % 2 == 0)
			p_philo->philos[i].prio = 0;
		else
			p_philo->philos[i].prio = 1;
		p_philo->philos[i].time_die = ft_atoi(argv[2]);
		p_philo->philos[i].time_eat = ft_atoi(argv[3]);
		p_philo->philos[i].time_sleep = ft_atoi(argv[4]);
		i ++;
	}
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_create(&p_philo->philos[i].philo, NULL, philo_routine, (void *) &p_philo->philos[i].philo) != 0)
			printf("FAILD to create thread");
		i ++;
	}
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_join(p_philo->philos[i].philo, NULL) != 0)
			printf("FAILDED to wait");
		i ++;
	}
}

void	philo_manager(t_philosopher *parent_philo, char const *argv[], int argc)
{
	create_philos(parent_philo, argv);
}

int	main(int argc, char const *argv[])
{
	t_philosopher	*parent_phi;

	if (argc >= 5)
	{
		parent_phi = (t_philosopher *) malloc(sizeof(t_philosopher));
		parent_phi->philos = (t_philo *) malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
		if (argc == 5)
		{
			philo_manager(parent_phi, argv, argc);
		}
	}
}
