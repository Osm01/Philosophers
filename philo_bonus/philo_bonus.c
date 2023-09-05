/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:38:03 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/30 22:14:20 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(struct timeval last_meal)
{
	return ((long long)last_meal.tv_sec * 1000 + \
	(long long)last_meal.tv_usec / 1000);
}

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

int	checker(int argc, char const *argv[])
{
	int	i;
	int	y;

	i = 1;
	while (i <= (argc - 1))
	{
		y = 0;
		while (argv[i][y])
		{
			if (argv[i][y] < '0' || argv[i][y] > '9')
			{
				if (argv[i][y] != '+' && argv[i][y] != '-')
					return (printf("\033[0;31mUNACCEPTABLE PARAMETTRE :P\n"), 0);
			}
			y ++;
		}
		if (i != 1 && i != 5 && ft_atoi(argv[i]) <= 60)
			return (0);
		i ++;
	}
	return (1);
}

int	main(int argc, char const *argv[])
{
	t_philo			*philos;
	int				status;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	if (!checker(argc, argv))
		return (EXIT_FAILURE);
	if ((ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200) || \
	(argc == 6 && (ft_atoi(argv[5]) <= 0)))
		return (EXIT_FAILURE);
	philos = (t_philo *) malloc(sizeof (t_philo) * ft_atoi(argv[1]));
	philo_manager(philos, argc, argv);
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == EXIT_SUCCESS)
			break ;
	}
	free (philos);
	return (EXIT_SUCCESS);
}
