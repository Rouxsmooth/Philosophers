/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:33:55 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/08 18:57:25 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	quit(char *error_msg, t_vals *vals)
{
	int	i;

	i = 0;
	if (vals)
	{
		clear_mutexes(vals, &vals->mutexes);
		if (vals->forks_usage)
			free(vals->forks_usage);
		if (vals->philos)
			free(vals->philos);
	}
	if (error_msg)
		display_error(error_msg);
	exit(0);
}

int	main(int argc, char **argv)
{	
	t_vals		vals;
	t_context	ctx;

	if (argc != 5 && argc != 6)
		return (display_error(ft_ternary("Missing args!", "Too much args!",
				argc < 5)));
	set_philos(&vals, &ctx);
	quit(NULL, &vals);
	return (0);
}

long int	get_utime(t_time *time)
{
	gettimeofday(&time->tv, NULL);
	time->curr_time = time->tv.tv_usec;
	return (time->curr_time - time->start_time);
}
