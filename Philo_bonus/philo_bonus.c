/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:39:48 by codespace         #+#    #+#             */
/*   Updated: 2023/08/19 18:15:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

void	my_usleep(long long target_time)
{
	long long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < target_time)
		usleep(10);
}

void	*check_death_by_eat(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *) arg;
	int	nb_philos;
	int	count;
	int	nb_tours;
	int	i;

	if (philos[0].nb_tours < 0)
		return ((void *)NULL);
	nb_philos = philos[0].nb_philos;
	nb_tours = philos[0].nb_tours;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < nb_philos)
		{
			pthread_mutex_lock(&philos[i].tour_lock);
			if (philos[i].nb_tours == nb_tours)
				count ++;
			pthread_mutex_unlock(&philos[i].tour_lock);
			i ++;
		}
		if (count == nb_tours)
			return ((void *)NULL);
	}
	return ((void *)NULL);

}

int	main(int argc, char const *argv[])
{
	t_philo			*philos;
	pthread_t		checker;
	int				status;

	if (argc == 5 || argc == 6)
	{
		philos = (t_philo *) malloc(sizeof (t_philo) * ft_atoi(argv[1]));
		philo_manager(philos, argc, argv);
	}
	else
		return (EXIT_FAILURE);
	if (pthread_create(&checker, NULL, check_death_by_eat, (void *)philos))
	{
		printf("HERE\n");
		return (EXIT_FAILURE);
	}
	while (waitpid(-1, &status , 2) > 0)
	{
		if (WEXITSTATUS(status) == EXIT_SUCCESS)
			break ;
	}
	return (EXIT_SUCCESS);
}
