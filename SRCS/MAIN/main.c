/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:33:55 by mzaian            #+#    #+#             */
/*   Updated: 2025/04/11 15:45:17 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	quit(char *error_msg, t_vals *vals)
{
	//del vals if needed
	int	i;

	i = 0;
	if (error_msg)
		display_error(error_msg);
	if (vals->philos_amount == -1)
		exit(0);
	while (i < vals->philos_amount - 1)
	{
		pthread_mutex_destroy(&(vals->forks[i]));
		free(&(vals->philos[i]));
		i++;
	}
	free(vals->forks);
	free(vals->forks_usage);
	free(vals->philos);
	exit(0);
}

void	set_philos(t_vals *vals, t_context *ctx)
{
	int	i;

	ctx->id = (int *) malloc(sizeof(int));
	vals->forks = (pthread_mutex_t *) malloc(vals->philos_amount * sizeof(pthread_mutex_t));
	vals->philos = (t_philo *) malloc(vals->philos_amount * sizeof(t_philo));
	vals->forks_usage = (int *) malloc(vals->philos_amount * sizeof(int));
	memset(vals->forks_usage, 1, vals->philos_amount);
	i = 0;
	vals->philo_died = 0;
	ctx->vals = vals;
	while (i < vals->philos_amount - 1)
	{
		vals->philos[i].is_alive = 1;
		vals->philos[i].has_eaten = 0;
		vals->philos[i].has_slept = 0;
		vals->philos[i].eatstart = 0;
		vals->philos[i].sleepstart = 0;
		vals->philos[i].thinks = 0;
		vals->philos[i].fork1 = -1;
		vals->philos[i].fork2 = -1;
		*(ctx->id) = i;
		if (pthread_create(&(vals->philos[i].thread), NULL, &philo_routine, ctx))
			return (quit("Thread creating error", vals));
		if (pthread_mutex_init(&(vals->forks[i]), NULL))
			return (quit("Mutex creating error", vals));
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{	
	t_vals		*vals;
	t_context	*ctx;
	int			i;

	if (argc != 5 && argc != 6)
		return (display_error(ft_ternary("Missing args!", "Too much args!",
				argc < 5)));
	vals = (t_vals *) malloc(sizeof(t_vals));
	ctx = (t_context *) malloc(sizeof(t_context));
	if (parse(vals, argc, argv) == -1)
		return (vals->philos_amount = -1, quit("Args error!", vals), 1);
	vals->time.start_time = vals->time.tv.tv_usec;
	gettimeofday(&vals->time.tv, NULL);
	set_philos(vals, ctx);
	i = 0;
	while (i < vals->philos_amount - 1)
		if (pthread_join(vals->philos[i].thread, NULL))
			quit("Thread joining error", vals);
	quit(NULL, vals);
	return (0);
}

long int	get_utime(t_time *time)
{
	gettimeofday(&time->tv, NULL);
	time->curr_time = time->tv.tv_usec;
	return (time->curr_time - time->start_time);
}

int	take_fork(t_vals *vals, int fork, int currtime, int currphilo)
{
	if (!vals->forks_usage[fork])
		return (0);
	pthread_mutex_lock(&vals->forks[fork]);
	messages(currphilo, currtime, "fork");
	vals->forks_usage[fork] = 0;
	return (1);
}

void	need2eat(t_vals *vals, t_philo *philo, int currphilo)
{
	long int	currtime;
	int			fork1;
	int			fork2;
	
	currtime = get_utime((&vals->time));
	fork1 = currphilo;
	fork2 = (currphilo + 1) % vals->philos_amount;
	if (fork1 > fork2)
	{
		fork1 ^= fork2;
		fork2 ^= fork1;
		fork1 ^= fork2;
	}
	if (take_fork(vals, currtime, fork1, currphilo))
		philo->fork1 = fork1;
	if (take_fork(vals, currtime, fork2, currphilo))
		philo->fork2 = fork2;
	if (philo->fork1 != -1 && philo->fork2 != -1)
	{
		messages(currphilo, currtime, "eat");		
		philo->eatstart = currtime;
		philo->thinks = 0;
	}
	return ;
}

void	set2sleep(t_vals *vals, t_philo *philo, int currphilo)
{
	long int	sleeptime;

	sleeptime = get_utime(&(vals->time));
	messages(currphilo, sleeptime, "sleep");
	philo->fork1 = -1;
	philo->fork2 = -1;
	philo->sleepstart = sleeptime;
	philo->thinks = 0;
	return ;
}

void	check_t2eat(t_vals *vals, t_philo *philo, int currphilo)
{
	int	currtime;

	currtime = get_utime(&(vals->time));
	if (currtime - philo->eatstart > vals->t2eat)
	{
		philo->fork1 = 0;
		philo->fork2 = 0;
		pthread_mutex_unlock(&(vals->forks[philo->fork1]));
		pthread_mutex_unlock(&(vals->forks[philo->fork2]));
		philo->eatstart = 0;
		return (set2sleep(vals, philo, currphilo));
	}
	return ;
}

void	check_t2sleep(t_vals *vals, t_philo *philo, int currphilo)
{
	int	currtime;

	currtime = get_utime(&(vals->time));
	if (currtime - philo->sleepstart > vals->t2sleep)
	{
		philo->sleepstart = 0;
		philo->thinks = currtime;
		messages(currphilo, currtime, "think");
	}
	return ;
}

void	check_dead_philo(t_vals *vals, t_philo *philo)
{
	if (!vals->philo_died)
		return ;
	if (philo->fork1 != -1)
		pthread_mutex_unlock(&(vals->forks[philo->fork1]));
	if (philo->fork2 != -1)
		pthread_mutex_unlock(&(vals->forks[philo->fork2]));
	return ;
}

void	*philo_routine(void *arg)
{
	t_context	ctx;
	t_philo		philo;
	int			id;

	ctx = *(t_context *)arg;
	id = *(ctx.id);
	free(ctx.id);
	printf("philo id%d, philo is %s \n", id, ctx.vals->philo_died ? "dead" : "alive");
	philo = ctx.vals->philos[id];
	while (philo.is_alive)
	{
		check_dead_philo(ctx.vals, &philo);
		if (philo.thinks)
			need2eat(ctx.vals, &philo, *(ctx.id));
		check_dead_philo(ctx.vals, &philo);
		if (!philo.is_alive)
			break ;
		if (philo.eatstart)
			check_t2eat(ctx.vals, &philo, *(ctx.id));
		check_dead_philo(ctx.vals, &philo);
		if (philo.sleepstart)
			check_t2sleep(ctx.vals, &philo, *(ctx.id));
		usleep(1);
	}
	messages(*(ctx.id), get_utime(&(ctx.vals->time)), "die");
	ctx.vals->philo_died = 1;
	return (NULL);
}
