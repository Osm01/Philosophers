/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:39:48 by codespace         #+#    #+#             */
/*   Updated: 2023/08/21 15:49:03 by codespace        ###   ########.fr       */
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

int	main(int argc, char const *argv[])
{
	t_philo			*philos;
	int				status;

	if (argc == 5 || argc == 6)
	{
		philos = (t_philo *) malloc(sizeof (t_philo) * ft_atoi(argv[1]));
		philo_manager(philos, argc, argv);
	}
	else
		return (EXIT_FAILURE);
	while (waitpid(-1, &status , 2) > 0)
	{
		if (WEXITSTATUS(status) == EXIT_SUCCESS)
			break ;
	}
	return (EXIT_SUCCESS);
}
