/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:38:35 by mzaian            #+#    #+#             */
/*   Updated: 2025/04/01 17:38:44 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		nbr *= 10;
		nbr += (nptr[i] - 48);
		i++;
	}
	return ((nbr > -1) * nbr + (nbr < 0) * -1);
}

int	parse(t_vals *vals, int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (-1);
			j++;
		}
		i++;
	}
	vals->philos_amount = ft_atoi(argv[1]);
	vals->t2die = ft_atoi(argv[2]);
	vals->t2eat = ft_atoi(argv[3]);
	vals->t2sleep = ft_atoi(argv[4]);
	if (vals->philos_amount == -1 || vals->t2die == -1 || vals->t2eat == -1
		|| vals->t2sleep == -1)
			return (-1);
	return (1);
}
