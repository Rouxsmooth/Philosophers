/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:39:40 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/11 20:24:24 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*philos;
	pthread_mutex_t	meal_amount;
	pthread_mutex_t	philo_died;
	pthread_mutex_t	philos_amount;
	pthread_mutex_t	t2die;
	pthread_mutex_t	t2eat;
	pthread_mutex_t	t2sleep;
}	t_mutexes;

typedef struct s_philo
{
	int				fork1;
	int				fork2;
	int				has_eaten;
	int				has_slept;
	int				is_alive;
	int				thinks;
	pthread_t		thread;
}	t_philo;

typedef struct s_time
{
	struct timeval	tv;
	long int		start_time;
	long int		curr_time;
}	t_time;

typedef struct s_vals
{
	int				t2die;
	int				t2eat;
	int				t2sleep;
	int				philo_died;
	int				philos_amount;
	int				*forks_usage;
	t_philo			*philos;
	t_time			time;
}	t_vals;

typedef struct s_context
{
	int			id;
	t_mutexes	mutexes;
	t_vals		*vals;
}	t_context;

/* ternaries */
void	*ft_ternary(void *output1, void *output2, int condition);
int		ft_intternary(int i1, int i2, int condition);
int		display_error(char *output);
int		parse(t_vals *vals, int argc, char **argv);
int		messages(int philo, long int time, const char *rule);
void	*philo_routine(void *arg);
void	print_philo_vals(t_philo *philo);
void	quit(char *error_msg, t_vals *vals);
void	clear_mutexes(t_vals *vals, t_mutexes *mutexes);
void	set_vals(int argc, char **argv);

#endif