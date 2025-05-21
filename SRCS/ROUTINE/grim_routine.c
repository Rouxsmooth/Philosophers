/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:10:08 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/21 17:13:44 by mzaian           ###   ########.fr       */
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
	long int	time;
	
	printf("Killing all preys\n");
	//printf("%ld\n", vals->id_log[grim->current_prey]);
	//printf("%ld time %ld\n", vals->id_log[grim->current_prey] + vals->t2die, time);
	printf("%ld - %ld : %ld > %d\n", get_utime(), vals->id_log[grim->current_prey], get_utime() - vals->id_log[grim->current_prey], vals->t2die);
	pthread_mutex_lock(&vals->mutexes.message);
	vals->message_allowed = 0;
	time = get_utime();
	messages(grim->current_prey, time - grim->start_time, "die");
	pthread_mutex_unlock(&vals->mutexes.message);
	exit(1);
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
	grim->current_prey_starttime = vals->id_log[0];
	while (1)
	{
		//printf("time : %ld\n", currtime);
		if (get_utime() - vals->id_log[grim->current_prey] > vals->t2die)
			kill_all_preys(grim, vals);
		if (grim->current_prey_starttime != vals->id_log[grim->current_prey])
			find_new_prey(grim, vals);
	}
	return (NULL);
}
