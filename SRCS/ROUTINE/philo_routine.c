/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:48:21 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/14 19:33:00 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	delayed_start(t_time *time, long int actual_start)
{
	while (get_utime(time) < actual_start)
		usleep(1);
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

void	check_dead_philo(t_vals *vals, t_philo *philo)
{
	if (!vals->philo_died)
		return ;
	if (philo->fork1 != -1)
		pthread_mutex_unlock(&vals->mutexes.forks[philo->fork1]);
	if (philo->fork2 != -1)
		pthread_mutex_unlock(&vals->mutexes.forks[philo->fork2]);
	exit(1);
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
	check_dead_philo(vals, &philo);
	gettimeofday(&philo.time.tv, NULL);
	philo.time.start_time = philo.time.tv.tv_usec;
	delayed_start(&philo.time, vals->delayed_start);
	while (philo.is_alive)
	{
		set2eating(vals, &philo, id);
		set2sleep(vals, &philo, id);
	}
	return (NULL);
}
