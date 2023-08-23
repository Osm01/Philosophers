/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:24:53 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/22 15:19:41 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	main(int argc, char const *argv[])
{
	t_philo			*philos;

	if (argc == 5 || argc == 6)
	{
		philos = (t_philo *) malloc(sizeof (t_philo) * ft_atoi(argv[1]));
		return (philo_manager(philos, argv, argc), EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
