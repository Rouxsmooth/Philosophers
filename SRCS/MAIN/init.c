/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:47:48 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/08 19:26:37 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	clear_mutexes(t_vals *vals, t_mutexes *mutexes)
{
	int	i;

	if (mutexes->forks)
	{
		i = 0;
		while (i < vals->philos_amount)
			pthread_mutex_destroy(&mutexes->forks[i++]);
		free(mutexes->forks);
		mutexes->forks = NULL;
	}
	if (mutexes->philos)
	{
		while (i < vals->philos_amount * 2)
			pthread_mutex_destroy(&mutexes->philos[i - vals->philos_amount]);
		free(mutexes->philos);
		mutexes->philos = NULL;
	}
	pthread_mutex_destroy(&mutexes->meal_amount);
	pthread_mutex_destroy(&mutexes->philo_died);
	pthread_mutex_destroy(&mutexes->philos_amount);
	pthread_mutex_destroy(&mutexes->t2die);
	pthread_mutex_destroy(&mutexes->t2eat);
	pthread_mutex_destroy(&mutexes->t2sleep);
	return ;
}

void	set_forks_philos(t_vals *vals, t_mutexes *mutexes)
{
	int	i;

	i = -1;
	mutexes->forks = (pthread_mutex_t *)
		malloc(vals->philos_amount * sizeof(pthread_mutex_t));
	if (!mutexes->forks)
		return (quit("mutex init error", vals), (void) 0);
	mutexes->philos = (pthread_mutex_t *)
		malloc(vals->philos_amount * sizeof(pthread_mutex_t));
	if (!mutexes->philos)
		return (quit("mutex init error", vals), (void) 0);
	while (++i < vals->philos_amount)
		if (pthread_mutex_init(&(mutexes->forks[i]), NULL))
			return (quit("mutex init error", vals), -1);
	i--;
	while (++i < 2 * vals->philos_amount)
		if (pthread_mutex_init(&(mutexes->forks[i - vals->philos_amount]), NULL))
			return (quit("mutex init error", vals), -1);
	return ;
}

void	set_mutexes(t_vals *vals, t_mutexes *mutexes)
{
	if (pthread_mutex_init(&mutexes->meal_amount, NULL))
		return (quit("mutex init error", vals), (t_mutexes){0});
	if (pthread_mutex_init(&mutexes->philo_died, NULL))
		return (quit("mutex init error", vals), (t_mutexes){0});
	if (pthread_mutex_init(&mutexes->philos_amount, NULL))
		return (quit("mutex init error", vals), (t_mutexes){0});
	if (pthread_mutex_init(&mutexes->t2die, NULL))
		return (quit("mutex init error", vals), (t_mutexes){0});
	if (pthread_mutex_init(&mutexes->t2eat, NULL))
		return (quit("mutex init error", vals), (t_mutexes){0});
	if (pthread_mutex_init(&mutexes->t2sleep, NULL))
		return (quit("mutex init error", vals), (t_mutexes){0});
	return ;
}

t_vals	set_vals(int argc, char **argv)
{
	t_vals	vals;

	vals = (t_vals) {0};
	if (parse(&vals, argc, argv) == -1)
		return (vals.philos_amount = -1, quit("Args error!", &vals), (t_vals) {0});
	vals.philos = (t_philo *) malloc(vals.philos_amount * sizeof(t_philo));
	if (!vals.philos)
		quit("Alloc error", &vals);
	vals.forks_usage = (int *) malloc(vals.philos_amount * sizeof(int));
	if (!vals.forks_usage)
		quit("Alloc error", &vals);
	memset(vals.forks_usage, 1, vals.philos_amount);
}

void	set_philos(t_vals *vals, t_context ctx)
{
	int	i;

	i = 0;
	while (i < vals->philos_amount - 1)
	{
		vals->philos[i] = (t_philo) {0};
		vals->philos[i].thinks = 1;
		vals->philos[i].is_alive = 1;
		vals->philos[i].fork1 = -1;
		vals->philos[i].fork2 = -1;
		ctx.vals = vals;
		ctx.id = i;
		if (pthread_create(&(vals->philos[i].thread), NULL, &philo_routine, &ctx))
			return (quit("Thread creating error", vals));
		i++;
	}
	i = 0;
	whiel (i < vals->philos_amount - 1)
	{
		
	}
	return ;
}
