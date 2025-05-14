/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:39:40 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/14 19:44:45 by mzaian           ###   ########.fr       */
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

typedef struct s_time
{
	struct timeval	tv;
	long int		start_time;
	long int		curr_time;
}	t_time;

typedef struct s_grim
{
	int			current_prey;
	int			message_allowed;
	int			prey_amount;
	long int	current_prey_starttime;
	t_time		time;
}	t_grim;

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
}	t_mutexes;

typedef struct s_philo
{
	int			fork1;
	int			fork2;
	int			is_alive;
	int			thinks;
	t_time		time;
}	t_philo;

typedef struct s_vals
{
	int			*id_log;
	int			t2die;
	int			t2eat;
	int			t2sleep;
	int			philo_died;
	int			philos_amount;
	int			message_allowed;
	long int	delayed_start;
	pthread_t	*threads;
	t_mutexes	mutexes;
}	t_vals;

int			display_error(char *output);
int			parse(t_vals *vals, int argc, char **argv);
int			messages(int philo, long int time, const char *rule);
void		*philo_routine(void *arg);
void		quit(char *error_msg, t_vals *vals);
void		clear_mutexes(t_vals *vals, t_mutexes *mutexes);
void		set_vals(int argc, char **argv);
t_vals		*get_vals(void);
long int	get_utime(t_time *time);
void		*grim_reaper_routine(void *arg);
void		delayed_start(t_time *time, long int actual_start);
void		set2sleep(t_vals *vals, t_philo *philo, int id);
void		set2eating(t_vals *vals, t_philo *philo, int id);
#endif