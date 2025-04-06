/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:33:55 by mzaian            #+#    #+#             */
/*   Updated: 2025/04/06 12:51:42 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/philo.h"

void	quit(char *error_msg, t_vals *vals)
{
	//del vals if needed
	(void) vals;
	if (error_msg)
		display_error(error_msg);
	exit(0);
}

void	set_philos(t_vals *vals)
{
	int	i;

	vals->philos = (t_philo *) malloc(vals->philos_amount * sizeof(t_philo));
	i = 0;
	while (i < vals->philos_amount - 1)
	{
		if (pthread_create(&(vals->philos[i].thread), NULL, /*routine*/, vals))
			return (quit("Thread creating error", vals));
		i++;
	}
}

int	main(int argc, char **argv)
{	
	t_vals	vals;

	if (argc != 5 && argc != 6)
		return (display_error(ft_ternary("Missing args!", "Too much args!",
				argc < 5)));
	if (parse(&vals, argc, argv) == -1)
		quit("Args error!", &vals);
	vals.forks = (int *) malloc(vals.philos_amount * sizeof(int));
	set_philos(&vals);
	// printf("%d %d %d %d\n", vals.philos_amount, vals.t2die, vals.t2eat, vals.t2sleep);
	gettimeofday(&vals.time.tv, NULL);
	vals.time.start_time = vals.time.tv.tv_usec;
	free(vals.forks);
	return (0);
}

long int	get_utime(t_time *time)
{
	gettimeofday(&time->tv, NULL);
	time->curr_time = time->tv.tv_usec;
	return (time->curr_time - time->start_time);
}

void	need2eat(t_vals *vals, t_philo *philo, int currphilo)
{
	long int	currtime;
	int			fork1;
	int			fork2;
	
	fork1 = currphilo;
	fork2 = currphilo - 1;
	if (currphilo == vals->philos_amount - 1 || currphilo == 0)
	{
		fork1 = 0;
		fork2 = vals->philos_amount - 2;
	}
	if (vals->forks[fork1] && vals->forks[fork2])
	{
		messages(currphilo, get_utime(&(vals->time)), "fork");
		messages(currphilo, get_utime(&(vals->time)), "fork");
		currtime = get_utime((&vals->time));
		messages(currphilo, currtime, "eat");
		return (philo->thinks = 0, philo->eatstart = currtime,
				vals->forks[fork2] = 0, vals->forks[fork1] = 0, (void) 0);
	}
	currtime = get_utime((&vals->time));
	if (currtime - philo->thinks > vals->t2die)
		philo->is_alive = 0, (void) 0;
	return ;
}

void	set2sleep(t_vals *vals, t_philo *philo, int currphilo)
{
	long int	sleeptime;

	sleeptime = get_utime(&(vals->time));
	messages(currphilo, sleeptime, "sleep");
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

void	actions(t_vals *vals, int currphilo)
{
	t_philo	philo;

	philo = vals->philos[currphilo];
	if (philo.thinks)
		return (need2eat(vals, &philo, currphilo));
	if (philo.eatstart)
		return (check_t2eat(vals, &philo, currphilo));
	if (philo.sleepstart)
		return (check_t2sleep(vals, &philo, currphilo));
	return ;
}

int	missing_philo(t_vals *vals)
{
	int	i;

	i = 0;
	while (i < vals->philos_amount - 1)
	{
		if (vals->philos[i].is_alive)
			return (1);
		i++;
	}
	return (0);
}

void	mainloop(t_vals *vals)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < vals->philos_amount)
		{
			actions(vals, i);
			if (!vals->philos[i].is_alive)
				break ;
			i++;
		}
	}
	return ;
}
