/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:10:08 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/16 11:31:41 by mzaian           ###   ########.fr       */
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

void	kill_all_preys(t_grim *grim, t_vals *vals, long int time)
{
	pthread_mutex_lock(&vals->mutexes.message);
	printf("%ld\n", vals->id_log[grim->current_prey]);
	printf("%ld time %ld\n", vals->id_log[grim->current_prey] + vals->t2die / 1000, time);
	printf("Killing all preys\n");
	vals->message_allowed = 0;
	messages(grim->current_prey, time, "die");
	pthread_mutex_unlock(&vals->mutexes.message);
	exit(1);
}

void	*grim_reaper_routine(void *arg)
{
	t_grim		*grim;
	t_vals		*vals;
	long int	currtime;

	grim = (t_grim *) arg;
	vals = get_vals();
	gettimeofday(&grim->time.tv, NULL);
	grim->time.start_time = grim->time.tv.tv_usec / 1000;
	delayed_start(&grim->time, vals->delayed_start, 1);
	find_new_prey(grim, vals);
	while (1)
	{
		currtime = get_utime(&grim->time)- vals->delayed_start;
		printf("time : %ld\n", currtime);
		if (vals->id_log[grim->current_prey] + vals->t2die / 1000 < currtime)
			return (kill_all_preys(grim, vals, currtime), NULL);
		if (grim->current_prey_starttime != vals->id_log[grim->current_prey])
			find_new_prey(grim, vals);
	}
	return (NULL);
}
