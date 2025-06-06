/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:10:08 by mzaian            #+#    #+#             */
/*   Updated: 2025/06/06 16:01:36 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

int	find_new_prey(t_grim *grim, t_vals *vals)
{
	int			i;
	long int	prey;

	i = 0;
	prey = LONG_MAX;
	while (i < grim->prey_amount)
	{
		pthread_mutex_lock(&vals->mutexes.meal_log);
		if (vals->id_log[i] < prey && vals->meal_log[i] > 0)
			prey = i;
		pthread_mutex_unlock(&vals->mutexes.meal_log);
		i++;
	}
	if (prey == LONG_MAX)
		return (-1);
	grim->current_prey_starttime = vals->id_log[prey];
	grim->current_prey = prey;
	return (1);
}

void	kill_all_preys(t_grim *grim, t_vals *vals)
{
	long int	time;

	pthread_mutex_unlock(&vals->mutexes.meal_log);
	pthread_mutex_lock(&vals->mutexes.message);
	vals->message_allowed = 0;
	time = get_utime();
	messages(grim->current_prey, time - grim->start_time, "die");
	pthread_mutex_unlock(&vals->mutexes.message);
	return ;
}

void	grim_loop(t_grim *grim, t_vals *vals)
{
	while (1)
	{
		pthread_mutex_lock(&vals->mutexes.id_log);
		grim->uses_id_log = 1;
		if (get_utime() - vals->id_log[grim->current_prey] > vals->t2die)
		{
			pthread_mutex_unlock(&vals->mutexes.id_log);
			grim->uses_id_log = 0;
			pthread_mutex_lock(&vals->mutexes.meal_log);
			if (vals->meal_log[grim->current_prey] > 0)
				return (kill_all_preys(grim, vals));
		}
		if (!grim->uses_id_log)
		{
			pthread_mutex_lock(&vals->mutexes.id_log);
			grim->uses_id_log = 1;
		}
		if (grim->current_prey_starttime != vals->id_log[grim->current_prey])
			if (find_new_prey(grim, vals) == -1)
				return (pthread_mutex_unlock(&vals->mutexes.id_log), (void) 0);
		if (grim->uses_id_log)
			pthread_mutex_unlock(&vals->mutexes.id_log);
		usleep(1);
	}
	return ;
}

void	*grim_reaper_routine(void *arg)
{
	t_grim		*grim;
	t_vals		*vals;

	grim = (t_grim *) arg;
	vals = get_vals();
	grim->start_time = vals->delayed_start;
	delayed_start(grim->start_time, 1);
	grim->current_prey = 0;
	pthread_mutex_lock(&vals->mutexes.id_log);
	grim->current_prey_starttime = vals->id_log[0];
	pthread_mutex_unlock(&vals->mutexes.id_log);
	grim_loop(grim, vals);
	return (NULL);
}
