/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:45:04 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/21 17:45:05 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	clear_mutexes(t_vals *vals, t_mutexes *mutexes)
{
	int	i;

	if (mutexes->forks)
	{
		i = 0;
		while (i < vals->philos_amount)
			pthread_mutex_destroy(&mutexes->forks[i++]);
		free(mutexes->forks);
		mutexes->forks = NULL;
	}
	pthread_mutex_destroy(&mutexes->message);
	return ;
}

void	quit(char *error_msg, t_vals *vals)
{
	if (vals)
	{
		clear_mutexes(vals, &vals->mutexes);
		if (vals->threads)
			free(vals->threads);
		if (vals->id_log)
			free(vals->id_log);
		if (vals->meal_log)
			free(vals->meal_log);
	}
	if (error_msg)
		display_error(error_msg);
	exit(0);
}
