/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:39:40 by mzaian            #+#    #+#             */
/*   Updated: 2025/06/06 16:03:29 by mzaian           ###   ########.fr       */
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

typedef struct s_grim
{
	int			current_prey;
	int			message_allowed;
	int			prey_amount;
	int			uses_id_log;
	long int	current_prey_starttime;
	long int	start_time;
}	t_grim;

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	id_log;
	pthread_mutex_t	meal_log;
	pthread_mutex_t	message;
}	t_mutexes;

typedef struct s_philo
{
	int			fork1;
	int			fork2;
	int			philos_amount;
	int			t2die;
	int			t2eat;
	int			t2sleep;
	int			thinks;
	int			uses_message;
	long int	start_time;
}	t_philo;

typedef struct s_vals
{
	int			*meal_log;
	int			meal_amount;
	int			message_allowed;
	int			t2die;
	int			t2eat;
	int			t2sleep;
	int			philos_amount;
	long int	*id_log;
	long int	delayed_start;
	pthread_t	*threads;
	t_mutexes	mutexes;
}	t_vals;

# define LONG_MAX 9223372036854775807

int			display_error(char *output);
int			parse(t_vals *vals, int argc, char **argv);
int			messages(int philo, long int time, const char *rule);
void		*philo_routine(void *arg);
void		quit(char *error_msg, t_vals *vals);
void		clear_mutexes(t_vals *vals, t_mutexes *mutexes);
void		set_vals(int argc, char **argv);
t_vals		*get_vals(void);
long int	get_utime(void);
void		*grim_reaper_routine(void *arg);
void		delayed_start(long int actual_start, int id);
int			set2sleep(t_vals *vals, t_philo *philo, int id);
int			set2eating(t_vals *vals, t_philo *philo, int id);
int			get_fork(t_philo *philo, int id, int fork_id);
#endif