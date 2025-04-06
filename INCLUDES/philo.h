/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:39:40 by mzaian            #+#    #+#             */
/*   Updated: 2025/04/06 12:29:09 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int	is_alive;
	int	has_slept;
	int	has_eaten;
	int	thinks;
	long int	eatstart;
	long int	sleepstart;
	pthread_t	thread;
}	t_philo;

typedef struct s_time
{
	struct timeval	tv;
	long int		start_time;
	long int		curr_time;
}	t_time;

typedef struct s_vals
{
	int		t2eat;
	int		t2die;
	int		t2sleep;
	int		philos_amount;
	// int		eat_amount;
	int		*forks;
	t_time	time;
	t_philo	*philos;
}	t_vals;

/* ternaries */
void	*ft_ternary(void *output1, void *output2, int condition);
int		ft_intternary(int i1, int i2, int condition);
int		display_error(char *output);
int		parse(t_vals *vals, int argc, char **argv);
int		messages(int philo, long int time, const char *rule);

#endif