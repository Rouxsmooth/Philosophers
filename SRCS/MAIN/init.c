/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:47:48 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/21 17:46:11 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

t_grim	set_grim(void)
{
	t_grim	grim;

	grim.prey_amount = get_vals()->philos_amount;
	grim.current_prey = 1;
	grim.message_allowed = 0;
	grim.current_prey_starttime = -1;
	return (grim);
}

t_mutexes	set_mutexes(t_vals *vals)
{
	t_mutexes	mutexes;
	int			i;

	i = 0;
	mutexes = (t_mutexes){0};
	mutexes.forks = (pthread_mutex_t *)
		malloc(vals->philos_amount * sizeof(pthread_mutex_t));
	if (!mutexes.forks)
		return (quit("mutex init error", vals), (t_mutexes){0});
	while (i < vals->philos_amount)
		if (pthread_mutex_init(&(mutexes.forks[i++]), NULL))
			return (quit("mutex init error", vals), (t_mutexes){0});
	if (pthread_mutex_init(&mutexes.message, NULL))
		return (quit("mutex init error", vals), (t_mutexes){0});
	return (mutexes);
}

void	start_philos(t_vals *vals, t_grim grim)
{
	int	i;
	int	*id;

	i = 0;
	printf("%d\n", vals->philos_amount);
	while (i < vals->philos_amount)
	{
		id = (int *)malloc(sizeof(int));
		*id = i;
		if (pthread_create(&vals->threads[i], NULL, &philo_routine, id))
			return (quit("Thread creating error", vals));
		i++;
	}
	if (pthread_create(&vals->threads[i], NULL, &grim_reaper_routine, &grim))
		return (quit("Thread creating error", vals));
	i = 0;
	while (i <= vals->philos_amount)
	{
		if (pthread_join(vals->threads[i], NULL))
			return (quit("Thread joining error", vals));
		i++;
	}
	return ;
}

void	set_logs(t_vals *vals)
{
	int	i;

	vals->id_log = (long int *) malloc(vals->philos_amount * sizeof(long int));
	if (!vals->id_log)
		quit("Alloc error", vals);
	i = 0;
	while (i < vals->philos_amount)
		vals->id_log[i++] = vals->delayed_start;
	vals->meal_log = (int *) malloc(vals->philos_amount * sizeof(int));
	if (!vals->meal_log)
		quit("Alloc error", vals);
	i = 0;
	while (i < vals->philos_amount)
		vals->meal_log[i++] = vals->meal_amount;
	return ;
}

void	set_vals(int argc, char **argv)
{
	t_vals	*vals;

	vals = get_vals();
	vals->threads = NULL;
	vals->mutexes = (t_mutexes){0};
	vals->message_allowed = 1;
	vals->delayed_start = get_utime() + 500;
	if (parse(vals, argc, argv) == -1)
		quit("Args error!", NULL);
	vals->threads = (pthread_t *) malloc((vals->philos_amount + 1)
			* sizeof(pthread_t));
	if (!vals->threads)
		quit("Alloc error", vals);
	set_logs(vals);
	vals->mutexes = set_mutexes(vals);
	start_philos(vals, set_grim());
	return ;
}
