/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouidriss <ouidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:59:29 by ouidriss          #+#    #+#             */
/*   Updated: 2023/08/22 15:19:15 by ouidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	value;
	int	signe;
	int	i;

	value = 0;
	signe = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' || str[i] == '+' || str[i] == 32)
		{
			if (str[i] == '-')
				signe *= -1;
		}
		else
			break ;
		i ++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + str[i] - '0';
		i ++;
	}
	return (signe * value);
}
