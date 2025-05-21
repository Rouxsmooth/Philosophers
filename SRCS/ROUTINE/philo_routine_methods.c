/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_methods.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:42:58 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/22 01:50:29 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	unlock_forks(t_vals *vals, t_philo *philo)
{
	if (philo->fork1 != -1)
		pthread_mutex_unlock(&vals->mutexes.forks[philo->fork1]);
	if (philo->fork2 != -1)
		pthread_mutex_unlock(&vals->mutexes.forks[philo->fork2]);
	philo->fork1 = -1;
	philo->fork2 = -1;
}

void	set2dead(t_vals *vals, t_philo *philo)
{
	if (philo->uses_message)
		pthread_mutex_unlock(&vals->mutexes.message);
	unlock_forks(vals, philo);
	return ;
}

int	set2sleep(t_vals *vals, t_philo *philo, int id)
{
	pthread_mutex_lock(&vals->mutexes.message);
	philo->uses_message = 1;
	if (!vals->message_allowed)
		return (set2dead(vals, philo), -1);
	messages(id, get_utime() - philo->start_time, "sleep");
	philo->uses_message = 0;
	pthread_mutex_unlock(&vals->mutexes.message);
	usleep(vals->t2sleep * 1000);
	pthread_mutex_lock(&vals->mutexes.message);
	philo->uses_message = 1;
	if (!vals->message_allowed)
		return (set2dead(vals, philo), -1);
	messages(id, get_utime() - philo->start_time, "think");
	philo->uses_message = 0;
	pthread_mutex_unlock(&vals->mutexes.message);
	return (1);
}

int	get_first_fork(t_vals *vals, int id)
{
	if (id % 2 == 1)
		return (id);
	return ((id + 1) % vals->philos_amount);
}

int	get_second_fork(t_vals *vals, int id)
{
	if (id % 2 == 0)
		return (id);
	return ((id + 1) % vals->philos_amount);
}

int	set2eating(t_vals *vals, t_philo *philo, int id)
{
	int			fork1;
	int			fork2;
	long int	currtime;

	fork1 = get_first_fork(vals, id);
	fork2 = get_second_fork(vals, id);
	pthread_mutex_lock(&vals->mutexes.forks[fork1]);
	philo->fork1 = fork1;
	pthread_mutex_lock(&vals->mutexes.message);
	philo->uses_message = 1;
	if (!vals->message_allowed)
		return (set2dead(vals, philo), -1);
	messages(id, get_utime() - philo->start_time, "fork");
	philo->uses_message = 0;
	pthread_mutex_unlock(&vals->mutexes.message);
	pthread_mutex_lock(&vals->mutexes.forks[fork2]);
	philo->fork2 = fork2;
	currtime = get_utime() - philo->start_time;
	pthread_mutex_lock(&vals->mutexes.message);
	philo->uses_message = 1;
	if (!vals->message_allowed)
		return (set2dead(vals, philo), -1);
	messages(id, currtime, "fork");
	messages(id, currtime, "eat");
	vals->id_log[id] = currtime + philo->start_time + vals->t2eat / 1000;
	if (vals->meal_amount != -1)
		vals->meal_log[id]--;
	philo->uses_message = 0;
	pthread_mutex_unlock(&vals->mutexes.message);
	usleep(vals->t2eat * 1000);
	unlock_forks(vals, philo);
	return (1);
}
