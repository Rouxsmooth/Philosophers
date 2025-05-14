/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 03:39:40 by mzaian            #+#    #+#             */
/*   Updated: 2025/05/14 16:13:10 by mzaian           ###   ########.fr       */
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
	int	message_allowed;
	int	*id_log;
	int	hunting_down;
	int	prey_amount;
}	t_grim;

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
}	t_mutexes;

typedef struct s_philo
{
	int				fork1;
	int				fork2;
	int				is_alive;
	int				thinks;
	t_time			time;
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
	int				message_allowed;
	pthread_t		*threads;
	t_mutexes		mutexes;
}	t_vals;

//typedef struct s_context
//{
//	int			id;
//	t_vals		*vals;
//}	t_context;

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
t_vals	*get_vals(void);
long int	get_utime(t_time *time);
void	grim_reaper_routine(void *arg);
#endif