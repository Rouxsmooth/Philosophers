/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:10:08 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/21 17:45:25 by mzaian           ###   ########.fr       */
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
		if (vals->id_log[i] < prey && vals->meal_log[prey] > 0)
			prey = vals->id_log[i];
		i++;
	}
	grim->current_prey_starttime = vals->id_log[prey];
	grim->current_prey = prey;
	return ;
}

void	kill_all_preys(t_grim *grim, t_vals *vals)
{
	long int	time;

	pthread_mutex_lock(&vals->mutexes.message);
	vals->message_allowed = 0;
	time = get_utime();
	messages(grim->current_prey, time - grim->start_time, "die");
	pthread_mutex_unlock(&vals->mutexes.message);
	exit(1);
}
//printf("%ld - %ld : %ld > %d\n", get_utime(),
//vals->id_log[grim->current_prey],
//get_utime() - vals->id_log[grim->current_prey], vals->t2die);

void	*grim_reaper_routine(void *arg)
{
	t_grim		*grim;
	t_vals		*vals;

	grim = (t_grim *) arg;
	vals = get_vals();
	grim->start_time = vals->delayed_start;
	delayed_start(grim->start_time, 1);
	grim->current_prey = 0;
	grim->current_prey_starttime = vals->id_log[0];
	while (1)
	{
		if (get_utime() - vals->id_log[grim->current_prey] > vals->t2die
			&& vals->meal_log[grim->current_prey] > 0)
			kill_all_preys(grim, vals);
		if (grim->current_prey_starttime != vals->id_log[grim->current_prey])
			find_new_prey(grim, vals);
	}
	return (NULL);
}
