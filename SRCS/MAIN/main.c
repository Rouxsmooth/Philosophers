/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:33:55 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/21 17:44:33 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

t_vals	*get_vals(void)
{
	static t_vals	vals = (t_vals){0};

	return (&vals);
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

long int	get_utime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
