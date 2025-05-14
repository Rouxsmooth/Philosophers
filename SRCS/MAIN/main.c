/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:33:55 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/14 19:46:32 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

t_vals	*get_vals(void)
{
	static t_vals	vals = (t_vals){0};

	return (&vals);
}

void	quit(char *error_msg, t_vals *vals)
{
	if (vals)
	{
		clear_mutexes(vals, &vals->mutexes);
		if (vals->threads)
			free(vals->threads);
	}
	if (error_msg)
		display_error(error_msg);
	exit(0);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		return (display_error("Missing args!"));
	if (argc > 6)
		return (display_error("Too much args!"));
	set_vals(argc, argv);
	quit(NULL, NULL);
	return (0);
}

long int	get_utime(t_time *time)
{
	gettimeofday(&time->tv, NULL);
	time->curr_time = time->tv.tv_usec;
	return (time->curr_time - time->start_time);
}
