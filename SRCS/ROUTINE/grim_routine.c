/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:10:08 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/14 19:47:20 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	find_new_prey(t_grim *grim, t_vals *vals)
{
	int	i;
	int	prey;

	i = 0;
	prey = 0;
	while (i < grim->prey_amount)
	{
		if (vals->id_log[i] < prey)
			prey = vals->id_log[i];
		i++;
	}
	grim->current_prey_starttime = vals->id_log[prey];
	grim->current_prey = prey;
	return ;
}

void	kill_all_preys(t_grim *grim, t_vals *vals)
{
	pthread_mutex_lock(&vals->mutexes.message);
	vals->message_allowed = 0;
	messages(grim->current_prey, get_utime(&grim->time), "die");
	pthread_mutex_unlock(&vals->mutexes.message);
	exit(1);
}

void	*grim_reaper_routine(void *arg)
{
	t_grim	*grim;
	t_vals	*vals;

	grim = (t_grim *) arg;
	vals = get_vals();
	gettimeofday(&grim->time.tv, NULL);
	grim->time.start_time = grim->time.tv.tv_usec;
	delayed_start(&grim->time, vals->delayed_start);
	find_new_prey(grim, vals);
	while (1)
	{
		if (vals->id_log[grim->current_prey] + vals->t2eat
			> get_utime(&grim->time))
			return (kill_all_preys(grim, vals), NULL);
		if (grim->current_prey_starttime != vals->id_log[grim->current_prey])
			find_new_prey(grim, vals);
	}
	return (NULL);
}
