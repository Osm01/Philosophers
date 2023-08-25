/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:24:53 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/25 12:51:28 by ouidriss         ###   ########.fr       */
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

void	*checker(int argc, char const *argv[])
{
	int	i;
	int	y;
	if (argc < 5 || argc > 6)
		return ((void *) NULL);
	i = 1;
	while (i <= (argc - 1))
	{
		y = 0;
		while (argv[i][y])
		{
			if (argv[i][y] < '0' || argv[i][y] > '9')
			{
				if (argv[i][y] == '-')
					return (printf("\033[0;31mNegative values are not allowed\n"), (void *) NULL);
				if (argv[i][y] != '+')
					return (printf("\033[0;31mUNACCEPTABLE PARAMETTRE :P\n"),(void *) NULL);
			}
			y ++;
		}
		if (i != 3 && i != 4 && ft_atoi(argv[i]) == 0)
			return ((void *) NULL);
		i ++;
	}
	return ((void *) 1);
}

int	main(int argc, char const *argv[])
{
	t_philo			*philos;

	if (checker(argc, argv) == NULL)
		return (EXIT_FAILURE);
	philos = (t_philo *) malloc(sizeof (t_philo) * ft_atoi(argv[1]));
	return (philo_manager(philos, argv, argc), EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
