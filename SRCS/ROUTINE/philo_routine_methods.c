/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_methods.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:42:58 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/21 17:34:05 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	set2dead(t_vals *vals, t_philo *philo)
{
	// printf("a philo died : %d %d\n", vals->message_allowed, vals->message_allowed);
	pthread_mutex_unlock(&vals->mutexes.message);
	if (philo->fork1 != -1)
		pthread_mutex_unlock(&vals->mutexes.forks[philo->fork1]);
	if (philo->fork2 != -1)
		pthread_mutex_unlock(&vals->mutexes.forks[philo->fork2]);
	philo->is_alive = 0;
	exit(1);
}

void	set2sleep(t_vals *vals, t_philo *philo, int id)
{
	pthread_mutex_lock(&vals->mutexes.message);
	if (!vals->message_allowed)
		return (set2dead(vals, philo));
	messages(id, get_utime() - philo->start_time, "sleep");
	pthread_mutex_unlock(&vals->mutexes.message);
	usleep(vals->t2sleep);
	pthread_mutex_lock(&vals->mutexes.message);
	messages(id, get_utime() - philo->start_time, "think");
	pthread_mutex_unlock(&vals->mutexes.message);
	return ;
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

void	set2eating(t_vals *vals, t_philo *philo, int id)
{
	int			fork1;
	int			fork2;
	long int	currtime;

	fork1 = get_first_fork(vals, id);
	fork2 = get_second_fork(vals, id);
	pthread_mutex_lock(&vals->mutexes.forks[fork1]);
	philo->fork1 = fork1;
	if (!vals->message_allowed)
		return (set2dead(vals, philo));
	//printf("philo %d tried taking messages\n", id + 1);
	pthread_mutex_lock(&vals->mutexes.message);
	//printf("philo %d succeded taking messages\n", id + 1);
	messages(id, get_utime() - philo->start_time, "fork");
	pthread_mutex_unlock(&vals->mutexes.message);
	//printf("philo %d succeded releasing messages\n", id + 1);
	pthread_mutex_lock(&vals->mutexes.forks[fork2]);
	philo->fork2 = fork2;
	if (!vals->message_allowed)
		return (set2dead(vals, philo));
	currtime = get_utime() - philo->start_time;
	//printf("philo %d tried taking messages\n", id + 1);
	pthread_mutex_lock(&vals->mutexes.message);
	//printf("philo %d succeded taking messages\n", id + 1);
	messages(id, currtime, "fork");
	messages(id, currtime, "eat");
	vals->id_log[id] = currtime + philo->start_time + vals->t2eat;
	vals->meal_log[id]--;
	pthread_mutex_unlock(&vals->mutexes.message);
	//printf("philo %d succeded releasing messages\n", id + 1);
	//printf("t2eat : %d\n", vals->t2eat);
	usleep(vals->t2eat);
	//printf("seg after\n");
	pthread_mutex_unlock(&vals->mutexes.forks[fork1]);
	pthread_mutex_unlock(&vals->mutexes.forks[fork2]);
}
