/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:48:21 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/21 17:40:29 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	delayed_start(long int actual_start, int id)
{
	while (get_utime() < actual_start)
		usleep(1);
	if (id % 2 == 0)
		usleep(1000);
}

t_philo	set_philos(void)
{
	t_philo	philo;

	philo = (t_philo){0};
	philo.thinks = 1;
	philo.is_alive = 1;
	philo.fork1 = -1;
	philo.fork2 = -1;
	return (philo);
}

void	*philo_routine(void *arg)
{
	int			id;
	t_vals		*vals;
	t_philo		philo;

	id = *(int *)arg;
	free(arg);
	philo = set_philos();
	vals = get_vals();
	philo.start_time = vals->delayed_start;
	delayed_start(vals->delayed_start, id);
	while (philo.is_alive)
	{
		if (!vals->meal_log[id])
			exit(1);
		set2eating(vals, &philo, id);
		set2sleep(vals, &philo, id);
	}
	return (NULL);
}
