/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:33:55 by mzaian            #+#    #+#             */
/*   Updated: 2025/04/01 18:22:31 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	quit(char *error_msg, t_vals *vals)
{
	//del vals if needed
	(void) vals;
	if (error_msg)
		display_error(error_msg);
	exit(0);
}

int	main(int argc, char **argv)
{	
	t_vals	vals;

	if (argc != 5 && argc != 6)
		return (display_error(ft_ternary("Missing args!", "Too much args!",
				argc < 5)));
	if (parse(&vals, argc, argv) == -1)
		quit("Args error!", &vals);
	vals.forks = (int *) malloc((vals.philos_amount + 1) * sizeof(int));
	// printf("%d %d %d %d\n", vals.philos_amount, vals.t2die, vals.t2eat, vals.t2sleep);
	gettimeofday(&vals.time.tv, NULL);
	vals.time.start_time = vals.time.tv.tv_usec;
	free(vals.forks);
	return (0);
}

long int	get_utime(t_time *time)
{
	gettimeofday(&time->tv, NULL);
	time->curr_time = time->tv.tv_usec;
	return (time->curr_time - time->start_time);
}
