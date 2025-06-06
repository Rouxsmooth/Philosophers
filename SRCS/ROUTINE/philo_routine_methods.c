/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_methods.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:42:58 by mzaian            #+#    #+#             */
/*   Updated: 2025/06/06 16:04:16 by mzaian           ###   ########.fr       */
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
	usleep(philo->t2sleep * 1000);
	pthread_mutex_lock(&vals->mutexes.message);
	philo->uses_message = 1;
	if (!vals->message_allowed)
		return (set2dead(vals, philo), -1);
	messages(id, get_utime() - philo->start_time, "think");
	philo->uses_message = 0;
	pthread_mutex_unlock(&vals->mutexes.message);
	return (1);
}

int	eating_with_2forks(t_vals *vals, t_philo *philo, int id)
{
	long int	currtime;
	int			fork2;

	fork2 = get_fork(philo, id, 1);
	pthread_mutex_lock(&vals->mutexes.forks[fork2]);
	philo->fork2 = fork2;
	pthread_mutex_lock(&vals->mutexes.message);
	philo->uses_message = 1;
	if (!vals->message_allowed)
		return (set2dead(vals, philo), -1);
	currtime = get_utime() - philo->start_time;
	messages(id, currtime, "fork");
	messages(id, currtime, "eat");
	pthread_mutex_lock(&vals->mutexes.id_log);
	vals->id_log[id] = currtime + philo->start_time + philo->t2eat / 1000;
	pthread_mutex_unlock(&vals->mutexes.id_log);
	pthread_mutex_lock(&vals->mutexes.meal_log);
	if (vals->meal_amount != -1)
		vals->meal_log[id]--;
	pthread_mutex_unlock(&vals->mutexes.meal_log);
	philo->uses_message = 0;
	pthread_mutex_unlock(&vals->mutexes.message);
	usleep(philo->t2eat * 1000);
	return (unlock_forks(vals, philo), 1);
}

int	set2eating(t_vals *vals, t_philo *philo, int id)
{
	int			fork1;

	fork1 = get_fork(philo, id, 0);
	pthread_mutex_lock(&vals->mutexes.forks[fork1]);
	philo->fork1 = fork1;
	pthread_mutex_lock(&vals->mutexes.message);
	philo->uses_message = 1;
	if (!vals->message_allowed)
		return (set2dead(vals, philo), -1);
	messages(id, get_utime() - philo->start_time, "fork");
	philo->uses_message = 0;
	pthread_mutex_unlock(&vals->mutexes.message);
	return (eating_with_2forks(vals, philo, id));
}
